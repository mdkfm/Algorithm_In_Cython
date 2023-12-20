class Sample:
    def __init__(self, samples):
        if isinstance(samples, dict):
            self.samples = samples
            self.num = sum(samples.values())
        if isinstance(samples, list):
            self.samples = {}
            self.num = len(samples)
            for elem in samples:
                if elem in self.samples:
                    self.samples[elem] += 1
                else:
                    self.samples[elem] = 1


    def average(self):
        return sum([key * value for key, value in self.samples.items()]) / self.num

    def variance(self):
        return sum([value * (key - self.average()) ** 2 for key, value in self.samples.items()]) / (self.num - 1)

    def standard_deviation(self):
        return self.variance() ** 0.5


test = [1, 0, -1, 2, -1]
sample = Sample(test)
print(sample.average())
print(sample.variance())
