""" Copyright Stack Underflow 2025 CC-BY 4.0 """
from .solver import Solver
from .solution_log import SolutionLog

class PartitionSolver(Solver):
    def __init__(self, input):
        super().__init__(input)
        
    @staticmethod
    def partition_rec(input, solution, best_solution, log=None, index = 0):
        if log: log.log_iteration()

        if index == len(input):
            sum_left = sum([input[i] for i in range(len(input)) if solution[i] == 0])
            difference = abs(sum_left - (sum(input) - sum_left))
            best_left = sum([input[i] for i in range(len(input)) if best_solution[i] == 0])
            best_difference = abs(best_left - (sum(input) - best_left))

            if difference < best_difference:
                best_solution[:] = solution

            return difference
        
        least_difference = float('inf')
        # left
        solution[index] = 0
        difference = PartitionSolver.partition_rec(input, solution,
                                                  best_solution, log, index + 1)
        if difference != float('inf'):
           least_difference = min(least_difference, difference)

        # right
        solution[index] = 1
        difference = PartitionSolver.partition_rec(input, solution,
                                                  best_solution, log, index + 1)
        if difference != float('inf'):
           least_difference = min(least_difference, difference)

        return least_difference

    @staticmethod
    def partition_td(input, solution, memo, best_solution, log=None,
                     index = 0, sum_left = 0):
        if log: log.log_iteration()

        if index == len(input):
            difference = abs(sum_left - (sum(input) - sum_left))
            paired = list(zip(input, best_solution))
            best_left = sum([value for value, sol in paired if sol == 0])
            best_difference = abs(best_left - (sum(input) - best_left))
            if difference < best_difference:
                best_solution[:] = solution

            return difference
        
        key = (index, sum_left)
        if key in memo:
            return memo[key]
        
        least_difference = float('inf')
        # left
        solution[index] = 0
        difference = PartitionSolver.partition_td(input, solution, memo,
                                                  best_solution, log, index + 1,
                                                  sum_left + input[index])
        if difference != float('inf'):
           least_difference = min(least_difference, difference)

        # right
        solution[index] = 1
        difference = PartitionSolver.partition_td(input, solution, memo,
                                                  best_solution, log, index + 1,
                                                  sum_left)
        if difference != float('inf'):
           least_difference = min(least_difference, difference)

        memo[key] = least_difference
        return least_difference
    
    def solve_recursive(self, log):
        solution = [0] * len(self.input)
        best_solution = [0] * len(self.input)
        self.partition_rec(self.input, solution, best_solution, log)
        return best_solution
    
    def solve_dynamic_top_down(self, log):
        solution = [0] * len(self.input)
        best_solution = [0] * len(self.input)
        memo = {}
        self.partition_td(self.input, solution, memo, best_solution, log)
        return best_solution

    def create_fitness_function(self):
        def fitness_function(solution):
            total_weight = sum(self.input)
            paired = list(zip(self.input, solution))
            
            # 0 means left partition, 1 means right partition
            sumleft = sum([weight for weight, sol in paired if sol == 0])
            sumright = sum([weight for weight, sol in paired if sol == 1])
            
            difference = abs(sumleft - sumright)

            # Penalize difference
            if difference == 1 and total_weight % 2 != 0:  #odd
                return 1
            return 1 / (1 + difference)  # even
        return fitness_function


"""Extra method for iterative solution"""
def partition_iterative(input):
  total_weight = sum(input)
  print(total_weight)
  bits_count = len(input)
  conbination_count = 2**bits_count

  best_solution = []
  minimum_difference = float('inf')

  for i in range(conbination_count):
    # create combination
    offset = 1
    combination = [0]*bits_count
    for digit in reversed(str(bin(i))[2:]):
      combination[bits_count - offset] = int(digit)
      offset =  offset + 1

    # evaluate
    sumleft = sum([input[i] for i in range(len(input)) if combination[i] == 0])
    sumright = sum([input[i] for i in range(len(input)) if combination[i] == 1])
    difference = abs(sumleft - sumright)
    if difference < minimum_difference or minimum_difference == float('inf'):
      best_solution = combination.copy()
      minimum_difference = difference
      # first optimal
      if difference <= 1:
          if total_weight % 2 != 0:  # odd
            return best_solution
          elif difference == 0:     # even
            return best_solution

  return best_solution
