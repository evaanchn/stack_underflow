""" Copyright Stack Underflow 2025 CC-BY 4.0 """

class BinPacking:
    def __init__(self,
                 elements,
                 bins_count,
                 bins_size,
                 solution_count):
        self.elements = elements
        self.bins_count = bins_count
        self.bins_size = bins_size
        self.solution_count = solution_count

    @staticmethod
    def bin_packing_recursive(elements, bins, bins_size, index=0, used_bins=0):
        
        # reports a new solution after evaluating a possible combination
        if index == len(elements):
            # returns the bins with their values and used bins count
            return bins.copy(), used_bins

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
                    BinPacking.bin_packing_recursive(elements, new_bins,
                                                     bins_size, index + 1,
                                                     new_used_bins)

                # verifies which one is a better solution for the problem
                if (result_used_bins < min_used_bins):
                    min_used_bins = result_used_bins
                    best_bins = result_bins

        # returns an empty solution if no solution is found
        if best_bins is None:
            return [-1] * len(bins), float('inf')

        # returns the best solution of the problem
        return best_bins, min_used_bins

    @staticmethod
    def bin_packing_td(elements, bins, bins_size, index=0, used_bins=0,
                        memo=None):
        # checks if memo is empty or non initialized
        if memo == None:
            memo = {}
        
        # creates a unique key to save values in memo
        key = (index, tuple(sorted(bins)))

        # returns if the solution was already evaluated
        if key in memo:
            return memo[key]

        # reports a new solution after evaluating a possible combination
        if index == len(elements):
            # returns the bins with their values and used bins count
            return bins.copy(), used_bins

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
                    BinPacking.bin_packing_td(elements, new_bins,
                                                bins_size, index + 1,
                                                new_used_bins, memo)

                # verifies which one is a better solution for the problem
                if (result_used_bins < min_used_bins):
                    min_used_bins = result_used_bins
                    best_bins = result_bins

        # Guardamos el resultado en memo antes de retornar
        if best_bins is None:
            memo[key] = ([-1] * len(bins), float('inf'))
        else:
            memo[key] = (best_bins, min_used_bins)
        
        return memo[key]

    def solve_recursive(self):
        self.elements.sort(reverse=True)
        bins = [0] * self.bins_count
        return self.bin_packing_recursive(self.elements, bins, self.bins_size)

    def solve_td(self):
        self.elements.sort(reverse=True)
        bins = [0] * self.bins_count
        return self.bin_packing_td(self.elements, bins, self.bins_size)
