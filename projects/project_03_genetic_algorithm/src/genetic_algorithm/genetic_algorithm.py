# Copyright 2025 stack_underflow CC-BY 4.0

import random
from chromosome import Chromosome

class GeneticAlgorithm:
    def __init__(
                self,
                input,
                population_size,
                max_generations,
                fitness_function,
                chromosome_type,
                elitism_percentage = 0.0,
                max_fails = float('inf'),
                parents_per_selection = 2,
                parent_selection_type = "RANKING",
                crossover_prob = 0.6,
                mutation_prob = 0.1):
        """ Input from which algorithm will be working with """
        self.input = input
        """ Set of possible solutions """
        self.population = []
        """ Amount of cromosomes in population """
        self.population_size = population_size

        """ Amount of generations to create """
        self.max_generations = max_generations
        """ Determines fitness of a cromosome """
        self.fitness_function = fitness_function
        """" Amount of elites to keep around """
        self.elites_count = round(self.population_size * elitism_percentage)
        """ Binary, real or permutation chromosome """
        self.chromosome_type = chromosome_type
        """ Max amount of generations without improvements """
        self.max_fails = max_fails
        """ Amount of parents to consider in a selection """
        self.parents_per_selection = parents_per_selection
        
        """ Ranking, Roulette or Tournament """
        self.parent_selection_type = parent_selection_type

        self.crossover_prob = crossover_prob
        self.mutation_prob = mutation_prob

    def create_chromosome(self):
        """
        Create with designated chromosome type, len of each is length of input
        """
        chromosome = self.chromosome_type(len(self.input))
        chromosome.initialize()
        return chromosome

    def initialize_population(self):
        """ Fill list with new chromosomes """
        self.population = [self.create_chromosome()
                           for _ in range(self.population_size)]

    def evaluate_fitness(self, chromosomes):
        return [self.fitness_func(self.input, chrom.genes)
                 for chrom in chromosomes]

    def sort_by_fitness(self, chromosomes):
        # Extract top N chromosomes
        fitness_values = self.evaluate_fitness(chromosomes)

        # Pair each chromosome with its fitness
        paired = list(zip(self.population, fitness_values))

        # Sort by fitness descending
        paired.sort(key=lambda pair: pair[1], reverse=True)

        return [chrom for chrom, _ in paired]  # Return sorted chromosomes only

    def pick_best_chromosomes(self, chromosomes, amount):
        if amount == 0: return []
        return self.sort_by_fitness(chromosomes)[:amount]
    
    def ranking(self):   
        return self.pick_best_chromosomes(self.population,
                                          self.parents_per_selection)

    def roulette(self):
        fitness_values = self.evaluate_fitness()
        # chromosomes =  self.population
        # Pair each chromosome with its fitness
        paired = list(zip(self.population, fitness_values))
        selected =  []    
        for pair in paired:
            if (random.uniform([0, 1]) < pair[1]):
                selected.append(pair[0])
                sel
        
        return selected

    def tournament(self):
        pass

    def selection(self):
        if (self.parent_selection_type == "RANKING"):
            return self.ranking()
        elif (self.parent_selection_type == "ROULETTE"):
            return self.roulette()
        elif (self.parent_selection_type == "TOURNAMENT"):
            return self.tournament()

    def elitism(self):
        return self.pick_best_chromosomes(self.population, self.elites_count)
    
    def reproduce(self, children_count):
        children = []
        for _ in range(children_count):
            best_parents = self.selection()
            child = Chromosome.crossover(best_parents, self.crossover_prob,
                                         self.chromosome_type)
            if (random.uniform([0, 1]) < self.mutation_prob):
                child.mutate()
            children.append(child)
        return children
    
    def generation_evolved(self, children):
        # If max fitness of current population is lower than the max fitness
        # of the children, then new generation truly evolved
        return max(self.evaluate_fitness(self.population)) < max(
            self.evaluate_fitness(children))

    def evolve(self):   
        """! Creates a new generation of chromosomes based on prev population

        @return True if at least one new child was better than the best 
            chromosome in the last generation.
        """
        evolved = True
    
        new_population = self.elitism()  # First add elites, if any
        # Calculate remaining children to reproduce
        children_count = self.population_size - len(new_population)
        children = self.reproduce(children_count)

        # compare self population and new children
        if self.max_fails != float('inf'):
            evolved = self.generation_evolved(children)
        
        self.population = new_population.extend(children)  # Add children 

        return evolved

    def run(self):
        fails = 0
        # Create each generation
        for _ in range(self.max_generations):
            evolved = self.evolve()
            # If max fails attribute was set
            if self.max_fails != float('inf'):
                if not evolved:
                    fails += 1
                else:
                    fails = 0  # Reset consecutive fails

                if fails >= self.max_fails:
                    break
