""" Copyright Stack Underflow 2025 CC-BY 4.0 """
from .solver import Solver
from .solution_log import SolutionLog

class PartitionSolver(Solver):
    def __init__(self, input):
        super().__init__(input)
        self.fitness_function = self.create_fitness_function()

    @staticmethod
    def get_differences(input, sum_left, best_solution):
        difference = abs(sum_left - (sum(input) - sum_left))
        best_left = sum([input[i] for i in range(len(input)) if best_solution[i] == 0])
        return difference, abs(best_left - (sum(input) - best_left))
       
    @staticmethod
    def partition_rec(input, solution, best_solution, index=0, log=SolutionLog()):
        log.log_iteration()

        if index == len(input):
            sum_left = sum([input[i] for i in range(len(input)) if solution[i] == 0])
            difference, best_difference = \
                PartitionSolver.get_differences(input,
                                                sum_left,
                                                best_solution)

            if difference < best_difference:
                best_solution[:] = solution

            return difference
        
        least_difference = float('inf')
        # left
        solution[index] = 0
        difference = PartitionSolver.partition_rec(input, solution,
                                                  best_solution, index + 1, log)
        if difference != float('inf'):
           least_difference = min(least_difference, difference)

        # right
        solution[index] = 1
        difference = PartitionSolver.partition_rec(input, solution,
                                                  best_solution, index + 1, log)
        if difference != float('inf'):
           least_difference = min(least_difference, difference)

        return least_difference

    @staticmethod
    def partition_td(input, solution, memo, best_solution,
                     index=0, sum_left=0, log=SolutionLog()):
        log.log_iteration()

        if index == len(input):
            difference, best_difference = \
                PartitionSolver.get_differences(input,
                                                sum_left,
                                                best_solution)
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
                                                  best_solution, index + 1,
                                                  sum_left + input[index], log)
        if difference != float('inf'):
           least_difference = min(least_difference, difference)

        # right
        solution[index] = 1
        difference = PartitionSolver.partition_td(input, solution, memo,
                                                  best_solution, index + 1,
                                                  sum_left, log)
        if difference != float('inf'):
           least_difference = min(least_difference, difference)

        memo[key] = least_difference
        return least_difference

    def get_partitions(self, combination):
        left_partition = [self.input[i] for i in range(len(self.input)) \
                          if combination[i] == 0]
        right_partition = [self.input[i] for i in range(len(self.input)) \
                           if combination[i] == 1]

        return (left_partition, sum(left_partition)), \
            (right_partition, sum(right_partition))

    def solve_recursive(self, log):
        solution = [0] * len(self.input)
        best_solution = [0] * len(self.input)
        self.partition_rec(self.input, solution, best_solution, log=log)
        return self.get_partitions(best_solution)
    
    def solve_dynamic_top_down(self, log):
        solution = [0] * len(self.input)
        best_solution = [0] * len(self.input)
        memo = {}
        self.partition_td(self.input, solution, memo, best_solution, log=log)
        return self.get_partitions(best_solution)

    def solve_genetic(self, genetic_algorithm, log):
        solution_chromosome = genetic_algorithm.run(log)
        return self.get_partitions(solution_chromosome.genes)

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
