import numpy as np
cimport numpy as cnp

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
    cdef dict[int, Node] tree
    cdef dict result
    def __init__(self, bint leaf=0, int label=0, int feature=0):
        self.leaf = leaf
        self.label = label
        self.feature = feature
        self.tree = {}
        self.result = {'label:': self.label, 'feature': self.feature, 'tree': self.tree}

    def __repr__(self):
        return '{}'.format(self.result)

    def add_node(self, val, node):
        self.tree[val] = node

    def predict(self, cnp.ndarray[int, ndim=1] features):
        if self.leaf:
            return self.label
        return self.tree[features[self.feature]].predict(features)


cdef class ID3Tree:
    cdef int n_features
    cdef int n_class
    cdef Node tree
    def __cinit__(self, int n_features, int n_class):
        self.n_features = n_features
        self.n_class = n_class
        self.tree = None

    def info_gain(self, cnp.ndarray[int, ndim=2] datasets, int feature=0):
        cdef int length, i, feature_class
        cdef cnp.ndarray[int, ndim=2] count
        cdef double result

        length = datasets.shape[0]
        feature_class = np.unique(datasets[:, feature]).shape[0]
        count = np.zeros((feature_class, self.n_class))
        for i in range(length):
            feature_value = datasets[i, feature]
            value = datasets[i, -1]
            count[feature_value, value] += 1

        ent = np.sum(count, axis=1) / length
        ent = np.sum(-ent * np.log2(ent + 1e-8))
        cond_ent = - 1 / length * np.sum( \
            count * \
            np.log2(count / np.sum(count, axis=0, keepdims=True) + 1e-8))
        return ent - cond_ent

    def fit(self, datasets):
        datasets = np.asarray(datasets, dtype=np.int32)
        self.tree = self._fit(datasets, np.ones(self.n_features, dtype=np.int32))
        return self

    def _fit(self, cnp.ndarray[int, ndim=2] datasets, cnp.ndarray[int, ndim=1] used_features):
        cdef int i, length, best_feature, best_feature_class
        cdef cnp.ndarray[long, ndim=1] count
        cdef cnp.ndarray[long, ndim=2] child_datasets
        used_features = np.copy(used_features)

        cdef double max_info_gain, info_gain
        cdef Node node, child_node

        length = datasets.shape[0]
        count = np.bincount(datasets[:, -1])
        if count.shape[0] == 1:
            return Node(leaf=True, label=count[0])

        max_info_gain = 0
        for i in range(self.n_features):
            if used_features[i]:
                continue
            info_gain = self.info_gain(datasets, i)
            if info_gain > max_info_gain:
                max_info_gain = info_gain
                best_feature = i
                best_feature_class = np.unique(datasets[:, i]).shape[0]

        node = Node(leaf=False, feature=best_feature)
        used_features[best_feature] = 1
        for i in range(best_feature_class):
            child_datasets = datasets[np.where(datasets[:, best_feature] == i)]
            child_node = self._fit(child_datasets, used_features)
            node.add_node(i, child_node)
        return node

    def predict(self, features):
        features = np.asarray(features, dtype=np.int32)
        return self.tree.predict(features)