

# find the shortest string s over alphabet [0, 1, 2, ... k - 1]
# s.t all strings of length n appear at least once in s as a substring.
# de Brujin sequence problem, construct a de Brujin graph and find a eulerian circuit.
# just read wikipedia for the all the info.
# construct a graph with k**n-1 nodes.
# each node have k out edges and k in edges. 
# since every node has out degree = in degree, an eulerian circuit exists.

# in the de brujin graph every (node, edge) correspond to 1 string we are trying to make.
# each edge is used only once.
# each edge adds only 1 more character.
# hence the eulerian circuit is the shortest possible string.
# the total length is n - 1 + k**n

class Solution:
    def crackSafe(self, n: int, k: int) -> str:
        if n == 1:
            return ''.join(str(i) for i in range(k))
        
        edges_left = dict[str, int]()
        left: list[tuple[str,int]] = []
        right: list[tuple[str, int]] = []
        left.append(('0' * (n - 1), 0))
        edges_left['0' * (n - 1)] = 1

        while len(left) != 0:
            node, edge = left[-1]
            next_node = node[1:] + str(edge)
            if next_node not in edges_left:
                edges_left[next_node] = 0
            next_edge = edges_left[next_node]

            if next_edge == k:
                right.append((node, edge))
                left.pop()
            else:
                left.append((next_node, next_edge))
                edges_left[next_node] += 1

        right.reverse()
        #print(right)

        res = right[0][0] + str(right[0][1])
        for edge in right[1:]:
            res += str(edge[1])

        return res

sol = Solution()
ans = sol.crackSafe(3, 2)
print(ans)

        
