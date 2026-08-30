import math
from functools import reduce

# brute force.
# for each i, we remove nums[i] then test the resulting array for how many split indexes.
# a split index i is s.t gcd(arr[0:i + 1]) == gcd(arr[i + 1:])

class Solution:
    def maxValidSplits(self, nums: list[int]) -> int:
        best = 0
        for i in range(len(nums) + 1):
            arr = nums[0:i] + nums[i + 1:] if i < len(nums) else nums

            prefix_gcd = []
            for j in range(len(arr)):
                if j == 0:
                    prefix_gcd.append(arr[j])
                else:
                    prefix_gcd.append(math.gcd(prefix_gcd[-1], arr[j]))

            suffix_gcd = [0] * len(arr)
            for j in range(len(arr) - 1, -1, -1):
                if j == len(arr) - 1:
                    suffix_gcd[j] = arr[j]
                else:
                    suffix_gcd[j] = math.gcd(arr[j], suffix_gcd[j + 1])


            score = sum(a == b for a, b in zip(prefix_gcd, suffix_gcd[1:]))
            best = max(best, score)

        return best

sol = Solution()
nums = [83,58,28,34,10,26]
ans = sol.maxValidSplits(nums)
print(ans)