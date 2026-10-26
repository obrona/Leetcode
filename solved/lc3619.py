# just dfs

import itertools

class Solution:
    def countIslands(self, grid: list[list[int]], k: int) -> int:
        R = len(grid)
        C = len(grid[0])
        visited = [[False for _ in range(C)] for _ in range(R)]
        dirs = [(-1, 0), (0, 1), (1, 0), (0, -1)]

        def in_bounds(r: int, c: int) -> bool:
            return r >= 0 and r < R and c >= 0 and c < C

        def dfs(r: int, c: int) -> int:
            visited[r][c] = True
            res = grid[r][c]
            for dr, dc in dirs:
                nr = r + dr
                nc = c + dc
                if not in_bounds(nr, nc) or grid[r][c] == 0 or visited[nr][nc]:
                    continue
                res += dfs(nr, nc)
            return res

        return sum(dfs(r, c) % k == 0 
                   for r, c in itertools.product(range(R), range(C)) if not visited[r][c] and grid[r][c] > 0)