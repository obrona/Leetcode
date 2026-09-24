
# since n = 1000, we can do dfs per node.
# root the tree at node i, then count how many nodes with path sum i -> node that is divisible by signal speed.

class Solution:
    def countPairsOfConnectableServers(self, edges: list[list[int]], signalSpeed: int) -> list[int]:
        n = len(edges) + 1
        adj = [[] for _ in range(n)]

        for u, v, w in edges:
            adj[u].append((v, w))
            adj[v].append((u, w))

        def dfs(curr: int, parent: int, path: int) -> int:
            cnt = 1 if path % signalSpeed == 0 else 0
            cnt += sum(dfs(x, curr, path + w) for x, w in adj[curr] if x != parent)
            return cnt

        out = [0] * n
        for i in range(n):
            res = 0
            curr_cnt = 0
            for c, w in adj[i]:
                new = dfs(c, i, w)
                res += new * curr_cnt
                curr_cnt += new
            out[i] = res

        return out

sol = Solution()

edges = [[0,6,3],[6,5,3],[0,3,1],[3,2,7],[3,1,6],[3,4,2]]
signalSpeed = 3

ans = sol.countPairsOfConnectableServers(edges, signalSpeed)
print(ans)