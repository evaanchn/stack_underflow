""" Copyright 2025 stack_underflow CC-BY 4.0 """

from .solver import Solver
from .solution_log import SolutionLog

class SubsetSumSolver(Solver):
    def __init__(self, input, target_sum):
        super().__init__(input)
        self.target_sum = target_sum

    @staticmethod
    def subset_sum_rec(nums, target, log = SolutionLog(), best_subset = [],
                       index = 0):
        if log: log.log_iteration()

        # Base cases. Decides if subset's sum is target with end of list index
        if target == 0:
            return True
        if index == len(nums):
            return False

        # Skip current number
        if SubsetSumSolver.subset_sum_rec(nums, target, log, best_subset,
                                            index + 1):
            return True

        # Then, include current number, if it's not larger than target
        if nums[index] <= target:
            best_subset.append(nums[index])
            if SubsetSumSolver.subset_sum_rec(nums, target - nums[index], log,
                                                    best_subset, index + 1):
                return True
            else:
                best_subset.pop()

        # No subset found
        return False

    @staticmethod
    def subset_sum_td(nums, target, memo, log=None, best_subset=[], index=0):
        if log: log.log_iteration()

        key = (index, target)
        if key in memo:
            return memo[key]

        if target == 0:
            return True
        if index == len(nums):
            return False

        # Try skipping the current number
        if SubsetSumSolver.subset_sum_td(nums, target, memo, log, best_subset, index + 1):
            memo[key] = True
            return True

        # Try including the current number
        if nums[index] <= target:
            best_subset.append(nums[index])
            if SubsetSumSolver.subset_sum_td(nums, target - nums[index], memo, log, best_subset, index + 1):
                memo[key] = True
                return True
            best_subset.pop()  # Undo append

        memo[key] = False
        return False


    def solve_recursive(self, log):
        return self.subset_sum_rec(self.input, self.target_sum, log)

    def solve_dynamic_top_down(self, log):
        memo = dict()
        return self.subset_sum_td(self.input, self.target_sum, memo, log)

    def create_fitness_function(self):
        def fitness_function(solution):
            paired = list(zip(self.input, solution))
            subset_sum = sum([value * sol for value, sol in paired])
            difference = abs(self.target_sum - subset_sum)
            # Penalize difference
            return 1 / (1 + difference)
        return fitness_function

