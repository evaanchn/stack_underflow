""" Program purpose """
import sys
import random

from genetic_algorithm.chromosome import Chromosome
from genetic_algorithm.chromosome import BinaryChromosome
from genetic_algorithm.chromosome import RealChromosome

def main():
    random.seed(42)  # For reproducible results

    length = 10
    crossover_prob = 0.7

    # Initialize binary chromosomes
    binary_parent1 = BinaryChromosome(length)
    binary_parent2 = BinaryChromosome(length)
    binary_parent1.initialize()
    binary_parent2.initialize()

    print("Binary Parent 1:", binary_parent1.genes)
    print("Binary Parent 2:", binary_parent2.genes)

    binary_child = Chromosome.crossover([binary_parent1, binary_parent2], crossover_prob, BinaryChromosome)
    print("Binary Child before mutation:", binary_child.genes)
    binary_child.mutate()
    print("Binary Child after mutation:", binary_child.genes)

    print()

    # Initialize real chromosomes
    real_parent1 = RealChromosome(length)
    real_parent2 = RealChromosome(length)
    real_parent1.initialize()
    real_parent2.initialize()

    print("Real Parent 1:", real_parent1.genes)
    print("Real Parent 2:", real_parent2.genes)

    real_child = Chromosome.crossover([real_parent1, real_parent2], crossover_prob, RealChromosome)
    print("Real Child before mutation:", real_child.genes)
    real_child.mutate()
    print("Real Child after mutation:", real_child.genes)

if __name__ == '__main__':
    main()
