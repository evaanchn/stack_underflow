""" Copyright Sergio Moya Valerin, ejemplo de clase CI-0116 """

from .solver import Solver
from .solution_log import SolutionLog
# TODO(any): Think about solution type for genetic algorithm with this problem
class MinCoinsChangeSolver(Solver):
    def __init__(self, input, amount):
        super().__init__(input)
        self.amount = amount

    @staticmethod
    def min_coins_rec(coins, amount, log = None):
        if log: log.log_iteration()

        if amount == 0:
            return 0
        if amount < 0:
            return float('inf')  # Negative means no complete change for this collection

        min_coins = float('inf')
        for coin in coins:
            res = MinCoinsChangeSolver.min_coins_rec(coins, amount - coin, log)
            if res != float('inf'):
                min_coins = min(min_coins, res + 1)
    
        return min_coins

    @staticmethod
    def min_coins_topdown(coins, amount, memo = None, log = None):
        if log: log.log_iteration()

        if amount in memo:
            return memo[amount]

        if amount == 0:
            return 0
        if amount < 0:
            return float('inf')  # Negative means no complete change for this collection

        min_coins = float('inf')
        for coin in coins:
            res = MinCoinsChangeSolver.min_coins_topdown(coins, amount - coin, memo, log)
            if res != float('inf'):
                min_coins = min(min_coins, res + 1)
    
        memo[amount] = min_coins
        return min_coins

    @staticmethod
    def min_coins_bottomup(coins, amount, log = None):
        coins.sort()
        best_change = dict()
        for current_amount in range (coins[0], amount + 1):
            for coin in coins[::-1]:
                remaining_change = current_amount - coin
                if remaining_change == 0:
                    best_change[current_amount] = 1
                    break
                elif remaining_change > 0 and remaining_change in best_change:
                    best_change[current_amount] = best_change[remaining_change] + 1
                    break
                if log: log.log_iteration()
        return best_change[amount]

    def solve_recursive(self, log):
        return self.min_coins_rec(self.input, self.amount, log)

    def solve_dynamic_top_down(self, log):
        memo = dict()
        return self.min_coins_topdown(self.input, self.amount, memo, log)

    def solve_dynamic_bottom_up(self, log):
        return self.min_coins_bottomup(self.input, self.amount, log)

    def create_fitness_function(self):
        """ Using real (whole) chromosome, each gene representing amount
            of coins for the coin in the same position """
        def fitness_function(solution):
            solution_sum = sum([self.input[i] * solution[i]
                                for i in range(len(self.input))])
            if solution_sum == self.amount:
                return 1
            return 0
        return fitness_function

