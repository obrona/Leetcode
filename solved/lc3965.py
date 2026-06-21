import math

# just dfs

def get_adj(n: int, edges: list[list[int]]) -> list[list[int]]:
    adj = [[] for _ in range(n)]
    for x, y in edges:
        adj[x].append(y)
        adj[y].append(x)
    return adj

class Solution:
    def dfs(self, v: int, p: int, adj: list[list[int]], baseTime: list[int]) -> int:
        children = adj[v]
        if (len(children) == 0 and v == 0) or (len(children) == 1 and children[0] == p):
            return baseTime[v]
        
        times = [self.dfs(c, v, adj, baseTime) for c in children if c != p]
        min_time = min(times)
        max_time = max(times)
        return max_time - min_time + baseTime[v] + max_time


    def finishTime(self, n: int, edges: list[list[int]], baseTime: list[int]) -> int:
        adj = get_adj(n, edges)
        return self.dfs(0, 0, adj, baseTime)

sol = Solution()
n = 3
edges = [[0, 1], [1, 2]]
baseTime = [9, 5, 3]
print(sol.finishTime(n, edges, baseTime))