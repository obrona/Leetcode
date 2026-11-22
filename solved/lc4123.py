

# pure observation question.
# the 1st and last element have to be counted no matter what as there are no elems to the left/right
# to remove them.
# hence just remove them.
# for the subarray arr[1:n-1], sum up elems < 0.
# if there are even elems great can pair them all up.
# if not, there are 2 options
# remove the largest neg elem or include the smallest non-neg elem.

class Solution:
    def minCost(self, nums: list[int]) -> int:
        res = nums[0] + nums[-1]
        c = sum(1 for x in nums[1:-1] if x < 0)
        s = sum(x for x in nums[1:-1] if x < 0)
        to_minus = max((x for x in nums[1:-1] if x < 0), default=None)
        to_add = min((x for x in nums[1:-1] if x >= 0), default=None)

        best = 999999999

        if c == 0:
            return res
        elif c % 2 == 0:
            return res + s
        else:
            add = 999999999 if to_add is None else res + s + to_add
            minus = 999999999 if to_minus is None else res + s - to_minus
            return min(add, minus)




sol = Solution()
nums = [2, -7, 3, -5]
print(sol.minCost(nums))