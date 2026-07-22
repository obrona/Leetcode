# just math.

class Solution:
    def maximumValue(self, n: int, s: int, m: int) -> int:
        if n == 1:
            return s
        if n % 2 != 0:
            n -= 1

        x = (n - 1 - 1) // 2
        return s + m + (m - 1) * x

sol = Solution()
n = 4
s = 3
m = 5
print(sol.maximumValue(n, s, m))