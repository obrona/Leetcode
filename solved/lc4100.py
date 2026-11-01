from dataclasses import dataclass

# xor balance = # of set bits in a xor b xor c ... is even
# popcount(x) = # of set bits
# popcount(a xor b) = popcount(a) + popcount(b) - 2 * popcount(a & b)
# so for popcount(a xor b) to be even, parity of popcount of a, b must be the same.
# only the parity of popcount(a) matters, the value of a is not needed.
# this is the key insight to solving the problem.

# at every node, we just need to get
# length of shortest path whose xor val of path has even # of set bits.
# length of shortest path whose xor val of path has odd # of set bits.

@dataclass
class Res:
    res: int | None = None
    e_len: int | None = None  # length of shortest path whose xor val of path has even number of set bits
    o_len: int | None = None  # lenght of shortest path whose xor value of path has odd number of set bits
 
def make_adj(n: int, edges: list[list[int]]) -> list[list[tuple[int, int]]]:
    adj = [[] for _ in range(n)]
    for u, v, w in edges:
        adj[u].append((v, w))
        adj[v].append((u, w))
    return adj

def mn(a: int | None, b: int | None) -> int:
    if a == None and b == None:
        return None
    elif a == None:
        return b
    elif b == None:
        return a
    else:
        return min(a, b)


def dfs(v: int, p: int, adj: list[list[tuple[int,int]]], values: list[int]) -> Res:
    my_res = Res()
    bc = values[v].bit_count()

    if bc % 2 == 0:
        my_res.e_len = 0
    else:
        my_res.o_len = 0

    for c, w in adj[v]:
        if c == p:
            continue

        c_res = dfs(c, v, adj, values)
        
        my_res.res = mn(my_res.res, c_res.res)

        if c_res.e_len != None and my_res.e_len != None:
            my_res.res = mn(my_res.res, my_res.e_len + w + c_res.e_len)

        if c_res.o_len != None and my_res.o_len != None:
            my_res.res = mn(my_res.res, my_res.o_len + w + c_res.o_len)


        if values[v].bit_count() % 2 == 0:
            if c_res.e_len != None:
                my_res.e_len = c_res.e_len + w if my_res.e_len == None else min(my_res.e_len, c_res.e_len)
            if c_res.o_len != None:
                my_res.o_len = c_res.o_len + w if my_res.o_len == None else min(my_res.o_len, c_res.o_len + w)
        else:
            if c_res.o_len != None:
                my_res.e_len = c_res.o_len + w if my_res.e_len == None else min(my_res.e_len, c_res.o_len + w)
            if c_res.e_len != None:
                my_res.o_len = c_res.e_len + w if my_res.o_len == None else min(my_res.o_len, c_res.e_len + w)

    return my_res


class Solution:
    def minActivationCost(self, edges: list[list[int]], values: list[int]) -> int:
        adj = make_adj(len(values), edges)
        res = dfs(0, 0, adj, values)
        #print(adj)
        #print(res)
        return -1 if res.res == None else res.res

sol = Solution()
edges = [[0,1,4],[0,2,6],[0,3,3],[3,4,5]]
values = [3,1,7,1,3]
ans = sol.minActivationCost(edges, values)
print(ans)