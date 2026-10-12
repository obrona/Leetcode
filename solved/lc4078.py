# rate of growth of fibonacci is O(1.62^n)
# so just generate the fibonacci sequence 1 by 1.

class Solution:
    def threeFibonacciSum(self, n: int) -> bool:
        a, b, c = 0, 1, 1
        while 1:
            if a + b + c == n:
                return True
            elif a + b + c > n:
                return False
            a, b, c = b, c, b + c