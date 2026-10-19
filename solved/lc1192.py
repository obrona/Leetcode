
# graph must be connected
def find_bridges(n: int, edges: list[list[int]]) -> list[list[int]]:
    adj = [[] for _ in range(n)]
    for u, v in edges:
        adj[u].append(v)
        adj[v].append(u)
    
    t = 0
    visited = [False] * n
    time = [0] * n
    low = [n + 1] * n

    def dfs(v: int, p: int):
        nonlocal t
        visited[v] = True
        time[v] = t
        t += 1

        for c in adj[v]:
            if c == p:
                continue
            elif visited[c]:
                # back edge so take time
                low[v] = min(low[v], time[c])
            else:
                dfs(c, v)
                # tree edge so take low
                low[v] = min(low[v], low[c])

    dfs(0, 0)

    bridges = []
    for u, v in edges:
        if time[u] < time[v] and time[u] < low[v] or time[v] < low[u]:
            bridges.append([u, v])

    return bridges

class Solution:
    def criticalConnections(self, n: int, connections: list[list[int]]) -> list[list[int]]:
        return find_bridges(n, connections)