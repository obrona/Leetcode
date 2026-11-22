class Solution:
    def countDominantElements(self, nums: list[int]) -> int:
        cnt = 0
        for i in range(len(nums)):
            c = 0
            s = 0
            if i - 1 >= 0:
                c += 1
                s += nums[i - 1]
            if i + 1 < len(nums):
                c += 1
                s += nums[i + 1]
            if c == 0 or nums[i] >= s / c:
                cnt += 1
        return cnt