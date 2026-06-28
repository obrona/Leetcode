import heapq

# dijkstra with state augmentation.
# state is (power, node)
# for all (p, n - 1) find the shortest path
# then find the max remaining power among all (p, n - 1) with the shortest path.

# some constant factor optimisation is to order the priority queue 
# by smallest path then largest remaning power, 
# so that we can break the moment we get target as the node.
# we can do this as by pq property, we process the node with the shortest distance 1st.
# the 2nd ordering by decreasing remaining power ensure that we process the node 
# with the largest remaining power 1st.

def make_adj_list(n: int, edges: list[list[int]]) -> list[list[tuple[int,int]]]:
    adj = [[] for _ in range(n)]
    for u, v, d in edges:
        adj[u].append((v, d))
    return adj

class Solution:
    def minTimeMaxPower(
            self, 
            n: int, 
            edges: list[list[int]], 
            power: int, 
            cost: list[int], 
            source: int, 
            target: int
        ) -> list[int]:
        INVALID = int(1e15)
        
        adj = make_adj_list(n, edges)
        dists = [[INVALID for _ in range(n)] for _ in range(power + 1)]
        pq = []
        heapq.heappush(pq, (0, -power, source))
        while len(pq) > 0:
            d, p, u = heapq.heappop(pq)
            p = -p
            if dists[p][u] < INVALID:
                continue
            dists[p][u] = d

            if u == target:
                return [d, p]

            new_cost = p - cost[u]
            if new_cost < 0:
                continue
            
            for v, d2 in adj[u]:
                if dists[new_cost][v] < INVALID:
                    continue
                heapq.heappush(pq, (d + d2, -new_cost, v))

        return [-1, -1]
        
sol = Solution()

n = 5
edges = [[0,1,1],[1,4,1],[0,2,1],[2,3,1],[3,4,1]]
power = 4
cost = [2,3,1,1,1]
source = 0
target = 4

ans = sol.minTimeMaxPower(n, edges, power, cost, source, target)
print(ans)