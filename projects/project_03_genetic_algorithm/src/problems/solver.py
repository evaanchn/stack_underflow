""" Copyright 2025 stack_underflow CC-BY 4.0 """

from .solution_log import SolutionLog
from genetic_algorithm.genetic_algorithm import GeneticAlgorithm

class Solver:
    def __init__(self, input):
        self.input = input

    def solve(self, solve_mode, genetic_algorithm = None):
        log = SolutionLog()
        log.record_start()

        if solve_mode == "RECURSIVE":
            log.solution = self.solve_recursive(log)
        elif solve_mode == "DYNAMIC_TD":
            log.solution = self.solve_dynamic_top_down(log)
        elif solve_mode == "DYNAMIC_BU":
            log.solution = self.solve_dynamic_bottom_up(log)
        elif solve_mode == "GENETIC":
            if genetic_algorithm is None:
                raise ValueError("genetic_algorithm must be provided for GENETIC solve mode")
            log.solution = self.solve_genetic(genetic_algorithm, log)
        else:
            raise ValueError(f"Unknown solve mode: {solve_mode}")

        log.record_finish()
        return log

    def solve_recursive(self, log):
        raise NotImplementedError

    def solve_dynamic_top_down(self, log):
        raise NotImplementedError
    
    def solve_dynamic_bottom_up(self, log):
        pass

    def solve_genetic(self, genetic_algorithm, log):
        raise NotImplementedError
    
    def create_fitness_function(self, log):
        raise NotImplementedError
