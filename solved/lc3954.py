
# just a math question.
# abs(n - x) = abs(x - n)
# abs(x - n) <= k -> n - k <= x <= n + k
# then just check if n & x = 0

class Solution:
    def sumOfGoodIntegers(self, n: int, k: int) -> int:
        it = range(max(0, n - k), n + k + 1)
        it = filter(lambda x: n & x == 0, it)
        #print(list(it))
        return sum(it)

print(Solution().sumOfGoodIntegers(1, 13))