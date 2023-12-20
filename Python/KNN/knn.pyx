from collections import Counter
from queue import PriorityQueue
import numpy as np
cimport numpy as cnp


cdef class Neighbor:
    cdef double distance
    cdef cnp.ndarray value
    def __cinit__(self, cnp.ndarray value, double dis):
        self.value = value
        self.distance = dis
    
    property distance:
        def __get__(self):
            return self.distance
        
    property value:
        def __get__(self):
            return self.value

    def __lt__(self, Neighbor other):
        return self.distance > other.distance

cdef class KDNode:
    cdef cnp.ndarray value
    cdef KDNode leftchild
    cdef KDNode rightchild
    def __cinit__(self, cnp.ndarray value, KDNode left=None, KDNode right=None):
        # value concludes features and labels
        self.value = value
        self.leftchild = left
        self.rightchild = right

class NeighborQueue(PriorityQueue):

    def __init__(self, cnp.ndarray point, int maxsize, int num_features):
        super().__init__(maxsize)
        self.num_features = num_features
        self.point = point

    def update(self, KDNode node):
        item = Neighbor(node.value, self._distance(node))

        if not self.full():
            self.put(item)
        elif self.queue[0].distance > item.distance:
            self.get()
            self.put(item)

    def _distance(self, KDNode node):
        """计算两个结点之间的距离"""
        coordinates = node.value[:self.num_features]
        return np.sqrt(np.sum(np.square(coordinates - self.point))).astype(np.float64)



cdef class KDTree:
    cdef cnp.ndarray _data
    cdef KDNode kdtree
    cdef int _num_features
    def __cinit__(self, cnp.ndarray data, int num_features):
        self._data = data
        self._num_features = num_features
        self.kdtree = self.create_kdtree(data)
    
    def create_kdtree(self, cnp.ndarray data, int depth=0):
        # 3.2.3: until no point
        if data.shape[0] == 0:
            return None
        # 3.2.2: choose the aixs
        l = depth % (data.shape[1] - 1)
        # sort along the chose axis
        data = data[data[:, l].argsort()]
        # 3.2.1: choose the median point as split point
        median_index = data.shape[0] // 2
        return KDNode(
            data[median_index], # value
            self.create_kdtree(data[:median_index], depth + 1), # leftchild
            self.create_kdtree(data[median_index + 1:], depth + 1) # rightchild
        )
    
    def query(self, cnp.ndarray point, int k=1) -> list[Neighbor]:
        queue = NeighborQueue(point, k, self._num_features)
        self._search(point, queue, 0, self.kdtree)
        return queue.queue
    
    def _search(self, cnp.ndarray point, queue, int depth = 0, KDNode tree=None):
        """
        Search the k min distance nodes.

        ///
        point: one dimension ndarray
        queue: the searched alternative k neighbors
        depth: the searching depth
        """
        n = point.shape[0]
        if tree is None:
            return

        value = point[depth % n]
        bound = tree.value[depth % n]
        # 递归地向下访问kd树
        if value < bound:
            next_branch, other_branch = tree.leftchild, tree.rightchild
        else:
            next_branch, other_branch = tree.rightchild, tree.leftchild

        if next_branch is None:
            queue.update(tree)
            return

        # (3)(b)检查另一子结点对应的区域是否相交
        self._search(point, queue, depth = depth + 1, tree = next_branch)

        # 计算目标点与切分点形成的分割超平面的距离
        temp_dist = abs(bound - value)

        if not (queue.queue[0].distance < temp_dist and queue.full()):
            # 如果相交，递归地进行近邻搜索
            # (3)(a) 判断当前结点，并更新当前k近邻点集
            queue.update(tree)
            self._search(point, queue, depth = depth + 1, tree = other_branch)


class KNN:
    def __init__(self, X_train, y_train, n_neighbors=3, p=2):
        """
        parameter: n_neighbors
        parameter: p distance metric
        """
        self.n = n_neighbors
        self.p = p
        self.num_features = X_train.shape[1]
        self.num_labels = y_train.shape[1]
        data = np.concatenate([X_train, y_train], axis=1)
        self.KDTree = KDTree(data, X_train.shape[1])

    def predict(self, X):
        # get n nearest neighbors
        cdef int i
        cdef int j

        if X.ndim == 1:
            X = X.reshape(1, -1)

        cdef cnp.ndarray result = np.zeros((X.shape[0], self.num_labels))
        for i in range(X.shape[0]):
            neighbors = self.KDTree.query(X[i].reshape(-1), k=self.n)
            # get the most common class label
            knn = np.concatenate([n.value[self.num_features:].reshape(1, -1) for n in neighbors], axis=0)
            for j in range(self.num_labels):
                result[i, j] = Counter(knn[:, j]).most_common(1)[0][0]
        return result

    def score(self, X_test, y_test):
        right_count = 0
        for X, y in zip(X_test, y_test):
            label = self.predict(X.reshape(-1))
            if label == y:
                right_count += 1
        return right_count / len(X_test)