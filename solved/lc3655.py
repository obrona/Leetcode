from functools import cache

# even with mirrors robot can only move right or down, so it is a DAG.
# state is (r, c, dir I entered the cell with)

class Solution:
    def uniquePaths(self, grid: list[list[int]]) -> int:
        MOD = int(1e9) + 7
        R = len(grid)
        C = len(grid[0])

        def in_bounds(r: int, c: int) -> bool:
            return r >= 0 and r < R and c >= 0 and c < C
        
        @cache
        def dp(r: int, c: int, d: bool) -> int:
            if r == R - 1 and c == C - 1:
                return 1

            if grid[r][c] == 0:
                if d == 1:
                    return dp(r, c, 0)
                
                right = dp(r, c + 1, 0) if in_bounds(r, c + 1) else 0
                down = dp(r + 1, c, 1) if in_bounds(r + 1, c) else 0
                return (right + down) % MOD
            elif d == 0:
                return dp(r + 1, c, 1) if in_bounds(r + 1, c) else 0
            elif d == 1:
                return dp(r, c + 1, 0) if in_bounds(r, c + 1) else 0

            return 0

        return dp(0, 0, 0)