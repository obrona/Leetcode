
# simple tree dfs.

def make_adj(parent: list[int]) -> list[list[int]]:
    out = [[] for _ in range(len(parent))]
    for i, p in enumerate(parent):
        if p == -1:
            continue
        out[p].append(i)
    return out

def get_height(root: int, adj: list[list[int]]) -> int:
    def dfs(v: int) :
        return 1 + max((dfs(c) for c in adj[v]), default=0)
    return dfs(root)

def get_weighted_sum(root: int, h: int, adj: list[list[int]], nums: list[int]) -> int:
    def dfs(v: int, d: int):
        return nums[v] * (h - d + 1) + sum(dfs(c, d + 1) for c in adj[v])
    return dfs(root, 1)

class Solution:
    def weightedSum(self, parent: list[int], nums: list[int]) -> int:
        adj = make_adj(parent)
        h = get_height(0, adj)
        ans = get_weighted_sum(0, h, adj, nums)
        return ans

sol = Solution()
parent = [-1,0,0,0,2,2]
nums = [5,2,3,1,4,6]

ans = sol.weightedSum(parent, nums)
print(ans)