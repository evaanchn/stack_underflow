""" Copyright Stack Underflow 2025 CC-BY 4.0 """

def make_partition_function(input):
    def partition_fitness(solution):
        total_weight = sum(input)
        partition_weight = total_weight // 2
        paired = list(zip(input, solution))

        # 0 means left partition, 1 means right partition
        # e.g. input = [2, 10, 3, 8, 5, 7, 9, 5, 3, 2] 
        #   solution = [1, 1, 1, 0, 1, 1, 0, 0, 0, 0]
        sumleft = sum([value for value, sol in paired if sol == 0])
        sumright = sum([value for value, sol in paired if sol == 1])
        # TODO remove print
        # print(f"Total weight: {total_weight}, Left sum: {sumleft}, Right sum: {sumright}")
        difference = abs(sumleft - sumright)

        # Penalize difference
        if difference == 1 and total_weight % 2 != 0:  #odd
            return 1
        return 1 / (1 + difference)  # even
    return partition_fitness


def two_partition_recursive(list, index = float('inf'),left_count = 0, right_count = 0):
  if len(list) < 2:
    return float("inf")

  if index == float('inf'):
    index = len(list) - 1
  
  
  
  partition_weight = sum(list) // 2
  left_difference = abs(left_count - partition_weight)
  right_difference = abs(right_count - partition_weight)

  if left_difference <= 1 and right_difference <= 1:
    difference = abs(left_count - right_count)
    if difference == 1:
      if partition_weight % 2 == 0:
          return partition_weight
      else:
        return float('inf')
    if difference == 0:
      return partition_weight

    element = list[index]
    two_partition_recursive(list, index - 1,left_count + element, right_count)
    two_partition_recursive(list, left_count, right_count + element)
