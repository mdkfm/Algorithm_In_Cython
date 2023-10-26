import numpy as np
cimport numpy as cnp

cdef class GaussianNB:
    """
    Gaussian Navie Bayes for classification task
    """
    cdef int num_features
    cdef int num_class
    cdef cnp.ndarray model
    def __init__(self, int num_features, int num_class):
        self.num_features = num_features
        self.num_class = num_class
        self.model = np.ones((num_class, num_features, 2), dtype=np.float64)

    property num_features:
        def __get__(self):
            return self.num_features

    property num_class:
        def __get__(self):
            return self.num_class

    # Gaussian distribution
    def gaussian(self, cnp.ndarray x, double mean, double std):
        # log Gaussian
        # output shape (num_samples, )
        return (x - mean) ** 2 / (2 * std ** 2) +  np.log(std + 0.1)

    # Get the coefficient of sub-model
    def fit(self, cnp.ndarray x, cnp.ndarray y):
        # x shape: (num_samples, num_features)
        # y shape: (num_samples, 1), must encode
        cdef int i

        if np.unique(y).shape[0] != self.num_class:
            raise ValueError("The num of classes is not matched")
        if x.shape[1] != self.num_features:
            raise ValueError("The num of features is not matched")

        for i in range(self.num_class):
            self.model[i, :, 0] = x[(y == i).ravel(), :].mean(axis=0)
            self.model[i, :, 1] = x[(y == i).ravel(), :].std(axis=0)
        return 'gaussianNB train done!'

    def calculate_probabilities(self, cnp.ndarray input_data):
        # input_data shape (num_samples, num_features)
        cdef cnp.ndarray probabilities = np.zeros((input_data.shape[0], self.num_class))
        cdef int label
        cdef int feature
        for label in range(self.num_class):
            for feature in range(self.num_features):
                probabilities[:, label] += self.gaussian(
                    input_data[:, feature],
                    self.model[label, feature, 0],
                    self.model[label, feature, 1]
                )
        return probabilities

    # Category
    def predict(self, cnp.ndarray x_test):
        return self.calculate_probabilities(x_test).argmin(axis=1)

    def score(self, cnp.ndarray x_test, cnp.ndarray y_test):
        cdef cnp.ndarray result = self.predict(x_test)
        if y_test.ndim != 1:
            y_test = y_test.ravel()
        cdef int right = (result == y_test).sum()
        return right / x_test.shape[0]