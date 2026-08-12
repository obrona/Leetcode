from sortedcontainers import SortedList

# simple greedy.
# always take the largest asteroid whose weight is <= current mass.

class Solution:
    def asteroidsDestroyed(self, mass: int, asteroids: list[int]) -> bool:
        sorted_as = SortedList(asteroids)
        while len(sorted_as) > 0:
            idx = sorted_as.bisect_right(mass)
            if idx == 0:
                return False
            mass += sorted_as.pop(idx - 1)
        return True

sol = Solution()
mass = 10
asteroids = [3,9,19,5,21]

print(sol.asteroidsDestroyed(mass, asteroids))