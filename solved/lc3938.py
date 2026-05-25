
# p1 wants to go from (0, 0) to (m - 1, n - 1) can only go right, down
# p2 wants to go from (m - 1, 0) to (0, n - 1) can only go right, up

# the intersecting path can only be a column or a row.

# but there are edge cases

# for each row and col, at the endpoints (the start and the end), 
# must take 2 squares (e.g row[0] and row[1] or row[n - 2] and row[n - 1])

# this means for the 1st and last row / col we cannot take 1 square only.

# also we cannot take 0 squares, must be at least 1
 
# if right is true means the result at arr[-1] must be length 2 or more or length 0
# if left is true means the result at arr[0] must be length 2 or more or length 0
def kadane(arr: list[int], left=False, right=False) -> int:
    store = [-int(1e9)] * len(arr)
    store[0] = arr[0]
    for i in range(1, len(arr)):
        store[i] = arr[i] + max(0, store[i - 1])

    if right:
        store[-1] = arr[-1] + arr[-2] + (max(0, store[-3] if len(store) >= 3 else 0))

    if left:
        _store = [0] * len(arr)
        _store[-1] = arr[-1]
        for i in range(len(arr) - 2, -1, -1):
            _store[i] = arr[i] + max(0, _store[i + 1])
        
        store[0] = arr[0] + arr[1] + max(0, (_store[2] if len(_store) >=3 else 0))
    
    #print(max(store))
    return max(store)


def kadane_at_least2(arr: list[int]) -> int:
    store = [0] * len(arr)
    store[0] = arr[0]
    for i in range(1, len(arr)):
        store[i] = arr[i] + max(0, store[i - 1])

    #print(store)

    result = [-int(1e9)] * len(arr)
    for i in range(1, len(arr)):
        result[i] = arr[i] + arr[i - 1] + max(0, (store[i - 2] if i - 2 >= 0 else 0))

    #print(max(result))
    return max(result)

class Solution:
    def maxScore(self, grid: list[list[int]]) -> int:
        R = len(grid)
        C = len(grid[0])
        transpose = list(zip(*grid))
        
        r = max(kadane(row, True, True) if i != 0 and i != R - 1 else kadane_at_least2(row) for i, row in enumerate(grid))
        
        c = max(kadane(col, True, True) if i != 0 and i != C - 1 else kadane_at_least2(col) for i, col in enumerate(transpose)) 

        #print(r, c)

        return max(r, c)
    
sol = Solution()
grid = [[-5,-6,-7],[-8,-100,-9],[-10,-11,-12]]
#print(sol.maxScore(grid))
print(kadane_at_least2([-5, -6, -7]))

