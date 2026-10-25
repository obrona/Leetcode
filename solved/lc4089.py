from functools import cache

# simple dp.
# dp(i) = # of valid subarrays starting at index i and has at least 1 elem.

class Solution:
    def countSubarrays(self, nums: list[int], minK: int, maxK: int) -> int:
        @cache
        def dp(i: int) -> int:
            if i == len(nums):
                return 0

            if nums[i] < minK or nums[i] > maxK:
                return 0

            return 1 + dp(i + 1)

        return sum(dp(i) for i in range(len(nums)))