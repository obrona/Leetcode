from functools import cache

# dp.
# trick here is to derive i for multiplier[i] using l, r the left and right endpoints of nums.

class Solution:
    def maximumScore(self, nums: list[int], multipliers: list[int]) -> int:
        @cache
        def dp(l: int, r: int) -> int:
            i = len(nums) - (r - l + 1)
            if i == len(multipliers):
                return 0

            left = nums[l] * multipliers[i] + dp(l + 1, r)
            right = nums[r] * multipliers[i] + dp(l, r - 1)
            return max(left, right)

        return dp(0, len(nums) - 1)

sol = Solution()
nums = [1,2,3]
multipliers = [3,2,1]
print(sol.maximumScore(nums, multipliers))