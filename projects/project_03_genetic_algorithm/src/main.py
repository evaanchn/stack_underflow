""" Program purpose """
import sys
import random

from genetic_algorithm.chromosome import Chromosome
from genetic_algorithm.chromosome import BinaryChromosome
from genetic_algorithm.chromosome import RealChromosome
from genetic_algorithm.genetic_algorithm import GeneticAlgorithm

def sample_fitness_function(input, solution):
    # Example fitness: count of 1s for BinaryChromosome, sum of values for RealChromosome
    return sum(solution)

def make_subset_sum_function(target):
    def subset_sum_fitness(input, solution):
        paired = list(zip(input, solution))
        subset_sum = sum([value * sol for value, sol in paired])
        difference = abs(target - subset_sum)
        # Penalize difference
        return 1 / (1 + difference)
    return subset_sum_fitness

def main():
    # random.seed(42)

    #input_data = [0] * 10  # Dummy input to set chromosome length
    input_data = [2, 2, 2, 2, 1, 10]
    target = 3
    population_size = 6
    max_generations = 20

    print("=== Initializing Genetic Algorithm with BinaryChromosome ===")
    ga_binary = GeneticAlgorithm(
        input=input_data,
        population_size=population_size,
        max_generations=max_generations,
        fitness_function=make_subset_sum_function(target),
        chromosome_type=BinaryChromosome,
        elitism_percentage=0.2,
        crossover_prob=0.7,
        mutation_prob=0.1
    )
    
    ga_binary.initialize_population()

    fitnesses = ga_binary.evaluate_fitness(ga_binary.population)
    # print genetic algorithm population and fitnesses
    for i, chromo in enumerate(ga_binary.population):
        print(f"Binary Chromosome {i + 1}: {chromo.genes}, Fitness: {fitnesses[i]}")

if __name__ == '__main__':
    main()
