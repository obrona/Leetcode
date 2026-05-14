from collections import Counter
from functools import reduce

# we sort nums
# starting from the smallest number we check x, 2x, 3x ... if kx exists then replace it with x

class Solution:
    def minArraySum(self, nums: list[int]) -> int:
        lim = max(nums)
        sorted_nums = sorted(set(nums))
        cnter = Counter(nums)

        for x in sorted_nums:
            if x not in cnter:
                continue
            for y in range(x * 2, lim + 1, x):
                if y in cnter:
                    cnter[x] += cnter[y]
                    del cnter[y]
        print(cnter)
        ans = reduce(lambda acc, x: acc + x[0] * x[1], cnter.items(), 0)
        return ans
    
sol = Solution()
print(sol.minArraySum([4,2,6,8]))
    
