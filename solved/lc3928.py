import heapq

# just do 2 dijkstras
# one where the cost of roads is just c and one where the cost of roads is c * t

def make_adj_no_tax(n: int, roads: list[list[int]]):
    out = [[] for _ in range(n)]
    for r in roads:
        u, v, c, t = r
        out[u].append((v, c))
        out[v].append((u, c))
    return out

def make_adj_tax(n: int, roads: list[list[int]]):
    out = [[] for _ in range(n)]
    for r in roads:
        u, v, c, t = r
        out[u].append((v, c * t))
        out[v].append((u, c * t))
    return out

def dijkstra(n: int, src: int, adj: list[list[tuple[int,int]]]) -> list[int]:
    ds = [-1] * n
    pq = []
    
    heapq.heappush(pq, (0, src))
    
    while (len(pq) > 0):
        d, v = heapq.heappop(pq)
        if ds[v] != -1:
            continue
        ds[v] = d
        for u, c in adj[v]:
            if ds[u] != -1:
                continue
            heapq.heappush(pq, (d + c, u))

    return ds

class Solution:
    def minCost(self, n: int, prices: list[int], roads: list[list[int]]) -> list[int]:
        adj_no_tax = make_adj_no_tax(n, roads)
        adj_tax = make_adj_tax(n, roads)

        best = prices.copy()
        for v in range(n):
            to = dijkstra(n, v, adj_no_tax)
            fro = dijkstra(n, v, adj_tax)
           
            for i in range(n):
                if i == v or to[i] == -1 or fro[i] == -1:
                    continue
                best[v] = min(best[v], to[i] + fro[i] + prices[i])

        return best


sol = Solution()
n = 2
prices = [8, 3]
roads = [[0,1,1,2]]

print(sol.minCost(n, prices, roads))
        