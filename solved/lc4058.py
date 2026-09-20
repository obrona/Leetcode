from functools import cache
# when we left shit arr[s:e] basically the sum becomes from -x to x
# so we want the most negative subarray.
# don't forget the start element.
# sign changes depending on the length 

class Solution:
    def maxValue(self, nums: list[int]) -> int:
        nums = [pow(-1, i) * x for i, x in enumerate(nums)]

        @cache
        def dp(i: int) -> int:
            if i >= len(nums) - 1:
                return int(1e15)
            else:
                own = sum(nums[i:i+2])
                return min(own, own + dp(i + 2))

        pulse_val = sum(nums)

        best = int(1e15)
        for i in range(len(nums) - 1):
            # case 1: 1st elememt sign does not change
            case1 = dp(i + 1)

            # case 2: 1st element sign does change
            front = nums[i] + nums[i + 1]
            case2 = min(front, front + dp(i + 2))

            best = min(best, case1, case2)

        #print(best)

        return max(pulse_val, pulse_val - 2 * best)

sol = Solution()
nums = [6,4,3]
print(sol.maxValue(nums))