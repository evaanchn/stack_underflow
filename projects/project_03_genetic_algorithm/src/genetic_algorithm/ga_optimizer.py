""" Copyright 2025 stack_underflow CC-BY 4.0 """

import optuna
import optuna.visualization as vis

# Local imports
from .chromosome import Chromosome
from .genetic_algorithm import GeneticAlgorithm
from problems.solution_log import SolutionLog

class GAOptimizer:
    def __init__(self,
                 chromosome_type,
                 chromosome_length,
                 fitness_function,
                 base_time,
                 min_gene_value=0,
                 max_gene_value=1,
                 study_name=None,
                 storage = None,
                 direction="maximize"):
        """
        Initializes the optimizer.

        :param chromosome_type: The Chromosome subclass to use.
        :param chromosome_length: Length of input, same length as chromosome.
        :param fitness_function: Problem-specific fitness function.
        :param base_time: Recursive's duration for the same problem.
        :param min_gene_value: Minimum value a gene could be
        :param max_gene_value: Maximum value gene can be
        :param storage: Directory of storage.
        :param study_name: Optional name for the study.
        :param direction: Optimization direction ("maximize" or "minimize").
        """
        # Store non-variating parameters as attributes
        self.chromosome_type = chromosome_type
        self.chromosome_length = chromosome_length
        self.fitness_function = fitness_function
        self.min_gene_value = min_gene_value
        self.max_gene_value = max_gene_value
        self.base_time = base_time

        # Create or load study
        if storage:
            self.study = optuna.create_study(
                study_name=study_name,  # Name of study
                storage=storage,
                direction=direction,  # Direction, "maximize" by default
                load_if_exists=True  # Prevents error if previous study with same name exists
            )
        else:
            self.study = optuna.create_study(study_name=study_name,
                                             direction=direction)
    
    def objective(self, trial):
        # Suggest hyperparameters
        population_size = trial.suggest_int("population_size", 10, 500)
        max_generations = trial.suggest_int("max_generations", 50, 150)
        elitism_percentage = trial.suggest_float("elitism_percentage", 0.0, 0.3)
        max_fails = trial.suggest_int("max_fails", 10, 100)
        parents_per_selection = trial.suggest_int("parents_per_selection", 2, 8)
        parent_selection_type = trial.suggest_categorical(
            "parent_selection_type",
            ["RANKING", "ROULETTE", "TOURNAMENT"]
        )
        crossover_prob = trial.suggest_float("crossover_prob", 0.5, 0.99)
        mutation_prob = trial.suggest_float("mutation_prob", 0.01, 0.5)

        # Create and run GA
        ga = GeneticAlgorithm(
            population_size=population_size,
            max_generations=max_generations,
            fitness_function=self.fitness_function,
            chromosome_type=self.chromosome_type,
            chromosome_length=self.chromosome_length,
            min_gene_value = self.min_gene_value,
            max_gene_value = self.min_gene_value,
            max_fails=max_fails,
            elitism_percentage=elitism_percentage,
            parents_per_selection=parents_per_selection,
            parent_selection_type=parent_selection_type,
            crossover_prob=crossover_prob,
            mutation_prob=mutation_prob,
        )
 
        # Create log to take duration into consideration
        log =  SolutionLog()
        log.record_start()
        best_chromosome = ga.run(log)
        log.record_finish()
        fitness = self.fitness_function(best_chromosome.genes)

        # Optuna will try to maximize the fitness + speedup
        return fitness + self.base_time / log.get_duration()

    def optimize(self, n_trials=20, n_jobs=1):
        """
        Runs the hyperparameter optimization.

        :param n_trials: Number of Optuna trials.
        :param n_jobs: Number of parallel jobs.
        :return: Best hyperparameters found.
        """
        self.study.optimize(self.objective, n_trials=n_trials, n_jobs=n_jobs)
        return self.study.best_params

    # GETS
    def get_best_params(self):
        return self.study.best_params

    def get_best_value(self):
        return self.study.best_value

    def get_study(self):
        return self.study

    # PLOTS
    def save_summary(self, directory="optuna_studies",
                     summmary_name="study_summary.txt"):
        """ creates a txt file with summary of study """
        # Create directory, if it doesn't exist already
        import os
        os.makedirs(directory, exist_ok=True)
        path = os.path.join(directory, summmary_name)

        # Open summary file in writing mode and write best value and best params
        with open(path, "w") as f:
            f.write(f"Best value: {self.study.best_value}\n")
            f.write(f"Best params:\n")
            for key, val in self.study.best_params.items():
                f.write(f"  {key}: {val}\n")

    def plot_optimization_history(self, directory="optuna_studies"):
        """ shows the objective value per trial (progress). """
        import os
        os.makedirs(directory, exist_ok=True)

        fig = vis.plot_optimization_history(self.study)
        fig.write_html(os.path.join(directory, "optimization_history.html"))
        print("Saved optimization history plot.")

    def plot_param_importances(self, directory="optuna_studies"):
        """ shows which hyperparameters most affect performance. """
        import os
        os.makedirs(directory, exist_ok=True)

        fig = vis.plot_param_importances(self.study)
        fig.write_html(os.path.join(directory, "param_importances.html"))
        print("Saved parameter importances plot.")

    def plot_parallel_coordinate(self, directory="optuna_studies"):
        """ visualizes relationships between parameters and objective. """
        import os
        os.makedirs(directory, exist_ok=True)

        fig = vis.plot_parallel_coordinate(self.study)
        fig.write_html(os.path.join(directory, "parallel_coordinate.html"))
        print("Saved parallel coordinate plot.")
