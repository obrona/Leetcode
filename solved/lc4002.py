import math

# PnC question.
# k positive integers that sum to n is just stars and bars trick.
# for product to be even, at least 1 integer must be even.
# find the complement, num of sequences of k integers that sum to n s.t all integers are odd.

class Solution:
    def countValidSequences(self, n: int, k: int) -> int:
        MOD = int(1e9 + 7)
        total = math.comb(n - k + k - 1, k - 1)

        num_of_2s = n - k

        # all sequence have at least 1 even num
        if num_of_2s % 2 != 0:
            return total % MOD

        num_of_2s //= 2
        all_odd = math.comb(num_of_2s + k - 1, k - 1)  #  give pairs to the slots using stars and bars
        ans = (total - all_odd) % MOD
        return ans

sol = Solution()
ans = sol.countValidSequences(3, 2)
print(ans)