""" Copyright 2025 stack_underflow CC-BY 4.0 """
import sys
import random

from problems.bin_packing import BinPackingSolver
from problems.double_knapsack import DoubleKnapsackSolver
from problems.partition import PartitionSolver
from problems.subset_sum import SubsetSumSolver
from genetic_algorithm.genetic_algorithm import GeneticAlgorithm
from genetic_algorithm.chromosome import BinaryChromosome
from genetic_algorithm.chromosome import RealChromosome
from genetic_algorithm.ga_optimizer import GAOptimizer
from tester.tester import Tester

def invalid_option(problem):
    return problem != "bin_packing" and problem != "subset_sum" and \
           problem != "double_knapsack" and problem != "partition"

def selected_option(problem, problem_input, range_numbers):
    solver = None
    chromosome_type = None
    min_gen = 0
    max_gen = 1
    increase_size = 3
    if (problem == "subset_sum"):
        # SubsetSumSolver(input, target_sum)
        solver = SubsetSumSolver(problem_input, 15)
        chromosome_type = BinaryChromosome
        increase_size = 4
    elif (problem == "partition"):
        # PartitionSolver(input)
        solver = PartitionSolver(problem_input)
        chromosome_type = BinaryChromosome
        increase_size = 4
    elif (problem == "bin_packing"):
        # BinPackingSolver(input, bins_count, bin_size)
        solver = BinPackingSolver(problem_input, 3, 90)
        chromosome_type = RealChromosome
        max_gen = 2
    elif (problem == "double_knapsack"):
        # DoubleKnapsackSolver(input, capacity1, capacity2)
        solver = DoubleKnapsackSolver(problem_input, 80, 40)
        chromosome_type = RealChromosome
    tester = Tester(problem)
    tester.test_fixed_input(solver=solver,
                            optimizations=10,
                            chromosome_type=chromosome_type,
                            min_gene=min_gen,
                            max_gene=max_gen)
    for _ in range(3):
        tester.test_increasing_input(solver,
                                    optimizations=5,
                                    chromosome_type=chromosome_type,
                                    iterations=4,
                                    increase_size=increase_size,
                                    size=4,
                                    range_numbers=range_numbers,
                                    min_gene=min_gen,
                                    max_gene=max_gen)

def main():
    random.seed(4269)
    problem = ""
    while (invalid_option(problem)):
        print("Select the problem to solve:\n   - subset_sum\n   - partition\
              \n   - bin_packing\n   - double_knapsack\n")
        problem = input()
        if (invalid_option(problem)):
            print("\n== INVALID OPTION ==\n")
    print("Select the range of numbers to implement for each element:")
    range_numbers = int(input())
    print("Select the amount of elements to implement in the problem:")
    amount = int(input())

    problem_input = [random.randint(1, range_numbers) for _ in range(0, amount)]
    selected_option(problem, problem_input, range_numbers)

if __name__ == '__main__':
    main()
