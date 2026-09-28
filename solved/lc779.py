
# just build the path from bottom to top (here top row is 1, bottom row is n).
# then retraverse back down and just change the curr val we are tracking accordingly.

class Solution:
    def kthGrammar(self, n: int, k: int) -> int:
        stack = []

        k -= 1
        for _ in range(n - 1):
            stack.append(k)
            k >>= 1

        curr = 0
        curr_pos = 0
        for pos in stack[::-1]:
            if curr == 0:
                if pos == 2 * curr_pos:
                    curr = 0
                else:
                    curr = 1
            else:
                if pos == 2 * curr_pos:
                    curr = 1
                else:
                    curr = 0
            curr_pos = pos

        return curr

sol = Solution()
print(sol.kthGrammar(2, 2))
                
