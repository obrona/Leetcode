from functools import cache

# dp(idx, parity, has_skip)
# the problem is that we can skip elements even if we have not taken any elems before

class Solution:
    def maxAlternatingSum(self, nums: list[int]) -> int:
        store = [[[-999999999 for _ in range(2)] for _ in range(2)] for _ in range(len(nums))]
        def dp(i: int, parity: bool, has_skip: bool) -> int:
            if i == len(nums):
                return 0

            if store[i][parity][has_skip] != -999999999:
                return store[i][parity][has_skip]

            no_skip = nums[i] * (1 if not parity else -1) + max(0, dp(i + 1, not parity, has_skip))
            
            skip = -999999999
            if has_skip and i <= len(nums) - 3:
                skip = nums[i] * (1 if not parity else -1) + dp(i + 2, not parity, False)

            store[i][parity][has_skip] = max(no_skip, skip)
            return store[i][parity][has_skip]

        return max(dp(i, False, True) for i in range(len(nums)))

sol = Solution()
nums = [-72]
print(sol.maxAlternatingSum(nums))

