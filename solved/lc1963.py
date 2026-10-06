import math

# given a string, we cross out matched pairs []
# eg []]][[ -> ]][[
# after crossing out match pairs, it can be proven the final string is in the form of
# ]]...]][[...[[
# ans is just ceil(num of ] // 2).
# as each ops clears 2.

class Solution:
    def minSwaps(self, s: str) -> int:
        cnt = 0
        inbalance = 0
        for c in s:
            if c == '[':
                cnt += 1
            elif c == ']':
                if cnt == 0:
                    inbalance += 1
                else: 
                    cnt -= 1
        #print(inbalance)
        return math.ceil(inbalance / 2)

sol = Solution()
s = "[[[]]]][][]][[]]][[["
print(sol.minSwaps(s))