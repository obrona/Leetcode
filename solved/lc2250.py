# only 2 options for each monkey so total of 2^n ways.
# the only 2 ways of no collisions is when all monkeys move in the same direction.
# so ans is 2^n - 2.

class Solution:
    def monkeyMove(self, n: int) -> int:
        m = int(1e9 + 7)
        all_ways = pow(2, n, m)
        return (all_ways - 2) % m