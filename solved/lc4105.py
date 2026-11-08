import math


# Idea: look at the infinite string aaaa.... If b * y appears in a * x at position p,
# then each of the y copies of b starts at p, p + |b|, p + 2|b|, ...
# Every one of those positions has to be a place where b matches. Since the infinite
# string repeats every |a| characters, only the value p mod |a| matters.
#
# Steps:
# 1. Quick rejection: if |a| * x < |b| * y, the target is longer than the text -> false.
# 2. Find valid start positions (KMP): build a repeated just enough times to cover any
#    window of length |b| that starts in [0, |a|). Run KMP on it and keep the match
#    positions i < |a|. Call this set S. If S is empty -> false.
# 3. Build a functional graph: add an edge i -> (i + |b|) % |a|. Each node has exactly
#    one out-edge, and the map is injective, so no node has two in-edges. Following a
#    chain from i tells you how many copies of b in a row you can place starting at i.
#    The chain stops when it reaches a node that isn't in S.
# 4. DFS over the chains. Each component is one of two shapes:
#    - Path: the chain leaves S after L steps. Starting at node i, you can place at most
#      L copies of b. The answer is true if L >= y and i + |b| * y <= |a| * x.
#    - Cycle: the chain comes back to a node already on the DFS stack. Then every node
#      on the stack can produce copies of b forever, including tail nodes that lead into
#      the cycle. The count y is never the limit; only the total length is. So the best
#      choice is the smallest start on the stack, and the answer is true if
#      min_start + |b| * y <= |a| * x.
# 5. Return true if any start passes its check.
#
# Complexity: KMP runs on a string of length O(|a| + |b|), and the graph has at most
# |a| nodes. Everything is polynomial in the string lengths and doesn't depend on x or y,
# which can be as large as 10^9.

def prefix_function(s: str) -> list[int]:
    N = len(s)
    store = [0] * N
    k = 0
    for i in range(1, N):
        while k > 0 and s[i] != s[k]:
            k = store[k - 1]
        if s[i] == s[k]:
            k += 1
        store[i] = k
    return store


def kmp_find_all(a: str, b: str) -> list[int]:
    pi = prefix_function(b)
    out = []
    j = 0
    for i, c in enumerate(a):
        while j > 0 and c != b[j]:
            j = pi[j - 1]
        if c == b[j]:
            j += 1
        
        if j == len(b):
            out.append(i - j + 1)
            j = pi[j - 1]
    return out


def find_all_possible_start(a: str, b: str) -> list[int]:
    aa = a * (1 + math.ceil((len(b) - 1) / len(a)))
    pos = kmp_find_all(aa, b)
    return [i for i in pos if i < len(a)]

# for cycle we don't need the cycle length at all.
# we just need the min of all the start_positions in that cycle.
def can_cycle(start_pos: int, a: str, b: str, x: int, y: int) -> bool:
    return start_pos + len(b) * y <= len(a) * x

def can_path(start_pos: int, path_len: int, a: str, b: str, x: int, y: int) -> bool:
    if path_len < y:
        return False
    return start_pos + len(b) * y <= len(a) * x


class Solution:
    def repeatedStringMatch(self, a: str, b: str, x: int, y: int) -> bool:
        if len(a) * x < len(b) * y:
            return False
        
        start_pos = set(find_all_possible_start(a, b))
        if len(start_pos) == 0:
            return False

        can = False
        visited = set[int]()
       
        def dfs(i: int, stack: set[int]) -> int:
            nonlocal can, start_pos, visited

            visited.add(i)
            stack.add(i)
            next = (i + len(b)) % len(a)
            
            if next in stack:
                min_start_pos = min(i, i, *stack)
                res = can_cycle(min_start_pos, a, b, x, y)
                can = can or res

                stack.remove(i)
                return -1
            elif next not in start_pos:
                stack.remove(i)
                res = can_path(i, 1, a, b, x, y)
                can = can or res
                return 1

            stack.add(i)
            d = dfs(next, stack)
            stack.remove(i)

            if d == -1:
                return -1
            else:
                path_len = 1 + d
                res = can_path(i, path_len, a, b, x, y)
                can = can or res
                return path_len

        for i in start_pos:
            if i not in visited:
                dfs(i, set())

        return can


#print(prefix_function("aba"))
#print(kmp_find_all("abababa", "aba"))
#print(find_all_possible_start("abcd", "cdab"))

sol = Solution()
a = 'uz'
b = 'u'
x = 6
y = 1

ans = sol.repeatedStringMatch(a, b, x, y)
print(ans)
