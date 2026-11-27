class Solution:
    def minimumCost(self, cost1: int, cost2: int, costBoth: int, need1: int, need2: int) -> int:
        if costBoth <= min(cost1, cost2):
            return max(need1, need2) * costBoth

        if cost1 <= costBoth <= cost2:
            if need1 < need2:
                return costBoth * need1 + (need2 - need1) * costBoth
            else:
                return costBoth * need2 + cost1 * (need1 - need2)

        if cost2 <= costBoth <= cost1:
            if need1 < need2:
                return costBoth * need1 + cost2 * (need2 - need1)
            else:
                return costBoth * need2 + costBoth * (need1 - need2)

        if costBoth < cost1 + cost2:
            return costBoth * min(need1, need2) + cost1 * (need1 - min(need1, need2)) + cost2 * (need2 - min(need1, need2))
        
        if costBoth >= cost1 + cost2:
            return need1 * cost1 + need2 * cost2

        return -1