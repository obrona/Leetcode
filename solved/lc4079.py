import math

# use sieve of eratosthenes.
# always select the smallest available prime number.

class Solution:
    def maxPrimes(self, n: int, s: int) -> list[int]:
        is_prime = [False] * 2 + [True] * (n - 1)
        for i in range(2, math.floor(math.sqrt(n)) + 1):
            if is_prime[i]:
                for j in range(i * i, n + 1, i):
                    is_prime[j] = False

        res = 0
        out = []
        for i in range(2, n + 1):
            if not is_prime[i]:
                continue
            if res + i > s:
                break
            res += i
            out.append(i)

        return out

sol = Solution()
n = 7
s = 20
print(sol.maxPrimes(n, s))