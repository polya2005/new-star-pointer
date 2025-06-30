from struct import Struct
import numpy as np


class BallNode:
    binary_format = Struct("3d d h h h ? x")

    def __init__(
        self, center, radius, left=None, right=None, index=None, is_leaf=False
    ):
        self.center = center
        self.radius = radius
        self.left = left
        self.right = right
        self.index = index  # original index of the point (for leaves)
        self.is_leaf = is_leaf

    def pack(self):
        """
        Packs the node into a binary format.
        """
        return self.binary_format.pack(
            *self.center,
            self.radius,
            self.left or -1,
            self.right or -1,
            self.index or -1,
            self.is_leaf
        )

    def __repr__(self):
        return (
            f"BallNode(center={self.center}, radius={self.radius}, "
            f"left={self.left}, right={self.right}, index={self.index}, "
            f"is_leaf={self.is_leaf})"
        )


class BallTree3D:
    def __init__(self, points):
        points = np.array(points)
        norms = np.linalg.norm(points, axis=1, keepdims=True)
        self.points = points / norms  # normalize all points
        self.indices = np.arange(len(points))  # original indices
        self.nodes = []
        self.root = self._build(0, len(self.points))

    def _build(self, start, end):
        if end - start == 1:
            center = self.points[start]
            orig_idx = self.indices[start]
            node = BallNode(center=center, radius=0.0, index=orig_idx, is_leaf=True)
            self.nodes.append(node)
            return len(self.nodes) - 1

        # Compute spherical centroid and normalize
        center = np.mean(self.points[start:end], axis=0)
        center /= np.linalg.norm(center)

        # Compute max angular distance (radius)
        dot_products = np.clip(np.dot(self.points[start:end], center), -1.0, 1.0)
        angles = np.arccos(dot_products)
        radius = np.max(angles)

        # Split direction
        direction = self.points[start] - self.points[end - 1]
        direction /= np.linalg.norm(direction)

        # Partition by dot product with the direction
        mid = (start + end) // 2
        dot_proj = np.dot(self.points[start:end], direction)
        sorted_idx = np.argsort(dot_proj)
        self.points[start:end] = self.points[start:end][sorted_idx]
        self.indices[start:end] = self.indices[start:end][sorted_idx]

        left = self._build(start, mid)
        right = self._build(mid, end)

        node = BallNode(center=center, radius=radius, left=left, right=right)
        self.nodes.append(node)
        return len(self.nodes) - 1

    def nearest_neighbor(self, query):
        self.best_index = -1
        self.best_similarity = -2.0
        query = query / np.linalg.norm(query)
        self._search(self.root, query)
        return self.best_index

    def _search(self, node_idx, query):
        node = self.nodes[node_idx]
        sim = np.dot(query, node.center)

        if node.is_leaf:
            if sim > self.best_similarity:
                self.best_similarity = sim
                self.best_index = node.index  # original index
            return

        angle = np.arccos(np.clip(sim, -1.0, 1.0))
        if angle > node.radius and sim < self.best_similarity:
            return

        left_sim = np.dot(query, self.nodes[node.left].center)
        right_sim = np.dot(query, self.nodes[node.right].center)

        if left_sim > right_sim:
            self._search(node.left, query)
            self._search(node.right, query)
        else:
            self._search(node.right, query)
            self._search(node.left, query)
