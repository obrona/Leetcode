from collections import deque

# the 2 operations mean that the resulting array is a circular shift of [0, 1, 2, ... n - 1]
# or [n - 1, n - 2 ... 0]

# we draw the graph, then we see we can just do bfs
# eg 
# 0 1 2 3     3 2 1 0
# 1 2 3 0     0 3 2 1
# 2 3 0 1     1 0 3 2
# 3 0 1 2     2 1 0 3

# the edges go down for the left column, edge go up for the right column.
# for each row, the 2 values are the reverse of each other so the edge between them is bidrectional.

def make_adj(n: int) -> list[list[int]]:
    adj = [None for _ in range(2 * n)]
    
    for i in range(n):
        adj[i] = [(i + 1) % n, i + n]

    for i in range(n, 2 * n):
        adj[i] = [i - 1 if i > n else 2 * n - 1, i - n]

    return adj


def bfs(src: int, dst: int, adj: list[list[int]]) -> list[int]:
    dists = [-1] * len(adj)
    q = deque[int]()
    wave = 0
    
    q.append(src)

    while len(q) > 0:
        for _ in range(len(q)):
            n = q.popleft()
            if dists[n] != -1:
                continue
            dists[n] = wave
            
            if n == dst:
                return dists
            
            for c in adj[n]:
                if dists[c] != -1:
                    continue
                q.append(c)
        wave += 1

    return dists

# if is a increasing circular shift, returns the idx of the 0 element
# else return None
def is_increasing_circular_shift(arr: list[int]) -> int | None:
    i = next((i for i, x in enumerate(arr) if x == 0), -1)
    lst = arr[i:] + arr[:i]
    if all(a < b for a, b in zip(lst, lst[1:])):
        return i
    return None

# returns the index of the n - 1 element
def is_decreasing_circular_shift(arr: list[int]) -> int | None:
    last = len(arr) - 1
    i = next((i for i, x in enumerate(arr) if x == last), -1)
    lst = arr[i:] + arr[:i]
    if all(a > b for a, b in zip(lst, lst[1:])):
        return i
    return None

class Solution:
    def minOperations(self, nums: list[int]) -> int:
        i0 = is_increasing_circular_shift(nums)
        ilast = is_decreasing_circular_shift(nums)

        if i0 is None and ilast is None:
            return -1
        
        adj = make_adj(len(nums))

        if i0 is not None:
            pos = 0 if i0 == 0 else len(nums) - i0
            dists = bfs(pos, 0, adj)
            return dists[0]
        
        if ilast is not None:
            pos = len(nums) + ilast
            dists = bfs(pos, 0, adj)
            return dists[0]

#print(is_increasing_circular_shift([1,2,3,4,0]))
#print(is_decreasing_circular_shift([0,4,3,2,1]))
#rint(is_decreasing_circular_shift([0,3,2,1,4]))

sol = Solution()
nums = [0,1]
print(sol.minOperations(nums))