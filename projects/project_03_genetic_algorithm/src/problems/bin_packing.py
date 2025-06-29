""" Copyright Stack Underflow 2025 CC-BY 4.0 """

from problems.solver import Solver
from problems.solution_log import SolutionLog

class BinPackingSolver(Solver):
    def __init__(self, input, bins_count, bin_size):
        super().__init__(input)
        self.bins_count = bins_count
        self.bin_size = bin_size
        self.fitness_function = self.create_fitness_function()

    @staticmethod
    def bin_packing_recursive(input, bins, bins_size, index=0, bins_used=0,
                              log=SolutionLog()):
        log.log_iteration()

        # reports a new solution after evaluating a possible combination
        if index == len(input):
            # returns the bins with their values and amount of bins used
            return bins.copy(), bins_used

        best_bins = None
        min_bins_used = float('inf')

        # evaluates all available bins and attempts to allocate new input
        for bin_index in range(len(bins)):
            # checks if an element can be assigned to a container
            if bins[bin_index] + input[index] <= bins_size:
                new_bins = bins.copy()
                new_bins_used = bins_used

                # checks if it's using a new bin
                if new_bins[bin_index] == 0:
                    new_bins_used += 1
                new_bins[bin_index] += input[index]

                # try to assign new input and look for new solutions
                result_bins, result_bins_used = \
                    BinPackingSolver.bin_packing_recursive(input, new_bins,
                                                     bins_size, index + 1,
                                                     new_bins_used, log)

                # verifies which one is a better solution for the problem
                if (result_bins_used < min_bins_used):
                    min_bins_used = result_bins_used
                    best_bins = result_bins

        # returns the best solution of the problem
        return best_bins, min_bins_used

    @staticmethod
    def bin_packing_td(elements, bins, bins_size, memo, index=0, used_bins=0,
                       log=SolutionLog()):
        log.log_iteration()

        # reports a new solution after evaluating a possible combination
        if index == len(elements):
            # returns the bins with their values and used bins count
            return bins.copy(), used_bins

        # creates a unique key to save values in memo
        key = (index, tuple(sorted(bins)))

        # returns if the solution was already evaluated
        if key in memo:
            return memo[key]

        best_bins = None
        min_used_bins = float('inf')

        # evaluates all available bins and attempts to allocate new elements
        for bin_index in range(len(bins)):
            # checks if an element can be assigned to a container
            if bins[bin_index] + elements[index] <= bins_size:
                new_bins = bins.copy()
                new_used_bins = used_bins

                # checks if it's using a new bin
                if new_bins[bin_index] == 0:
                    new_used_bins += 1
                new_bins[bin_index] += elements[index]

                # try to assign new elements and look for new solutions
                result_bins, result_used_bins = \
                    BinPackingSolver.bin_packing_td(elements, new_bins,
                                                bins_size, memo, index + 1,
                                                new_used_bins, log)

                # verifies which one is a better solution for the problem
                if (result_used_bins < min_used_bins):
                    min_used_bins = result_used_bins
                    best_bins = result_bins

        memo[key] = (best_bins, min_used_bins)

        return memo[key]

    def solve_recursive(self, log):
        self.input.sort(reverse=True)
        bins = [0] * self.bins_count
        return self.bin_packing_recursive(self.input, bins, self.bin_size,
                                          log=log)

    def solve_dynamic_top_down(self, log):
        self.input.sort(reverse=True)
        bins = [0] * self.bins_count
        memo = {}
        return self.bin_packing_td(self.input, bins, self.bin_size, memo,
                                   log=log)

    def solve_genetic(self, genetic_algorithm, log):
        solution_chromosome = genetic_algorithm.run(log)
        solution_genes = solution_chromosome.genes
        # Avoid returning 
        if self.fitness_function(solution_genes) == 0: return None, 0

        bin_ids = set(solution_genes)  # Extract the bin id's
        best_bins = [0] * self.bins_count  # Initialize empty bins
        # Fill bins with sums, in corresponding spaces
        for bin_id in bin_ids:
            best_bins[bin_id] = sum([self.input[i] for i in range(len(self.input))
                                    if solution_genes[i] == bin_id])
        best_bins.sort(reverse=True)
        return best_bins, len(bin_ids)

    def create_fitness_function(self):
        """ Create a fitness function for real chromosomes (min = 0, 
            max = bins_count), each gene symbolizes a bin id """
        def fitness_function(solution):
            # Create a set with the ids of the bins used
            bin_ids = set(solution)

            # Check if bin size was surpassed, checking each bin ID
            for bin_id in bin_ids:
                # If sum of the input in input exceed bin size/capacity
                if sum([self.input[i] for i in range(len(self.input))
                        if solution[i] == bin_id]) > self.bin_size:
                    # Discourage reproducing the solution
                    return 0

            # Count how many bins were used
            bins_used = len(bin_ids)
            # bins_used should never be 0
            if bins_used == 0: raise AssertionError("0 bins used in gen al")
            # Minimization problem
            return 1 / bins_used
        return fitness_function
