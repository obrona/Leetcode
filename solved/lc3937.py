import itertools

# do modulo k for every elem in nums first.
# partition elems into 2 sets depending on whether their index is even or odd.
# because modulo distance is circular, it is not valid to always take the median.
# we just try all possiblities, since k <= 100

def modulo_dist(a: int, b: int, k: int):
    if a > b:
        a, b = b, a
    return min(b - a, a + k - b)
    
class Solution:
    def minOperations(self, nums: list[int], k: int) -> int:
        even, odd = [], []
        for i, x in enumerate(nums):
            if i % 2 == 0:
                even.append(x % k)
            else:
                odd.append(x % k)
        
        best = 999999999
        for x, y in itertools.product(range(k), range(k)):
            if x == y:
                continue
            best = min(best, sum(modulo_dist(n, x, k) for n in even) + sum(modulo_dist(n, y, k) for n in odd))
        return best

