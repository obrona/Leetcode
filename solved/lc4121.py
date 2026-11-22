
# suppose you do a prefix op at index j, then it is not optimal to do another op at index k 
# where k < j, likewise for suffix op.
# because the 2nd op is completely redundant

# if you do prefix op at index i, it is not optimal to do a suffix op at index j, j < i.
# because you can do the suffix op at index i and the result is the same but the cost is lower.

class Solution:
    def minCost(self, nums: list[int]) -> int:
        left_start = [0] * len(nums)
        right_start = [0] * len(nums)

        for i in range(len(nums)):
            if i == 0:
                left_start[i] = 0
            elif nums[i] == nums[i - 1]:
                left_start[i] = left_start[i - 1]
            else:
                left_start[i] = i

        for i in range(len(nums) - 1, -1, -1):
            if i == len(nums) - 1:
                right_start[i] = len(nums) - 1
            elif nums[i] == nums[i + 1]:
                right_start[i] = right_start[i + 1]
            else:
                right_start[i] = i

        #print(left_start, right_start)

        best = int(1e18)
        for i in range(1, len(nums) - 1):
            cost = 0
            if left_start[i] > 0:
                cost += nums[i] * max(1, left_start[i])
            if right_start[i] < len(nums) - 1:
                right_idx = min(right_start[i], len(nums) - 2)
                cost += nums[i] * (len(nums) - right_idx - 1)


            best = min(best, cost)

            #print(i, left_idx, right_idx, cost)


        return best
            

sol = Solution()

nums = [3, 4, 4, 5, 4, 4, 3]
print(sol.minCost(nums))
