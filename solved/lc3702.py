from functools import reduce

# trick question.
# xor the entire array, if it not 0 we get the ans immediately.
# if ans is 0, as long there is 1 non-zero element we can just remove it so ans is len - 1.
# if all is 0, then the ans is just 0.

class Solution:
    def longestSubsequence(self, nums: list[int]) -> int:
        ans = reduce(lambda acc, x: acc ^ x, nums, 0)
        if ans != 0:
            return len(nums)
        elif any(x != 0 for x in nums):
            return len(nums) - 1
        return 0
