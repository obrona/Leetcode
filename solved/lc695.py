from itertools import product

# simple dfs

class Solution:
    def maxAreaOfIsland(self, grid: list[list[int]]) -> int:
        R, C = len(grid), len(grid[0])
        dirs = [[-1,0], [0,1], [1,0], [0,-1]]
        seen = [[False for _ in range(C)] for _ in range(R)]
       

        def in_bounds(r: int, c: int) -> bool:
            return r >= 0 and r < R and c >= 0 and c < C

        def dfs(r: int, c: int) -> int:
            if seen[r][c] or grid[r][c] == 0:
                return 0
            
            seen[r][c] = True
            
            cnt = 1
            for dr, dc in dirs:
                nr, nc = r + dr, c + dc
                if not in_bounds(nr, nc):
                    continue
                cnt += dfs(nr, nc)

            return cnt
        
        best = 0
        for r, c in product(range(R), range(C)):
            if seen[r][c]:
                continue
            ans = dfs(r, c)
            best = max(best, ans)

        return best
    
sol = Solution()
grid = [[0,0,0,0,1]]
ans = sol.maxAreaOfIsland(grid)
print(ans)