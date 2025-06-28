""" Copyright 2025 stack_underflow CC-BY 4.0 """

from .solver import Solver
from .solution_log import SolutionLog

class DoubleKnapsackSolver(Solver):
    def __init__(self, input, capacity1, capacity2):
        super().__init__(input)
        self.capacity1 = capacity1
        self.capacity2 = capacity2

    """"
    source: https://www.geeksforgeeks.org/double-knapsack-dynamic-programming/
    """
    @staticmethod
    def double_knapsack_rec(n, arr, capacity1, capacity2, log=SolutionLog(),
                            index = 0):
        log.log_iteration()
        # Base case: If current index is past the last element, the current
        # recursive branch is done with
        if index >= n:
            return 0

        # Option 1: Don't take the current item
        accumulated = DoubleKnapsackSolver.double_knapsack_rec(n,
                                                            arr,
                                                            capacity1,
                                                            capacity2,
                                                            log, 
                                                            index + 1)

        # Option 2: If the current item can be
        # added to the first knapsack, do it
        if capacity1 >= arr[index]:
            takeInFirst = arr[index] + \
                DoubleKnapsackSolver.double_knapsack_rec(n,
                                                         arr,
                                                         capacity1 - arr[index],
                                                         capacity2,
                                                         log,
                                                         index + 1)
            accumulated = max(accumulated, takeInFirst)

        # Option 3: If the current item can be
        # added to the second knapsack, do it
        if capacity2 >= arr[index]:
            takeInSecond = arr[index] + \
                DoubleKnapsackSolver.double_knapsack_rec(n,
                                                         arr,
                                                         capacity1,
                                                         capacity2 - arr[index],
                                                         log,
                                                         index + 1)
            accumulated = max(accumulated, takeInSecond)
        return accumulated

    @staticmethod
    def double_knapsack_td(n, arr, capacity1, capacity2, memo=dict(),
                           log=SolutionLog(), index = 0):
        log.log_iteration()

        # Base case: if all items have been considered
        if index >= n:
            return 0

        key = (index, capacity1, capacity2)
        if (key in memo):
            return memo[key]

        # Option 1: Don't take the current item
        memo[key] = DoubleKnapsackSolver.double_knapsack_td(n,
                                                       arr,
                                                       capacity1,
                                                       capacity2,
                                                       memo,
                                                       log,
                                                       index + 1)

        # Option 2: If the current item can be
        # added to the first knapsack, do it
        if capacity1 >= arr[index]:
            takeInFirst = arr[index] + \
                DoubleKnapsackSolver.double_knapsack_td(n,
                                                         arr,
                                                         capacity1 - arr[index],
                                                         capacity2,
                                                         memo,
                                                         log,
                                                         index + 1)
            memo[key] = max(memo[key], takeInFirst)

        # Option 3: If the current item can be
        # added to the second knapsack, do it
        if capacity2 >= arr[index]:
            takeInSecond = arr[index] + \
                DoubleKnapsackSolver.double_knapsack_td(n,
                                                         arr,
                                                         capacity1,
                                                         capacity2 - arr[index],
                                                         memo,
                                                         log,
                                                         index + 1)
            memo[key] = max(memo[key], takeInSecond)
        return memo[key]

    def solve_recursive(self, log):
        return self.double_knapsack_rec(len(self.input),
                                        self.input,
                                        self.capacity1,
                                        self.capacity2,
                                        log)

    def solve_dynamic_top_down(self, log):
        return self.double_knapsack_rec(len(self.input),
                                        self.input,
                                        self.capacity1,
                                        self.capacity2,
                                        log)

    def solve_genetic(self, genetic_algorithm, log):
        solution_chromosome = genetic_algorithm.run(log)
        # The sum of weights both knapsacks retrieve is the solution to the prob
        accumulated = sum([self.input[i] for i in range(len(self.input))
                           if solution_chromosome[i] == 1
                           or solution_chromosome[i] == 2])
        return accumulated

    def create_fitness_function(self):
        def fitness_function(solution):
            paired = list(zip(self.input, solution))
            first_sum = sum([value for value, sol in paired if sol == 1])
            second_sum = sum([value for value, sol in paired if sol == 2])

            # check capacity. Must not exceed
            if first_sum > self.capacity1 or second_sum > self.capacity2 \
                or first_sum + second_sum == 0:
                return 0

            # Penalize difference
            return 1 - (1 / first_sum + second_sum)
        return fitness_function

