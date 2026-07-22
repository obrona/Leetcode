from functools import cache

# either take coins[i] or not.
# is just take, no take dp.
class Solution:
    def coinChange(self, coins: list[int], amount: int) -> int:
        coins.sort()

        @cache
        def dp(i: int, left: int) -> int:
            if left == 0:
                return 0
            if i == len(coins) or left < coins[i]:
                return 999999999
            
            return min(1 + dp(i, left - coins[i]), dp(i + 1, left))
        
        ans = dp(0, amount)
        return ans if ans < 999999999 else -1
    
sol = Solution()
coins = [1,2,5]
amount = 11
print(sol.coinChange(coins, amount))

