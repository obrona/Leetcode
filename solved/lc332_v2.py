
# recursive version instead of the iterative version.

def make_adj(tickets: list[list[str]]) -> dict[str, list[str]]:
    adj: dict[str, list[str]] = {}
    for src, dest in tickets:
        adj.setdefault(src, []).append(dest)
    
    for v in adj.values():
        v.sort(reverse=True)

    return adj


class Solution:
    def findItinerary(self, tickets: list[list[str]]) -> list[str]:
        adj = make_adj(tickets)

        store = []
        def dfs(v: str):
            a = adj.setdefault(v, [])
            while a:
                dfs(a.pop())
            store.append(v)

        dfs('JFK')
        store.reverse()
        return store
    
sol = Solution()
tickets = [["MUC","LHR"],["JFK","MUC"],["SFO","SJC"],["LHR","SFO"]]

ans = sol.findItinerary(tickets)
print(ans)