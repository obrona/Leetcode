
# simple greedy, pair the biggest discounts with the most expensive prices.

class Solution:
    def minPrice(self, prices: list[int], discounts: list[int]) -> float:
        prices.sort(reverse=True)
        discounts.sort(reverse=True)
        discounts.extend([0 for _ in range(len(prices) - len(discounts))])
        return sum(p * (100 - d) / 100 for p, d in zip(prices, discounts))

    
        