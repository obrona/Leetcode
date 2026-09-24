
# double dfs technique.

class Solution:
    def __init__(self):
        self.n = 0
        self.num_nodes: list[int] = []
        self.sum_paths: list[int] = []
        self.adj: list[list[int]] = []

    def dfs1(self, curr: int, parent: int):
        num_node = 1
        sum_path = 0
        for c in self.adj[curr]:
            if c == parent:
                continue
            self.dfs1(c, curr)

            num_node += self.num_nodes[c]
            sum_path += self.sum_paths[c] + self.num_nodes[c]

        self.num_nodes[curr] = num_node
        self.sum_paths[curr] = sum_path

    def dfs2(self, curr: int, parent: int):
        if curr != parent:
            parent_sum = self.sum_paths[parent]

            to_add_node = self.n - self.num_nodes[curr]
            to_add_path = parent_sum - self.sum_paths[curr] - self.num_nodes[curr]

            self.sum_paths[curr] += to_add_node + to_add_path

        for c in self.adj[curr]:
            if c == parent:
                continue
            self.dfs2(c, curr)

    def sumOfDistancesInTree(self, n: int, edges: list[list[int]]) -> list[int]:
        self.n = n
        self.num_nodes = [0] * n
        self.sum_paths = [0] * n
        self.adj = [[] for _ in range(n)]

        for u, v in edges:
            self.adj[u].append(v)
            self.adj[v].append(u)

        self.dfs1(0, 0)
        self.dfs2(0, 0)

        return self.sum_paths

sol = Solution()

n = 6
edges = [[0,1],[0,2],[2,3],[2,4],[2,5]]

ans = sol.sumOfDistancesInTree(n, edges)
print(ans)
