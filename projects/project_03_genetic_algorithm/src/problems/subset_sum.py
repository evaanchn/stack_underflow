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
    def subset_sum_top_down(nums, target, memo, subset=[], index=0, log=SolutionLog()):
        log.log_iteration()

        key = (index, target)
        if key in memo:
            return memo[key]

        if target == 0:
            return True
        if index == len(nums):
            return False

        # Try skipping the current number
        if SubsetSumSolver.subset_sum_top_down(nums,
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
            if SubsetSumSolver.subset_sum_top_down(nums,
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

    @staticmethod
    def subset_sum_bottom_up(nums, target, log=SolutionLog()):
        # Must build up to n
        n = len(nums)
        # Start tabulation dict, setting all sums except 0 to false for empty subset
        # (Empty set [] can only have subset [] that sums to 0)
        dp = {(0, sum_target): False for sum_target in range(1, target + 1)}
        dp[(0, 0)] = True

        # Start evaluating from list of size 1 to size n
        for current_size in range(1, n + 1):
            # A target 0 can be achieved with empty subset for any list size
            dp[(current_size, 0)] = True

            # Try to form sums with current list size building up from 1 to target
            for current_target in range(1, target + 1):
                log.log_iteration()
                prev_idx = current_size - 1

                if current_target < nums[prev_idx]:
                    # Skip current element, since it's greater than the desired target
                    dp[(current_size, current_target)] = dp[(prev_idx, current_target)]
                else:
                    # Otherwise, copy prev verdict | key = (prev_idx, current_target)
                    # or determine if a new subset that sums to the target was found
                    dp[(current_size, current_target)] = dp[(prev_idx, current_target)] \
                                                or dp[(prev_idx, current_target - nums[prev_idx])]

                # If at any size of the list considered, there is a subset 
                # that sums to target, then we can truncate and return True
                if current_target == target and dp[(current_size, target)]: return True
        return dp[(n, target)]

    def solve_recursive(self, log):
        return self.subset_sum_rec(self.input, self.target_sum, log=log)

    def solve_dynamic_top_down(self, log):
        memo = dict()
        return self.subset_sum_top_down(self.input, self.target_sum, memo, log=log)

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

