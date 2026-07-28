import heapq

# just single source shortest path using dijkstra.
# state is (r, c, parity).
# can go in the 4 dirs, paying the respective penalty, or stay and wait in the same cell to switch parity.

class Solution:
    def minCost(self, m: int, n: int, penalty: list[list[int]]) -> int:
        odd_dirs = [[0, 1], [1, 0]]
        even_dirs = [[0, -1], [-1, 0]]
        dists = [[[-1 for _ in range(2)] for _ in range(n)] for _ in range(m)]
        pq: list[tuple[int,...]] = []

        def cost(i: int, j: int) -> int:
            return (i + 1) * (j + 1)

        def valid(r: int, c: int) -> bool:
            return r >= 0 and r < m and c >= 0 and c < n

        heapq.heappush(pq, (cost(0, 0), 0, 0, 1))

        while len(pq) > 0:
            d, r, c, p = heapq.heappop(pq)
            if (dists[r][c][p] != -1):
                continue
            
            dists[r][c][p] = d

            if r == m - 1 and c == n - 1:
                return d

            for dr, dc in even_dirs:
                nr, nc = r + dr, c + dc
                if not valid(nr, nc) or dists[nr][nc][1 - p] != -1:
                    continue
                w = (0 if p == 0 else penalty[r][c]) + cost(nr, nc)
                heapq.heappush(pq, (d + w, nr, nc, 1 - p))

            for dr, dc in odd_dirs:
                nr, nc = r + dr, c + dc
                if not valid(nr, nc) or dists[nr][nc][1 - p] != -1:
                    continue
                w = (0 if p == 1 else penalty[r][c]) + cost(nr, nc)
                heapq.heappush(pq, (d + w, nr, nc, 1 - p))

            if dists[r][c][1 - p] == -1:
                heapq.heappush(pq, (d + penalty[r][c], r, c, 1 - p))

        raise RuntimeError('should not reach here')



sol = Solution()

m = 2
n = 2
penalty = [[5,3],[1,4]]

ans = sol.minCost(m, n, penalty)
print(ans)

                


