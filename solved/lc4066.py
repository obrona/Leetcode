from collections import Counter, defaultdict

# for each value x, take the freq counts of the mmediate left and right elem
# if we change x to y, the new counts to add is simply the freq of y 
# who is consecutive to elem of value x.
# how about pairs who were previously valid pairs before the operation?
# well they are still valid pairs after the operation as they both change together.
# so there is no need to change anything.

class Solution:
    def maxEqualAdjacentPairs(self, nums: list[int]) -> int:
        cnters = defaultdict[int, Counter[int]](Counter)
        total = 0

        for i in range(len(nums)):
            if i > 0:
                cnter = cnters[nums[i]]
                if nums[i] == nums[i - 1]:
                    total += 1
                else:
                    cnter[nums[i - 1]] += 1

            if i < len(nums) - 1:
                cnter = cnters[nums[i]]
                # don't double count!
                if nums[i] != nums[i + 1]:
                    cnter[nums[i + 1]] += 1


        best = total
        for x in set(nums):
            best = max(best, total + max(cnters[x].values(), default=0))

        return best

sol = Solution()

nums = [1,1,1]
ans = sol.maxEqualAdjacentPairs(nums)
print(ans)
