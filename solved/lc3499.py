from collections import Counter

# group the sequence into (type, cnt).
# eg 1001001 -> (1, 1) (0, 2) (1, 1) (0, 2) (1, 1).
# the max result is the maximum of 2 0s group seperated by 1 1s group.

class Solution:
    def maxActiveSectionsAfterTrade(self, s: str) -> int:
        cnts = Counter(s)
        store: list[tuple[str,int]] = []
        p = 0
        while p < len(s):
            c = s[p]
            start = p
            while p < len(s) and s[p] == c:
                p += 1
            store.append((c, p - start))

        lst = [tup for tup in store if tup[0] == '0']
        if len(lst) <= 1:
            return cnts['1']
        
        lst = list(zip(lst, lst[1:]))
        to_add = max(t[0][1] + t[1][1] for t in lst)

        
        return cnts['1'] + to_add
    

sol = Solution()
s = '0100'
print(sol.maxActiveSectionsAfterTrade(s))
