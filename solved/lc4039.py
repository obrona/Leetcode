# just use python pow() to handle modulo exponential.

class Solution:
    def sumDecoded(self, nums: list[int]) -> int:
        MOD = int(1e9 + 7)
        ans = 0
        for n in nums:
            w = n % 10
            d = n // 10

            l = len(str(d))
            m = pow(10, l - w)
            x = d // m
            y = d % m

            
            ans += pow(x, y, MOD)
            ans %= MOD
        return ans

sol = Solution()
nums = [2522,2101]
ans = sol.sumDecoded(nums)
print(ans)
