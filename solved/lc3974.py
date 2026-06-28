import heapq
# get the top k, as long mult is > 1 we multiply.

class Solution:
    def maxSum(self, nums: list[int], k: int, mul: int) -> int:
        top_k = heapq.nlargest(k, nums)
        sum = 0
        for x in top_k:
            if mul > 1:
                sum += x * mul
                mul -= 1
            else:
                sum += x
        return sum