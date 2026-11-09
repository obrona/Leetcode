import functools
import itertools

# for each node there are 3 possible states.
# 1. remove all red nodes.
# 2. make it s.t there is a single red connected component and the root of that subtree is also red.
#    or there are no red nodes at all.
# 3. make it s.t there is a single red connected component. It can be that there is no red nodes.
# note that score(1), score(2) >= score(3) because 1, 2 are specialisation of 3. 

def make_adj(n:int, edges: list[list[int]]) -> list[list[int]]:
    adj = [[] for _ in range(n)]
    for u, v in edges:
        adj[u].append(v)
        adj[v].append(u)
    return adj


class Solution:
    def minCost(self, n: int, colors: str, edges: list[list[int]]) -> int:
        adj = make_adj(n, edges)

        @functools.cache
        def cost(v: int, p: int) -> int:
            return 1 + sum(cost(u, v) for u in adj[v] if u != p)
        
        @functools.cache
        def dfs1(v: int, p: int) -> int:
            res = 0 if colors[v] == 'B' else cost(v, p)
            return res + sum(dfs1(u, v) for u in adj[v] if u != p)


        @functools.cache
        def dfs2(v: int, p: int) -> int:
            make_all_blue = dfs1(v, p)

            res = 0 if colors[v] == 'R' else cost(v, p)
            res += sum(dfs2(u, v) for u in adj[v] if u != p)

            return min(make_all_blue, res)


        @functools.cache
        def dfs3(v: int, p: int) -> int:
            make_tree_blue = dfs1(v, p)

            root_is_red = dfs2(v, p)

            res = 0 if colors[v] == 'B' else cost(v, p)
            make_single_red_cc = [dfs3(u, v) for u in adj[v] if u != p]
            make_all_blue = [dfs1(u, v) for u in adj[v] if u != p]

            # need to do prefix, suffix sums for make_all_blue
            prefix = list(itertools.accumulate(make_all_blue))
            suffix = list(itertools.accumulate(reversed(make_all_blue)))[::-1]

            N = len(make_single_red_cc)
            best = int(1e14)
            for i in range(N):
                left = 0 if i == 0 else prefix[i - 1]
                right = 0 if i == N - 1 else suffix[i + 1]
                best = min(best, left + make_single_red_cc[i] + right)
            res += best

            return min(make_tree_blue, root_is_red, res)


        return dfs3(0, 0)

sol = Solution()
n = 3
colors = "RBR"
edges = [[0,1],[1,2]]
ans = sol.minCost(n, colors, edges)
print(ans)




        
        