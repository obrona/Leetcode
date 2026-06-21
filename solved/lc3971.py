import math

# interesting binary search problem.
# we binary search the threshold, i.e all selected elems >= threshold.
# define the optimal threshold as when there exist >= 1 elem = threshold.
# lemma 1: for every arithmetic sequence, the next elem to be chosen is <= threshold
# otherwise we can replace the smallest element chosen with a better value.
# the threshold is >= 1, there is no point choosing a non-positive integer.

# so we binary search the threshold.
# if have too many values, then the threshold has to go higher
# if too little, it has go lower.
# if we hit m elems, but no chosen elem = threshold then we can go higher

# in the optimal solution, it could be there is some arithmetic sequence with no chosen elems.
# it can be that there are too many elems = threshold so we need to subtract some.

# returns # of elems >= t, sum of elems >= t, smallest elem = t
def helper(v: int, d: int, t: int) -> tuple[int,int,bool]:
    if t > v:
        return 0, 0, False
    
    k = (v - t) // d
    s = (v + v - k * d) * (k + 1) // 2
    return k + 1, s, v - k * d == t

class Solution:
    def maxTotalValue(self, value: list[int], decay: list[int], m: int) -> int:
        start, end = 1, max(value)
        while start < end:
            mid = (start + end) >> 1
            results = [helper(v, d, mid) for v, d in zip(value, decay)]
            cnt = sum(map(lambda t: t[0], results))
            
            #print(mid, cnt)
            #total = sum(map(lambda t: t[1], results))

            # it is fine if cnt > m, but cnt - cnt_hit_mid must be <= m
            # so that if we exceed m, we just remove some of the elems at the threshold
            cnt_hit_mid = sum(map(lambda t: t[2], results))

            valid_cnt = cnt - cnt_hit_mid

            if valid_cnt > m:
                start = mid + 1
            else:
                end = mid

        results = [helper(v, d, start) for v, d in zip(value, decay)]
        cnt = sum(map(lambda t: t[0], results))
        total = sum(map(lambda t: t[1], results))
        cnt_hit_mid = sum(map(lambda t: t[2], results))
        ans = total if cnt <= m else total - (cnt - m) * start
        return ans % int(1e9 + 7)
    
sol = Solution()
value = [7,2,2]
decay = [3,2,1]
m = 2
print(sol.maxTotalValue(value, decay, m))