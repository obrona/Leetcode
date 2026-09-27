from collections import Counter

# just 2 pointer
# when we insert a new element, we check with every element in the 'set'
# and see whether it matches an element in the set.
# once we hit a match i.e x + y = z, then we stop and remove the element at the left index.
# also handle the case where x + y (2 elem in the existing set) = new element to add.
# O(n^2) works because n <= 1000.


class Solution:
    def maxSubarray(self, nums: list[int]) -> int:
        r = 0
        cnter = Counter[int]()
        best = 0
        for i in range(len(nums)):
            r = max(r, i)
            while r < len(nums):
                can_take = True
                for x in range(i, r):
                    if cnter[nums[x] + nums[r]] > 0:
                        can_take = False
                        break

                    if nums[r] > nums[x]:
                        diff = nums[r] - nums[x]
                        if diff == nums[x]:
                            if cnter[diff] >= 2:
                                can_take = False
                                break
                        
                        elif cnter[diff] >= 1:
                            can_take = False
                            break
                
                if can_take:
                    cnter[nums[r]] += 1
                    r += 1
                else:
                    break

            best = max(best, r - i)

            if r > i:
                cnter[nums[i]] -= 1

        return best

sol = Solution()

nums = [3,4,5,6]

print(sol.maxSubarray(nums))
        