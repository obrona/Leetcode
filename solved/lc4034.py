# if bishop and target square are not of the same color ans is -1
# ans is 1 if bishop and target are on the same diagonal, else 2.

class Solution:
    def minBishopMoves(self, source: list[int], target: list[int]) -> int:
        if sum(source) % 2 != sum(target) % 2:
            return -1

        if sum(source) == sum(target):
            return 1

        if target[0] - source[0] == target[1] - source[1]:
            return 1

        return 2