""" Copyright 2025 stack_underflow CC-BY 4.0 """
import time

class SolutionLog:
    def __init__(self):
        self.iterations = 0
        self.start_time = time.time()
        self.finish_time = time.time()
        self.solution = None

    def log_iteration(self, iterations=1):
        self.iterations = self.iterations + iterations

    def record_start(self):
        self.start_time = time.perf_counter()

    def record_finish(self):
        self.finish_time = time.perf_counter()

    def get_duration(self):
        if self.start_time is not None and self.finish_time is not None:
            return (self.finish_time - self.start_time) * 1000  # milliseconds
        return 0.0

    def to_string(self):
        return f"Iterations: {self.iterations} | Duration: {self.get_duration():0f} ms"

