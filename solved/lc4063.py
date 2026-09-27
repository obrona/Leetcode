from collections import Counter

# O(n^2) algo.
# for each start index i, iterate to the right.
# at index j, store the sum arr[i:j] and then store in a dict 2*j % k
# arr[i:j] is valid if sum is divisible by k or there is an individual element
# where sum(arr[i:j]) % k = 2*x % k

class Solution:
    def longestSubarray(self, nums: list[int], k: int) -> int:
        best = 0
        for i in range(len(nums)):
            store = Counter[int]()
            curr_sum = 0
            for j in range(i, len(nums)):
                curr_sum += nums[j]
                store[(2 * nums[j]) % k] += 1

                if curr_sum % k == 0 or store[curr_sum % k] > 0:
                    best = max(best, j - i + 1)
        return best

sol = Solution()
nums = [2,2,5]
k = 6
ans = sol.longestSubarray(nums, k)
print(ans)