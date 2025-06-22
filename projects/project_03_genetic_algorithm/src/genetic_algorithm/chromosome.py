# Copyright 2025 stack_underflow CC-BY 4.0

import random

class Chromosome:
    """ @brief Abstract chromosome class with length and genes vector """
    def __init__(self, length):
        self.length = length
        self.genes = []

    def initialize(self):
        raise NotImplementedError

    @staticmethod
    def crossover(parents, crossover_probability, chromosome_class=None):
        if not parents or len(parents) < 1:
            raise ValueError("At least one parent is required")

        length = parents[0].length
        if any(p.length != length for p in parents):
            raise ValueError("All parents must have the same chromosome length")

        # Determine class to instantiate for the child
        if chromosome_class is None:
            chromosome_class = type(parents[0])

        child = chromosome_class(length)
        child.genes = []

        for gene_idx in range(length):
            gene = parents[0].genes[gene_idx]  # Default from first parent
            if random.random() < crossover_probability:
                gene = random.choice(parents).genes[gene_idx]
            child.genes.append(gene)

        return child

    def mutate(self):
        raise NotImplementedError


class BinaryChromosome(Chromosome):
    def initialize(self):
        self.genes = [random.choice([0, 1]) for _ in range(self.length)]

    def mutate(self):
        # First get a random gene index
        i = random.randint(0, self.length - 1)
        # Then flip bit
        self.genes[i] ^= 1

# TODO(any): Add min and max gene
class RealChromosome(Chromosome):
    def __init__(self, length, min_gene, max_gene):
        super.__init__(length)
        self.min_gene = min_gene
        self.max_gene = max_gene

    def initialize(self):
        self.genes = [random.uniform([self.min_gene, self.max_gene])
                      for _ in range(self.length)]

    def mutate(self):
        i = random.randint(0, self.length - 1)
        self.genes[i] += random.gauss(0, 0.1)  # Gaussian noise

# TODO(us) Implement crossover for permutation
class PermutationChromosome(Chromosome):
    def initialize(self):
        self.genes = list(range(self.length))
        random.shuffle(self.genes)  # Perrmutation

    def mutate(self):
        # Mutation for permutation is to swap two
        i, j = random.sample(range(self.length), 2)  # get positions
        self.genes[i], self.genes[j] = self.genes[j], self.genes[i]  # swap
    
