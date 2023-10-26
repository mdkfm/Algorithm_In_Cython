import numpy as np


# class DecisionTree:
#     def __cinit__(self):

def entropy(int[:] dataset) -> double:
    cdef int[:] np_dataset = np.asarray(dataset)
    cdef int total = np_dataset.shape[0]
    cdef double[:] count = np.bincount(np_dataset.ravel()) / total
    cdef int i = 0
    cdef double result = 0.0
    for i in range(count.shape[0]):
        result += count[i] * np.log2(count[i]) if count[i] != 0 else 0
    return result


cdef class Node:
    cdef bint leaf
    cdef int label
    cdef int feature
    def __init__(self, bint leaf=True, int label=None, int feature=None):
        self.leaf = leaf
        self.label = label
        self.feature = feature
        self.tree = {}
        # self.result = {'label:': self.label, 'feature': self.feature, 'tree': self.tree}

    def __repr__(self):
        return '{}'.format(self.result)

    def add_node(self, val, node):
        self.tree[val] = node

    def predict(self, features):
        if self.leaf is True:
            return self.label
        return self.tree[features[self.feature]].predict(features)



cdef class ClassificationDTree:
    cdef int n_features
    cdef int n_class
    def __cinit__(self, int n_features, int n_class):
        self.n_features = n_features
        self.n_class = n_class


