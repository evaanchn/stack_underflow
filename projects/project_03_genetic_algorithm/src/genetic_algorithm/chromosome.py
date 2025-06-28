""" Copyright 2025 stack_underflow CC-BY 4.0 """

import random

class Chromosome:
    """ @brief Abstract chromosome class with length and genes vector """
    def __init__(self, length, min_gene_val = 0, max_gene_val = 1):
        self.length = length
        self.genes = [0] * length
        self.min_gene_val = min_gene_val
        self.max_gene_val = max_gene_val

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

        child = chromosome_class(length, parents[0].min_gene_val,
                                 parents[0].max_gene_val)
        child.genes = []

        for gene_idx in range(length):
            gene = parents[0].genes[gene_idx]  # Default from first parent
            if random.random() < crossover_probability:
                # Choose gene from parent that is not first chromosome
                other_parent = random.choice(parents[1:])
                gene = other_parent.genes[gene_idx]
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

class RealChromosome(Chromosome):
    def initialize(self):
        if type(self.min_gene_val) == int and type(self.max_gene_val) == int:
            self.genes = [random.randint(self.min_gene_val, self.max_gene_val)
                          for _ in range(self.length)]
        else:
            self.genes = [random.uniform(self.min_gene_val,
                                         self.max_gene_val)
                                         for _ in range(self.length)]

    def mutate(self):
        i = random.randint(0, self.length - 1)
        if type(self.min_gene_val) == int and type(self.max_gene_val) == int:
            other_genes = list(range(self.min_gene_val, self.max_gene_val + 1))
            other_genes.remove(self.genes[i])
            self.genes[i] = random.choice(other_genes)
        else:
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
