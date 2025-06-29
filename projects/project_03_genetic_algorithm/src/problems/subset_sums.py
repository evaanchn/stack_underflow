""" Copyright 2025 stack_underflow CC-BY 4.0 """

from .solver import Solver
from .solution_log import SolutionLog

class SubsetSumSolver(Solver):
    def __init__(self, input, target_sum):
        super().__init__(input)
        self.target_sum = target_sum
        self.fitness_function = self.create_fitness_function()

    @staticmethod
    def subset_sum_rec(nums, target, subset=[], index = 0, log=SolutionLog()):
        log.log_iteration()

        # Base cases. Decides if subset's sum is target with end of list index
        if target == 0:
            return True
        if index == len(nums):
            return False

        # Skip current number
        if SubsetSumSolver.subset_sum_rec(nums, target, subset, index + 1, log):
            return True

        # Then, include current number, if it's not larger than target
        if nums[index] <= target:
            subset.append(nums[index])  # Add element
            if SubsetSumSolver.subset_sum_rec(nums,
                                              target - nums[index],
                                              subset,
                                              index + 1,
                                              log):
                return True
            else:
                subset.pop()

        # No subset found
        return False

    @staticmethod
    def subset_sum_td(nums, target, memo, subset=[], index=0, log=SolutionLog()):
        log.log_iteration()

        key = (index, target)
        if key in memo:
            return memo[key]

        if target == 0:
            return True
        if index == len(nums):
            return False

        # Try skipping the current number
        if SubsetSumSolver.subset_sum_td(nums,
                                         target,
                                         memo,
                                         subset,
                                         index + 1,
                                         log):
            memo[key] = True
            return True

        # Try including the current number
        if nums[index] <= target:
            subset.append(nums[index])
            if SubsetSumSolver.subset_sum_td(nums,
                                             target - nums[index],
                                             memo,
                                             subset,
                                             index + 1,
                                             log):
                memo[key] = True
                return True
            subset.pop()  # Undo append

        memo[key] = False
        return False

    def solve_recursive(self, log):
        return self.subset_sum_rec(self.input, self.target_sum, log=log)

    def solve_dynamic_top_down(self, log):
        memo = dict()
        return self.subset_sum_td(self.input, self.target_sum, memo, log=log)

    def solve_genetic(self, genetic_algorithm, log):
        solution_chromosome = genetic_algorithm.run(log)
        solution_genes = solution_chromosome.genes
        return [self.input[i] for i in range(len(self.input))
                if solution_genes[i] == 1]
        

    def create_fitness_function(self):
        """ Create fitness function for binary chromosome
            gene = 0 means element at that index is not included
            gene = 1 means element at that index is included """
        def fitness_function(solution):
            paired = list(zip(self.input, solution))
            subset_sum = sum([value * sol for value, sol in paired])
            difference = abs(self.target_sum - subset_sum)
            # Minimazation problem: we want a subset sum as close
            # to target as possible
            return 1 / (1 + difference)  # Ideal difference is 0, for fitness 1
        return fitness_function

