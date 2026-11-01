import math

# at index i with value, find the smallest prime factor.
# if it is already even so = 2k, then the optimal way is to go from 2(k+1), 2(k+2) ...
# don't forget to check if it can reach index 0.
# if it is odd so = kp, k is odd, then (k+1)p is even

def find_smallest_prime_factor(n: int) -> int:
    p = next((x for x in range(2, math.isqrt(n) + 1) if n % x == 0), None)
    return p if p != None else n

class Solution:
    def minimumMaxValue(self, n: int, index: int, value: int) -> int:
        if value == 1:
            return -1

        if value % 2 == 0:
            k = value // 2
            if k - 1 < index:
                return -1
            return (k + n - 1 - index) * 2

        else:
            p = find_smallest_prime_factor(value)
            k = value // p

            prev = (k - 1) * p
            k2 = prev // 2
            if k2 - 1 < index - 1:
                return -1

            next = (k + 1) * p
            k3 = next // 2
            return (k3 + n - 1 - index - 1) * 2
            

sol = Solution()
n = 4
index = 2
value = 8
print(sol.minimumMaxValue(n, index, value))