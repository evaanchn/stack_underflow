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
    def space_bins_optimized(old_bins, new_bins, bins_size):
        if old_bins is None:
            return True

        def space_remaining(bins):
            return sum(bins_size - b for b in bins if b > 0)

        return space_remaining(new_bins) < space_remaining(old_bins)


    @staticmethod
    def bin_packing_recursive(elements, bins, bins_size, index=0, used_bins=0, solution_count=None):
        if solution_count is None:
            solution_count = [0]

        if index == len(elements):
            solution_count[0] += 1
            print(f"Solución #{solution_count[0]}: used_bins={used_bins}, bins={bins}")
            return bins.copy(), used_bins

        best_bins = None
        min_used_bins = float('inf')

        for bin_index in range(len(bins)):
            if bins[bin_index] + elements[index] <= bins_size:
                new_bins = bins.copy()
                new_used_bins = used_bins

                if new_bins[bin_index] == 0:
                    new_used_bins += 1
                new_bins[bin_index] += elements[index]

                result_bins, result_used_bins = BinPacking.bin_packing_recursive(
                    elements, new_bins, bins_size, index + 1, new_used_bins, solution_count
                )

                if (result_used_bins < min_used_bins or
                    (result_used_bins == min_used_bins and
                    BinPacking.space_bins_optimized(best_bins, result_bins, bins_size))):
                    min_used_bins = result_used_bins
                    best_bins = result_bins

        if best_bins is None:
            return [-1 for _ in bins], float('inf')

        return best_bins, min_used_bins

    def solve_recursive(self):
        self.elements.sort(reverse=True)
        bins = [0 for i in range(self.bins_count)]
        return self.bin_packing_recursive(self.elements, bins, self.bins_size,
                                        used_bins=0, solution_count = self.solution_count)

elements = [2, 5, 4, 7, 1, 3]
bins_count = 5
bins_size = 10
solution_count = [0]
test = BinPacking(elements, bins_count, bins_size, solution_count)
print(f"Found best at {test.solve_recursive()}. Solutions: {solution_count[0]}")
