import math

# just simulate the process.
# use math to speed up the calculation.

class Solution:
    def minimumCost(self, nums: list[int], k: int) -> int:
        f = lambda curr, num_times: (curr + curr + num_times - 1) * num_times // 2
        
        curr = 1
        store = k
        ans = 0
        for x in nums:
            if x <= store:
                store -= x
            else:
                num_times = math.ceil((x - store) / k)
                ans += f(curr, num_times)
                curr += num_times
                store += num_times * k - x
        return ans % int(1e9 + 7)
    
sol = Solution()
nums = [1, 2, 3, 4]
k = 4
print(sol.minimumCost(nums, k))