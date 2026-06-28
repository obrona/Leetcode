from typing import Callable
import math

# consider f a function we can apply to 1 contigous subarray.
# let dp(i, b) be the max non empty subarray sum we can get starting at i.
# b = 0 means have not applied f.
# b = 1 means applying f
# b = 2 means stop applying f.
# dp(i, 0) can go to dp(i + 1, 0), dp(i + 1, 1)
# dp(i, 1) can go to dp(i + 1, 1), dp(i + 1, 2)
# dp(i, 2) can go to dp(i + 1, 2)

def dp(nums: list[int], f: Callable[[int], int]) -> int:
    N = len(nums)
    store = [[0 for _ in range(3)] for _ in range(N + 1)]
    for i in range(N - 1, -1, -1):
        store[i][0] = max(
            nums[i] + max(0, store[i + 1][0]),
            f(nums[i]) + max(0, store[i + 1][1])
        )

        store[i][1] = max(
            f(nums[i]) + max(0, store[i + 1][1]),
            nums[i] + max(0, store[i + 1][2])
        )

        store[i][2] = nums[i] + max(0, store[i + 1][2])
    
    return max(store[i][0] for i in range(N))

class Solution:
    def maxSubarraySum(self, nums: list[int], k: int) -> int:
        f1 = lambda x: x * k
        f2 = lambda x: math.ceil(x / k) if x < 0 else math.floor(x / k)
        return max(dp(nums, f1), dp(nums, f2))
    
sol = Solution()
nums = [2,-1,-1,2,-1,-1,2]
k = 2
ans = sol.maxSubarraySum(nums, k)
print(ans)