import math

# k = {1, 2, 3, 4}
# suppose r < c
# if r >= 2 and c >= 4, 
# reduce it to a r * 2 case by covering the top right (r - 2, c - 1) cells
# then there is only c ways, and we can reduce it to k by covering cells in the r - 2 layer, from the right to left.
# if r > c, we consider the tranpose, get the result, then tranpose back.
# if r > c, we consider the tranpose, get the result, then tranpose back.
# handle special case when r = 3, c = 3 and k = 4
# and also when r or c = 1


def helper(grid: list[list[str] | tuple[str]]) -> list[str]:
    return [''.join(lst) for lst in grid]

def handle_single_line(m: int, n: int, k: int) -> list[str]:
    if  k > 1:
        return []
    grid = [['.' for _ in range(n)] for _ in range(m)]
    return helper(grid)

def handle_rest(m: int, n: int, k: int) -> list[list[str]]:
    grid = [['.' for _ in range(n)] for _ in range(m)]
    
    for r in range(0, m - 2):
        for c in range(1, n):
            grid[r][c] = '#'

    for c in range(n - 1, k - 1, -1):
        grid[m - 2][c] = '#'

    return grid
    

class Solution:
    def createGrid(self, m: int, n: int, k: int) -> list[str]:
        max_paths = math.comb(m - 1 + n - 1, m - 1)
        if k > max_paths:
            return []
        
        if m == 1 or n == 1:
            return handle_single_line(m, n, k)
        
        if m == 3 and n == 3 and k == 4:
            return ['..#', '...', '#..']
        
        grid = handle_rest(min(m, n), max(m, n), k)
        if len(grid) != m:
            grid = list(zip(*grid))
        return helper(grid)
    
sol = Solution()
print(sol.createGrid(10, 10, 2))