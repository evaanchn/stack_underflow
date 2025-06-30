""" Copyright 2025 stack_underflow CC-BY 4.0 """

from .solver import Solver
from .solution_log import SolutionLog

class DoubleKnapsackSolver(Solver):
    def __init__(self, input, capacity1, capacity2):
        super().__init__(input)
        self.capacity1 = capacity1
        self.capacity2 = capacity2
        self.fitness_function = self.create_fitness_function()

    """
    source: https://www.geeksforgeeks.org/double-knapsack-dynamic-programming/
    """
    @staticmethod
    def double_knapsack_rec(n, arr, capacity1, capacity2, index = 0, log=SolutionLog()):
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
                                                            index + 1,
                                                            log)

        # Option 2: If the current item can be
        # added to the first knapsack, do it
        if capacity1 >= arr[index]:
            takeInFirst = arr[index] + \
                DoubleKnapsackSolver.double_knapsack_rec(n,
                                                         arr,
                                                         capacity1 - arr[index],
                                                         capacity2,
                                                         index + 1,
                                                         log)
            accumulated = max(accumulated, takeInFirst)

        # Option 3: If the current item can be
        # added to the second knapsack, do it
        if capacity2 >= arr[index]:
            takeInSecond = arr[index] + \
                DoubleKnapsackSolver.double_knapsack_rec(n,
                                                         arr,
                                                         capacity1,
                                                         capacity2 - arr[index],
                                                         index + 1,
                                                         log)
            accumulated = max(accumulated, takeInSecond)
        return accumulated

    @staticmethod
    def double_knapsack_td(n, arr, capacity1, capacity2, memo, index=0, log=SolutionLog()):
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
                                                       index + 1,
                                                       log)

        # Option 2: If the current item can be
        # added to the first knapsack, do it
        if capacity1 >= arr[index]:
            takeInFirst = arr[index] + \
                DoubleKnapsackSolver.double_knapsack_td(n,
                                                         arr,
                                                         capacity1 - arr[index],
                                                         capacity2,
                                                         memo,
                                                         index + 1,
                                                         log)
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
                                                         index + 1,
                                                         log)
            memo[key] = max(memo[key], takeInSecond)
        return memo[key]

    def solve_recursive(self, log):
        return self.double_knapsack_rec(n=len(self.input),
                                        arr=self.input,
                                        capacity1=self.capacity1,
                                        capacity2=self.capacity2,
                                        log=log)

    def solve_dynamic_top_down(self, log):
        return self.double_knapsack_rec(n=len(self.input),
                                        arr=self.input,
                                        capacity1=self.capacity1,
                                        capacity2=self.capacity2,
                                        log=log)

    def solve_genetic(self, genetic_algorithm, log):
        solution_chromosome = genetic_algorithm.run(log=log)
        solution_genes = solution_chromosome.genes
        # The sum of weights both knapsacks retrieve is the solution to the prob
        accumulated = sum([self.input[i] for i in range(len(self.input))
                           if solution_genes[i] == 1
                           or solution_genes[i] == 2])
        return accumulated

    def create_fitness_function(self):
        """ Create fitness function for real chromosome, where, at each index:
            gene = 0 means the element is not included
            gene = 1 means the element is included in knapsack 1
            gene = 2 means the element is included in knapsack 2 """
        def fitness_function(solution):
            paired = list(zip(self.input, solution))
            # Calculated accumulated weights for each knapsack
            first_sum = sum([value for value, sol in paired if sol == 1])
            second_sum = sum([value for value, sol in paired if sol == 2])

            # The knapsack capacities must not be surpassed, a solution with 0
            # weight taken is invalid. Return worst fitness for these scenarios
            if first_sum > self.capacity1 or second_sum > self.capacity2 \
                or first_sum + second_sum == 0:
                return 0

            # Maximization problem: The bigger the total sum, the less is subtracted
            return 1 - (1 / 1 + first_sum + second_sum)
        return fitness_function

