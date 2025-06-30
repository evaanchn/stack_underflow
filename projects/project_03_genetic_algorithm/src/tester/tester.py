""" Copyright 2025 stack_underflow CC-BY 4.0 """

import sys
import random

# Local imports
from problems.solver import Solver
from problems.solution_log import SolutionLog
from genetic_algorithm.chromosome import Chromosome, BinaryChromosome, RealChromosome
from genetic_algorithm.genetic_algorithm import GeneticAlgorithm
from genetic_algorithm.ga_optimizer import GAOptimizer

REPORTS_DIRECTORY = "reports/"

class Tester:
    def __init__(self, problem_name):
        self.problem_name = problem_name
        self.path, self.file_name = self.initialize_file()
        self.write_header()

    def initialize_file(self):
        import os
        # Create directory if it doesn't exist already
        os.makedirs(REPORTS_DIRECTORY, exist_ok=True)

        # Initialize file name as problem name with txt extension
        file_name = self.problem_name
        path = os.path.join(REPORTS_DIRECTORY, f"{self.problem_name}.txt")
        counter = 1

        # Starting from base name, build up file name until it's properly enumerated
        while os.path.exists(path):
            file_name = f"{self.problem_name}_{counter}"
            path = os.path.join(REPORTS_DIRECTORY, f"{file_name}.txt")
            counter += 1
        return path, file_name

    def write_header(self):
        # Write header
        with open(self.path, "w") as f:
            f.write(f"***  [REPORT]  ***\n")
            f.write(f"Problem: {self.problem_name}\n")
            f.write(f"METHOD | ITERATIONS | DURATION (ms) | SOLUTION \n")

    def write_input(self, input):
        # Write header
        with open(self.path, "a") as f:
            f.write(f"Input: {input}\n")

    def write_result(self, solve_mode, log):
        with open(self.path, "a") as f:
            f.write(f"\n{solve_mode} | {log.to_string()} | {log.solution}\n")

    def test_fixed_input(self, solver, optimizations, chromosome_type,
                         min_gene=0, max_gene=1):
        self.write_input(solver.input)
        log_recursive = solver.solve("RECURSIVE")
        self.write_result("RECURSIVE", log_recursive)

        log_dynamic_td = solver.solve("DYNAMIC_TD")
        self.write_result("DYNAMIC_TOPDOWN", log_dynamic_td)

        optimizer = GAOptimizer(chromosome_type=chromosome_type,
                           chromosome_length=len(solver.input),
                           fitness_function=solver.fitness_function,
                           base_time=log_recursive.get_duration(),
                           study_name=self.file_name)
        params = optimizer.optimize(optimizations)

        genetic_optimized = GeneticAlgorithm(
            population_size=params['population_size'],
            max_generations=params['max_generations'],
            fitness_function=solver.fitness_function,
            chromosome_type=chromosome_type,
            chromosome_length=len(solver.input),
            min_gene_value=min_gene,
            max_gene_value=max_gene,
            elitism_percentage=params['elitism_percentage'],
            crossover_prob=params['crossover_prob'],
            max_fails=params['max_fails'],
            mutation_prob=params['mutation_prob'],
            parents_per_selection=params['parents_per_selection'],
            parent_selection_type=params['parent_selection_type']
        )
        log_genetic = solver.solve("GENETIC", genetic_optimized)
        self.write_result("GENETIC", log_genetic)

        optimizer.save_summary(REPORTS_DIRECTORY, f"{self.file_name}.txt")
        optimizer.plot_optimization_history()
        optimizer.plot_param_importances()
        optimizer.plot_parallel_coordinate()


    def test_increasing_input(self, solver, optimizations, chromosome_type,
                              iterations, increase_size, size, min_gene=0,
                              max_gene=1):
        # Test with the initial input size and increase as specified
        for increase in range(iterations):
            new_input = list(range(1, size + 1))
            random.shuffle(new_input)
            solver.input = new_input
            print(f"Testing input size: {size} with input: {solver.input}")

            self.test_fixed_input(solver, optimizations, chromosome_type,
                                  min_gene, max_gene)
            
            size += increase_size