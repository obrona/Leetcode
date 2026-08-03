from functools import cache

# complicated dp.
# let dp(i, f0, f1, e0, e1) be the state.
# fi is the amount of fuel left in station[i].
# ei is the end time for the cars fuelling.
# invariant: when calling dp(i, ...) car[i] is ready to start fuelling.

# at dp(i, f0, f1, e0, e1) if car[i] decide to fuel at f0, then the waiting time is e0.
# and then e1 becomes max(0, e1 - e0), e0 becomes d, and car[i + 1] becomes ready to start fuelling.
class Solution:
    def minMaxWaitingTime(self, demand: list[int], fuel: list[int]) -> int:

        def merge(best, res):
            if res[0] > best[0] or res[0] == best[0] and res[1] < best[1]:
                return res
            return best
        
        # return (max cars served, max waiting time)
        # invariant: car[i] can start now.
        @cache
        def dp(i: int, f0: int, f1: int, e0: int, e1: int) -> tuple[int,int]:
            if i == len(demand) or demand[i] > max(f0, f1):
                return 0, 0
            
            d = demand[i]
            best = (0, -1)
            if d <= f0:
                cars_served, max_waiting = dp(i + 1, f0 - d, f1, d, max(e1 - e0, 0))
                cars_served += 1
                max_waiting = max(max_waiting, e0)
                best = merge(best, (cars_served, max_waiting))
            if d <= f1:
                cars_served, max_waiting = dp(i + 1, f0, f1 - d, max(e0 - e1, 0), d)
                cars_served += 1
                max_waiting = max(max_waiting, e1)
                best = merge(best, (cars_served, max_waiting))
            return best
        
        c, w = dp(0, fuel[0], fuel[1], 0, 0)
        #print(c, w)
        return -1 if c == 0 else w
        
        
sol = Solution()
demand = [6,8,4,6,5]
fuel = [16,13]
ans = sol.minMaxWaitingTime(demand, fuel)
print(ans)
                
            
