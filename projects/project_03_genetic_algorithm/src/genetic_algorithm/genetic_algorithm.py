""" Copyright 2025 stack_underflow CC-BY 4.0 """

import random
from .chromosome import Chromosome
from problems.solution_log import SolutionLog

class GeneticAlgorithm:
    def __init__(
                self,
                population_size,
                max_generations,
                fitness_function,
                chromosome_type,
                chromosome_length,
                min_gene_value = 0,
                max_gene_value = 1,
                elitism_percentage = 0.0,
                max_fails = float('inf'),
                parents_per_selection = 2,
                parent_selection_type = "RANKING",
                crossover_prob = 0.6,
                mutation_prob = 0.1):
        """ Set of possible solutions """
        self.population = []
        """ Amount of cromosomes in population """
        self.population_size = population_size

        """ Amount of generations to create """
        self.max_generations = max_generations
        """ Determines fitness of a cromosome """
        self.fitness_function = fitness_function
        """ Binary, real or permutation chromosome """
        self.chromosome_type = chromosome_type
        """ Amount oof elements in input"""
        self.chromosome_length = chromosome_length

        """ Min and max values gene can take on """
        self.min_gene_value = min_gene_value
        self.max_gene_value = max_gene_value

        """" Amount of elites to keep in new generations """
        self.elites_count = round(self.population_size * elitism_percentage)
        """ Max amount of generations without improvements allowed """
        self.max_fails = max_fails
        """ Amount of parents to consider in a selection """
        self.parents_per_selection = parents_per_selection

        """ Ranking, Roulette or Tournament """
        self.parent_selection_type = parent_selection_type

        """ Probabilities for new chromosomes creation """
        self.crossover_prob = crossover_prob
        self.mutation_prob = mutation_prob
        
        self.validate_attributes()

    def validate_attributes(self):
        # ---------- Validation ----------
        if type(self.population_size) != int or self.population_size <= 0:
            raise ValueError("Population size must be a positive integer.")

        if type(self.max_generations) != int or self.max_generations <= 0:
            raise ValueError("Max generations must be a positive integer.")

        if not callable(self.fitness_function):
            raise TypeError("Fitness function must be a callable function.")

        # valid_chromosome_types = {"BINARY", "REAL", "PERMUTATION"}
        if not issubclass(self.chromosome_type, Chromosome):
            raise ValueError(f"Invalid chromosome type")

        #if self.chromosome_type :   

        if type(self.chromosome_length) != int or self.chromosome_length <= 0:
            raise ValueError("Chromosome length must be a positive integer.")
        
        if not (type(self.min_gene_value) == int or type(self.min_gene_value) == float):
            raise TypeError("Minimum gene value must be an integer or float.")
        
        if not (type(self.max_gene_value) == int or type(self.max_gene_value) == float):
            raise TypeError("Maximum gene value must be an integer or float.")
    
        if not (0 <= self.elites_count < self.population_size):
            raise ValueError("Elites to preserve must be less than population size.")

        if not (type(self.max_fails) == int or self.max_fails == float('inf')) or self.max_fails < 0:
            raise ValueError("Maximun fails must be a non-negative integer or float('inf').")

        if type(self.parents_per_selection) != int or self.parents_per_selection < 2:
            raise ValueError("Parents per selection must be an integer ≥ 2.")

        valid_selection_types = {"RANKING", "ROULETTE", "TOURNAMENT"}
        if self.parent_selection_type not in valid_selection_types:
            raise ValueError(f"Parent selection type must be one of {valid_selection_types}.")

        if not (0 <= self.crossover_prob <= 1):
            raise ValueError("Crossover probability must be between 0 and 1.")

        if not (0 <= self.mutation_prob <= 1):
            raise ValueError("Mutation probability must be between 0 and 1.")
        
    def create_chromosome(self):
        """! Create with designated chromosome type,
            length of each is length of input
        """
        chromosome = self.chromosome_type(self.chromosome_length,
                                          self.min_gene_value,
                                          self.max_gene_value)
        chromosome.initialize()
        return chromosome

    def initialize_population(self):
        """ Fill list with new chromosomes """
        self.population = [self.create_chromosome()
                           for _ in range(self.population_size)]

    def evaluate_fitness(self, chromosomes):
        return [self.fitness_function(chrom.genes)
                 for chrom in chromosomes]

    def sort_by_fitness(self, chromosomes, descending=True):
        # Extract top N chromosomes
        fitness_values = self.evaluate_fitness(chromosomes)

        # Pair each chromosome with its fitness
        paired = list(zip(self.population, fitness_values))

        # Sort by fitness descending
        paired.sort(key=lambda pair: pair[1], reverse=descending)

        return [chrom for chrom, _ in paired]  # Return sorted chromosomes only

    def pick_best_chromosomes(self, chromosomes, amount):
        if amount == 0: return []
        return self.sort_by_fitness(chromosomes)[:amount]

    def ranking(self):
        """ Returns list of chromosomes with best fitness """
        return self.pick_best_chromosomes(self.population,
                                          self.parents_per_selection)

    def roulette(self):
        fitnesses = self.evaluate_fitness(self.population)
        fitnesses_sum = sum(fitnesses)
        # proportional probability from the sum of fitnesses
        probs = [fitness / fitnesses_sum for fitness in fitnesses]

        # choose random with fitness weight probability
        selected = random.choices(self.population, weights=probs,
            k = self.parents_per_selection)

        return selected

    def tournament(self, pick_winner_prob = 0.8):
        competitors = self.population[:]  # Copy to avoid modifying population
        prev_winners = competitors[:]
        while len(competitors) > self.parents_per_selection:
            next_round = []

            # if odd number, one chromosome passes to the next round
            if len(competitors) % 2 == 1:
                # select a random competitor
                lucky = competitors.pop(random.randrange(len(competitors)))
                next_round.append(lucky)
            # battle in pairs
            for i in range(0, len(competitors), 2):
                a, b = competitors[i], competitors[i + 1]
                fitness_a = self.fitness_function(a.genes)
                fitness_b = self.fitness_function(b.genes)
                if fitness_a > fitness_b:
                    best, worst = a, b
                else:
                    best, worst = b, a
                
                best_choice = random.random() < pick_winner_prob
                # pick winner with a probability
                winner = best if best_choice else worst
                next_round.append(winner)
            # Collects current round's losers, []
            prev_winners = [competitor for competitor in competitors
                            if competitor not in next_round]
            competitors = next_round
        if len(competitors) < self.parents_per_selection and len(prev_winners) > 0:
            competitors.append(random.choice(prev_winners))
        return competitors[:self.parents_per_selection]

    def selection(self):
        if self.parent_selection_type == "RANKING":
            return self.ranking()
        elif self.parent_selection_type == "ROULETTE":
            return self.roulette()
        elif self.parent_selection_type == "TOURNAMENT":
            return self.tournament()
        else:
            raise AssertionError("No suitable selection type found")

    def select_elites(self):
        return self.pick_best_chromosomes(self.population, self.elites_count)
    
    def reproduce(self, children_count):
        """! Creates new chromosomes, in a list

        @param children_count Amount of children to create
        @return List of children
        """
        children = []
        for _ in range(children_count):
            best_parents = self.selection()
            child = Chromosome.crossover(best_parents, self.crossover_prob,
                                         self.chromosome_type)
            if random.random() < self.mutation_prob:
                child.mutate()
            children.append(child)
        return children
    
    def generation_evolved(self, new_population):
        # evaluate if total fitness of new population is better than current sum
        return sum(self.evaluate_fitness(self.population)) < sum(
            self.evaluate_fitness(new_population))

    def evolve(self):
        """! Creates a new generation of chromosomes based on prev population

        @return True if at least one new child was better than the best 
            chromosome in the last generation.
        """
        evolved = True
    
        new_population = self.select_elites()  # First add elites, if any

        # Calculate remaining children to reproduce
        children_count = self.population_size - len(new_population)
        children = self.reproduce(children_count)

        # compare self population and new children
        new_population.extend(children) # Add children
        
        if self.max_fails != float('inf'):
            evolved = self.generation_evolved(new_population)
        
        self.population =  new_population

        return evolved

    def run(self, log=SolutionLog()):
        self.initialize_population()
        
        fails = 0
        # Create each generation
        for _ in range(self.max_generations):
            evolved = self.evolve()
            # If max fails attribute was set
            if self.max_fails != float('inf'):
                if not evolved:
                    fails += 1
                else:
                    pass
                    fails = 0  # Reset consecutive fails

                if fails >= self.max_fails:
                    break
            log.log_iteration(self.population_size * self.chromosome_length)

        # Return best chromosome from the last generation
        return self.population[0]
