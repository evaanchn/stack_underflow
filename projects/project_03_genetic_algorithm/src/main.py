""" Copyright 2025 stack_underflow CC-BY 4.0 """
import sys
import random

from genetic_algorithm.chromosome import Chromosome
from genetic_algorithm.chromosome import BinaryChromosome
from genetic_algorithm.chromosome import RealChromosome
from genetic_algorithm.genetic_algorithm import GeneticAlgorithm
from problems.partition import make_partition_function

def sample_fitness_function(input, solution):
    # Example fitness: count of 1s for BinaryChromosome, sum of values for RealChromosome
    return sum(solution)

def make_subset_sum_function(input, target):
    def subset_sum_fitness(solution):
        paired = list(zip(input, solution))
        subset_sum = sum([value * sol for value, sol in paired])
        difference = abs(target - subset_sum)
        # Penalize difference
        return 1 / (1 + difference)
    return subset_sum_fitness

def main():
    # random.seed(42)

    input_data = [2, 10, 3, 8, 5, 7, 9, 5, 3, 2]
    # input_data = [1, 5, 11, 5, 6, 7, 8, 9, 10, 12, 13, 14, 15, 16]
    # input_data = [1, 3, 7, 15, 31, 63]  # imposible partition

    # target = 3
    population_size = 9
    max_generations = 2
    
    ga_binary = GeneticAlgorithm(
        population_size=population_size,
        max_generations=max_generations,
        min_gene_value=1,
        max_gene_value=7,
        fitness_function=make_partition_function(input_data),
        chromosome_type=RealChromosome,
        chromosome_length=len(input_data),
        elitism_percentage=0.1,
        crossover_prob=0.7,
        mutation_prob=0.1,
        parents_per_selection=4,
        parent_selection_type="TOURNAMENT",
    )

    print("=== Initializing Genetic Algorithm with BinaryChromosome ===")
    ga_binary.initialize_population()
    # print genetic algorithm population and fitnesses
    fitnesses = ga_binary.evaluate_fitness(ga_binary.population)
    for i, chromo in enumerate(ga_binary.population):
        print(f"Binary Chromosome {i + 1}: {chromo.genes}, Fitness: {fitnesses[i]}")

    print("\n=== Parents ===")
    parents = ga_binary.selection()
    fitnesses = ga_binary.evaluate_fitness(parents)
    for i, chromo in enumerate(parents):
        print(f"New Chromosome {i + 1}: {chromo.genes}, Fitness: {fitnesses[i]}")
        

if __name__ == '__main__':
    main()
