
# problem is to find the lexicographical shortest eulerian path in a directed graph.
# we can use hierholzer algorithm, but the adjacent stack is sorted in decreasing 
# lexicographical order so the smallest elem gets pop out first.
# how to proof this ? leave it up to you I guess.

def make_adj(tickets: list[list[str]]) -> dict[str, list[str]]:
    adj: dict[str, list[str]] = {}
    for src, dest in tickets:
        adj.setdefault(src, []).append(dest)
    
    for v in adj.values():
        v.sort(reverse=True)

    return adj

def get_eulerian_path[T](start: T, adj: dict[T, list[T]]) -> list[T]:
    adj_copy = {k: v[:] for k, v in adj.items()}
    left_stack: list[T] = []
    right_stack: list[T] = []

    left_stack.append(start)
    while len(left_stack) > 0:
        end = left_stack[-1]
        nexts = adj_copy.setdefault(end, [])
        if len(nexts) == 0:
            left_stack.pop()
            right_stack.append(end)
        else:
            left_stack.append(nexts.pop())
    
    right_stack.reverse()
    return right_stack




class Solution:
    def findItinerary(self, tickets: list[list[str]]) -> list[str]:
        adj = make_adj(tickets)
        path = get_eulerian_path('JFK', adj)
        return path
    
sol = Solution()
tickets = [["MUC","LHR"],["JFK","MUC"],["SFO","SJC"],["LHR","SFO"]]

ans = sol.findItinerary(tickets)
print(ans)
