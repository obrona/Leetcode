class Solution:
    def peakValleyDifference(self, nums: list[int]) -> int:
        a = sum(x for i, x in enumerate(nums) 
                if i > 0 and i < len(nums) - 1 and nums[i - 1] < nums[i] and nums[i] > nums[i + 1])
        b = sum(x for i, x in enumerate(nums)
                if i > 0 and i < len(nums) - 1 and nums[i - 1] > nums[i] and nums[i] < nums[i + 1])
        return a - b