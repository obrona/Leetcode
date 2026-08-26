from itertools import zip_longest
from collections.abc import Callable
from collections import Counter

# a substring of s is beautiful if the number of 1's in it is exactly k.
# we can use suffix array to achieve O(nlogn) time complexity.
# problem is given 2 substring ranges [l1, r1) and [l2, r2), 
# how to determine which one is lexicographically smaller.
# WLOG, assume l1 < l2 in the suffix array.
# let len wbe the length of the longest common prefix of s[li] and s[l2].
# just do the casework of 4 different casework.
# case 1: both [l1, r1) and [l2, r2) <= len
# case 2: both of them > len.
# case 3, 4: one of them <= len and other is > len.

# so we do suffix array + lcp + sparse table for range min queries.
# then 2 pointers to get the end index for the beautiful substring starting at index i for i in [0, n - 1].

def get_suffix_array(s: str) -> list[int]:
    N = len(s)
    arr = [ord(c) for c in s]
    store = list(zip_longest(range(N), arr, arr[1:], fillvalue=0))
    store.sort(key=lambda t: (t[1], t[2]))


    for p in range(2, N.bit_length() + 1):
        # compress
        temp = []
        for i, t in enumerate(store):
            if i == 0:
                temp.append([t[0], 1, 0])
            else:
                temp.append([t[0], temp[-1][1] + int(t[1:] != store[i - 1][1:]), 0])

        # update 2nd half.
        d = dict((t[0], t[1]) for t in temp)
        for t in temp:
            second_half = t[0] + (1 << (p - 1))
            t[2] = d[second_half] if second_half < N else 0

        store = temp
        store.sort(key=lambda t: (t[1], t[2]))

    return [t[0] for t in store]

def get_lcp(s: str, sa: list[int]) -> list[int]:
    N = len(s)
    res = [0] * N
    d = dict((p, i) for i, p in enumerate(sa))

    h = 0
    for p in range(N):
        i = d[p]
        if i == 0:
            res[i] = 0
            h = 0
        else:
            prev = sa[i - 1]
            for j in range(h, min(N - p, N - prev)):
                if s[p + j] == s[prev + j]:
                    h += 1
                else:
                    break
            res[i] = h
            h = max(0, h - 1)

    return res

# returns a function(start, end) that returns the min(arr[start:end+1])
def get_sparse_table_querier(arr: list[int], red: Callable[[int,int],int] = min) -> Callable[[int,int],int]:
    N = len(arr)
    max_p = N.bit_length() - 1
    store = [[int(2e9)] * (max_p + 1) for _ in range(N)]

    for p in range(max_p + 1):
        if p == 0:
            for i in range(N):
                store[i][p] = arr[i]
        else:
            for i in range(N):
                second_half = i + (1 << (p - 1))
                if second_half < N:
                    store[i][p] = red(store[i][p - 1], store[second_half][p - 1])
                else:
                    store[i][p] = store[i][p - 1]

    def query(start: int, end: int) -> int:
        p = (end - start + 1).bit_length() - 1
        return red(store[start][p], store[end - (1 << p) + 1][p])

    return query

class Solution:
    def shortestBeautifulSubstring(self, s: str, k: int) -> str:
        sa = get_suffix_array(s)
        lcp = get_lcp(s, sa)
        d = dict((p, i) for i, p in enumerate(sa))
        query = get_sparse_table_querier(lcp)


        # returns -1, 0, 1
        def compare(range1: tuple[int,int], range2: tuple[int,int]) -> int:
            if range1[0] == range2[0]:
                return range1[1] - range2[1]
            
            i1, i2 = d[range1[0]], d[range2[0]]
            len1, len2 = range1[1] - range1[0], range2[1] - range2[0]
            prefix_len = query(min(i1, i2) + 1, max(i1, i2))

            # case 1:
            if len1 <= prefix_len and len2 <= prefix_len:
                return len1 - len2

            # case 2:
            if len1 > prefix_len and len2 > prefix_len:
                return i1 - i2
            
            if len1 <= prefix_len and len2 > prefix_len:
                return 1

            else:
                return -1

        best_range = (-1, -1)
        ptr = 0
        cnter = Counter[str]()
        for i in range(len(s)):
            ptr = max(ptr, i)
            while ptr < len(s) and cnter['1'] < k:
                cnter['1'] += s[ptr] == '1'
                ptr += 1

            if cnter['1'] == k:
                new_range = (i, ptr)
                l = ptr - i
                bl = best_range[1] - best_range[0]
                if best_range == (-1, -1) \
                    or l < bl \
                    or (l == bl and compare(new_range, best_range) < 0):
                    best_range = new_range

            cnter['1'] -= s[i] == '1'

        if best_range == (-1, -1):
            return ''
        else:   
            return s[best_range[0]:best_range[1]]

                
            



'''
s = 'MISSISSIPPI'
sa = get_suffix_array(s)
lcp = get_lcp(s, sa)
print(sa)
print(lcp)

query = get_sparse_table_querier([5, 2, 7, 1, 6])
assert query(1, 3) == 1
assert query(0, 2) == 2
'''

sol = Solution()
s = "001110101101101111"
k = 10
ans = sol.shortestBeautifulSubstring(s, k)
print(ans) 
