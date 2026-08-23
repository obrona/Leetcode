class Solution:
    def findDisappearedNumbers(self, nums: list[int], lower: int, upper: int) -> list[list[int]]:
        nums.sort()
        nums = [x for x in nums if lower <= x <= upper]
        #print(nums)
        if len(nums) == 0:
            return [[lower, upper]]
        
        out = []
        for i, x in enumerate(nums):
            if i == 0 and x > lower:
                out.append([lower, x - 1])

            if i == len(nums) - 1 and x < upper:
                out.append([x + 1, upper])

            if i < len(nums) - 1 and len(nums) >= 2 and x < nums[i + 1] - 1:
                out.append([x + 1, nums[i + 1] - 1])

        return out

sol = Solution()
nums = [550,127,466,378,689]
lower = 689
upper = 767
print(sol.findDisappearedNumbers(nums, lower, upper))
