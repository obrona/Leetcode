
# replacing 1 number with the sum of the other 2 numbers a, b means max - min of (a, b, c) is max(a, b).
# if we repeat the operation again, the range = max - min cannot go below max(a, b).
# because if we repeat the operation on (a, b, a + b) just check all 3 possible pairs.
# the range cannot go below max(a, b)

class Solution:
    def minRange(self, a: int, b: int, c: int) -> int:
        a, b, c = sorted([a, b, c])
        if c > a + b:
            return b
        else:
            return c - a

        