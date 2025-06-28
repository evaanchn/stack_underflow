""" Copyright 2025 stack_underflow CC-BY 4.0 """

from .solver import Solver
from .solution_log import SolutionLog

class DoubleKnapsackSolver(Solver):
    def __init__(self, input, capacity):
        super().__init__(input)
        self.capacity = capacity

    """"
    TODO(us) To be completed
    source: https://www.geeksforgeeks.org/double-knapsack-dynamic-programming/
    """
    @staticmethod
    def double_knapsack_rec(n, arr, capacity1, capacity2, log=None, index = 0):
        if log: log.log_iteration()
        # Base case: if all items have been considered
        if index >= n:
            return 0

        # Option 1: Don't take the current item
        res = DoubleKnapsackSolver.double_knapsack_rec(n, arr, capacity1, capacity2, log, index + 1)

        # Option 2: If the current item can be
        # added to the first knapsack, do it
        if capacity1 >= arr[index]:
            takeInFirst = arr[index] + \
                DoubleKnapsackSolver.double_knapsack_rec(n, arr, capacity1 - arr[index], capacity2, log, index + 1)
            res = max(res, takeInFirst)

        # Option 3: If the current item can be
        # added to the second knapsack, do it
        if capacity2 >= arr[index]:
            takeInSecond = arr[index] + \
                DoubleKnapsackSolver.double_knapsack_rec(n, arr, capacity1, capacity2 - arr[index], log, index + 1)
            res = max(res, takeInSecond)
        return res

    @staticmethod
    def double_knapsack_td(nums, target, memo, log=None, index=0):
        pass

    def solve_recursive(self, log):
        n = len(self.input)
        return self.double_knapsack_rec(0, n, self.input,
                                        self.capacity,
                                        self.capacity,
                                        log)

    def solve_dynamic_top_down(self, log):
        n = len(self.input)
        return self.double_knapsack_rec(0, n, self.input,
                                                      self.capacity,
                                                      self.capacity,
                                                      log)

    def create_fitness_function(self):
        def fitness_function(solution):
            paired = list(zip(self.input, solution))
            first_sum = sum([value for value, sol in paired if sol == 1])
            second_sum = sum([value for value, sol in paired if sol == 2])

            # check capacity. Must not exceed
            if first_sum > self.capacity or second_sum > self.capacity:
                return 0

            difference = abs(first_sum - second_sum)
            # Penalize difference
            return 1 / (1 + difference)
        return fitness_function

