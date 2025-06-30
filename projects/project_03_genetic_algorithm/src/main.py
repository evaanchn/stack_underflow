""" Copyright 2025 stack_underflow CC-BY 4.0 """
import sys
import random

from problems.subset_sum import SubsetSumSolver
from genetic_algorithm.genetic_algorithm import GeneticAlgorithm
from genetic_algorithm.chromosome import BinaryChromosome
from genetic_algorithm.chromosome import RealChromosome
from genetic_algorithm.ga_optimizer import GAOptimizer
from tester.tester import Tester

def main():
    random.seed(4269)
    input = [random.randint(1, 21) for _ in range(0,21)]
    
    subset = SubsetSumSolver(input, 10)
    tester = Tester("Subset Sum")
    tester.test_fixed_input(solver=subset,
                            optimizations=10,
                            chromosome_type=BinaryChromosome)
    tester.test_increasing_input(subset,
                                 optimizations=10,
                                 chromosome_type=BinaryChromosome,
                                 iterations=4,
                                 increase_size=4,
                                 size=4)

if __name__ == '__main__':
    main()