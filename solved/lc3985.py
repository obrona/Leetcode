from typing import Callable
from collections.abc import Sequence

# all the elems in the array are positive.
# use manacher algoritm to find per index, the longest palindrome centered at that index.
# then use prefix sum to get the sum.
# have to handle odd length / even length palindrome seperately.

def manacher_odd(s: Sequence) -> list[int]:
    valid_d = lambda i, d: i - d > -1 and i + d < len(s) and s[i - d] == s[i + d]

    p, r = -1, -1
    out = [0] * len(s)
    for i in range(len(s)):
        if i > r:
            p = i
            d = 1
            while valid_d(i, d):
                d += 1
            r = p + d - 1
            out[i] = d - 1

        else:
            m = p - (i - p)
            d = out[m]
            if i + d < r:
                out[i] = d
            else:
                d = r - i
                while valid_d(i, d):
                    d += 1
                out[i] = d - 1
                
                if i + d - 1 > r:
                    p = i
                    r = i + d - 1
    return out

# out[i] means the center is i, i + 1
def manacher_even(s: Sequence) -> list[int]:
    is_valid_d = lambda i, d: i - d > -1 and i + 1 + d < len(s) and s[i - d] == s[i + 1 + d]
    is_valid_center = lambda i: i + 1 < len(s) and s[i] == s[i + 1]

    # if r = -1, means s[p] != s[p + 1]
    p, r = -1, -1
    # out[i] = -1 means s[i] != s[i + 1]
    out = [-1] * len(s) 

    for i in range(len(s)):
        if i > r:
            p = i
            if not is_valid_center(i):
                r = -1
                out[i] = -1
            else:
                d = 1
                while is_valid_d(i, d):
                    d += 1
                out[i] = d - 1
                r = i + 1 + d - 1

        else:
            if not is_valid_center(i):
                out[i] = -1
            else:
                # the mirror is different due to how center is defined
                m = p - (i - (p + 1)) - 1
                print(i, m)

                d = out[m]
                
                if i + 1 + d < r:
                    out[i] = d
                else:
                    d = r - i - 1
                    while is_valid_d(i, d):
                        d += 1
                    out[i] = d - 1
                    
                    if i + d - 1 + 1 > r:
                        p = i
                        r = i + d - 1 + 1
    return out

def get_subarray_sum(nums: list[int]) -> Callable[[int,int], int]:
    res = [0] * len(nums)
    store = 0
    for i, x in enumerate(nums):
        store += x
        res[i] = store

    return lambda l, r: res[r] - (0 if l == 0 else res[l - 1])
                
class Solution:
    def getSum(self, nums: list[int]) -> int:
        prefix_func = get_subarray_sum(nums)
        odd = manacher_odd(nums)
        even = manacher_even(nums)
        best = 0

        for i, x in enumerate(odd):
            l = i - x
            r = i + x
            best = max(best, prefix_func(l, r))

        for i, x in enumerate(even):
            if x == -1:
                continue
            l = i - x
            r = i + 1 + x
            best = max(best, prefix_func(l, r))

        return best


sol = Solution()
nums = [1,2,3,2,1,5,6]
print(sol.getSum(nums))