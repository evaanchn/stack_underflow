""" Program purpose """
import sys
import random

from genetic_algorithm.chromosome import Chromosome
from genetic_algorithm.chromosome import BinaryChromosome
from genetic_algorithm.chromosome import RealChromosome

def main():
    #random.seed(42)  # For reproducible results
    length = 5
    crossover_prob = 0.7

    # === Binary Chromosomes ===
    binary_parents = [BinaryChromosome(length) for _ in range(4)]
    for i, parent in enumerate(binary_parents):
        parent.initialize()
        print(f"Binary Parent {i + 1}:", parent.genes, "\n")
    binary_child = Chromosome.crossover(binary_parents, crossover_prob, BinaryChromosome)
    print("Binary Child before mutation:", binary_child.genes, "\n")
    binary_child.mutate()
    print("Binary Child after mutation:", binary_child.genes, "\n")

    print()

    # === Real Chromosomes ===
    real_parents = [RealChromosome(length) for _ in range(4)]
    for i, parent in enumerate(real_parents):
        parent.initialize()
        print(f"Real Parent {i + 1}:", parent.genes, "\n")

    real_child = Chromosome.crossover(real_parents, crossover_prob, RealChromosome)
    print("Real Child before mutation:", real_child.genes, "\n")
    real_child.mutate()
    print("Real Child after mutation:", real_child.genes, "\n")

if __name__ == '__main__':
    main()
