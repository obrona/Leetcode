class Solution:
    def minMergedInteger(self, nums: list[int]) -> int:
        best = int(1e9)
        for i in range(0, len(nums), 2):
            best = min(best, int(str(nums[i]) + str(nums[i + 1])))
        return best