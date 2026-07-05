# just update the max as we go from right to left

class Solution:
    def maxValidPairSum(self, nums: list[int], k: int) -> int:
        best = int(-1e10)
        store = int(-1e10)
        for i in range(len(nums) - 1, -1, -1):
            if i + k < len(nums):
                store = max(store, nums[i + k])
                best = max(best, nums[i] + store)
        return best