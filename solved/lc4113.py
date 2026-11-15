from functools import cache

# dynamic programming problem.
# let dp(p, idx) = maximised alice, bob scores when player p starts first on array[idx:n]
# we can remove p by noticing alice go first and bob go first are symmetrical.

class Solution:
    def maxDifference(self, nums: list[int]) -> int:
        @cache
        def dp(i: int) -> tuple[int,int]:
            if i >= len(nums):
                return 0, 0

            # take 1
            a, b = nums[i], 0
            x, y = dp(i + 1)
            if a % 3 == 0:
                a += y
                b += x
            else:
                a += x
                b += y

            if len(nums) - i < 2:
                return a, b

            c, d = nums[i] + nums[i + 1], 0
            x, y = dp(i + 2)
            if c % 3 == 0:
                c += y
                d += x
            else:
                c += x
                d += y

            if a > c:
                return a, b
            else:
                return c, d


        a, b = dp(0)
        #print(a, b)
        return a - b

sol = Solution()
nums = [3,6,4]

ans = sol.maxDifference(nums)
print(ans)
            


            