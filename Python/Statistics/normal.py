import numpy as np

c = 1 / np.sqrt(2 * np.pi)


def normal(x, mu, sigma):
    return c / sigma * np.exp(-(x - mu) ** 2 / (2 * sigma ** 2))


def normal_distribution(mu, sigma):
    return lambda x: normal(x, mu, sigma)


def integrate(f, a, b):
    dx = 0.00001
    x = np.arange(a, b, dx)
    f_x = f(x)
    return np.sum(f_x * dx)


result = integrate(normal_distribution(0, 1), 0.00, 3.03)
result = 0.5 + result
print(result)
