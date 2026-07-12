from functools import cache

# just take or no take dp.
# time complexity is O(mn^2).

class Solution:
    def maxConsistentColumns(self, grid: list[list[int]], limit: int) -> int:
        
        @cache
        def dp(col: int, prev_col: int) -> int:
            if col == len(grid[0]):
                return 0
            
            notake = dp(col + 1, prev_col)

            take = 0
            if prev_col == -1:
                take = 1 + dp(col + 1, col)
            else:
                can = all(abs(grid[i][prev_col] - grid[i][col]) <= limit for i in range(len(grid)))
                if can:
                    take = 1 + dp(col + 1, col)

            return max(take, notake)
        
        return dp(0, -1)
    
sol = Solution()
grid = [[-2,0,3]]
limit = 2

print(sol.maxConsistentColumns(grid, limit))