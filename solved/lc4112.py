from functools import cache

# once we set a subtree nodes all to 0, the operation needed for the nodes inside that subtree no longer matter.

def make_adj(parent: list[int]) -> list[list[int]]:
    adj = [[] for _ in range(len(parent))]
    for i, p in enumerate(parent):
        if p == -1:
            continue
        adj[p].append(i)
    return adj


class Solution:
    def maxScore(self, parent: list[int], op: list[int], score: list[int]) -> int:
        adj = make_adj(parent)

        @cache
        def subtree_score(v: int) -> int:
            return score[v] + sum(subtree_score(c) for c in adj[v])

        def dfs(v: int) -> int:
            nexts = adj[v]
            if len(nexts) == 0:
                return score[v]

            store = [dfs(c) for c in nexts]
            no_zero = sum(store)
            zero_one = max(no_zero - store[i] for i in range(len(store)))

            if op[v] == 0:
                return max(no_zero, zero_one) + score[v]
            else:
                return zero_one + score[v]


        return dfs(0)

sol = Solution()
parent = [-1,0,0,0,1,2,3,3]
op = [1,1,0,0,1,1,0,1]
score = [5,6,1,2,3,2,3,-3]

ans = sol.maxScore(parent, op, score)
print(ans)