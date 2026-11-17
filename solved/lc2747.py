from itertools import zip_longest
from collections import Counter

# simple 2 pointer solution.
# 2 pointer to maintain window of serves request.
# before that we remove duplicate [sever, time]

class Solution:
    def countServers(self, n: int, logs: list[list[int]], x: int, queries: list[int]) -> list[int]:
        logs.sort(key=lambda l: l[1])

        res = [0] * len(queries)
        s, e = 0, 0
        queries_with_idx = list(enumerate(queries))
        queries_with_idx.sort(key=lambda q: q[1])
        seen_servers = Counter[int]()

        def remove(server: int):
            seen_servers[server] -= 1
            if seen_servers[server] == 0:
                del seen_servers[server]

        for i, t in queries_with_idx:
            while e < len(logs) and logs[e][1] <= t:
                seen_servers[logs[e][0]] += 1
                e += 1

            while s < e and logs[s][1] < t - x:
                remove(logs[s][0])
                s += 1

            res[i] = n - len(seen_servers)

        return res

sol = Solution()
n = 3
logs = [[2, 4], [2, 1], [1, 2], [3, 1]]
x = 2
queries = [3, 4]

ans = sol.countServers(n, logs, x, queries)
print(ans)
            
