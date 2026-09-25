
# for each character store the positions where it appears.
# then for each index i, binary search the earliest appearence of 'a', 'b', 'c'.
# let the index be j, then j, j+1, j+2 ... n - 1 are valid endpoints.

# get smallest element >= key
def binary_search(key: int, lst: list[int]) -> int | None:
    if len(lst) == 0:
        return None
    
    s = 0
    e = len(lst) - 1

    while s < e:
        m = (s + e) >> 1
        if lst[m] < key:
            s = m + 1
        else:
            e = m

    return lst[s] if lst[s] >= key else None

    

class Solution:
    def numberOfSubstrings(self, s: str) -> int:
        store: dict[str, list[int]] = {'a': [], 'b': [],  'c': []}
        for i, c in enumerate(s):
            store[c].append(i)

        #print(store)
        cnt = 0
        for i in range(len(s)):
            ends = [binary_search(i, store[c]) for c in ['a', 'b', 'c']]
            #print(ends)
            if any(x == None for x in ends):
                continue
            #print(i, max(ends))
            cnt += len(s) - max(ends)

        return cnt

sol = Solution()
s = "abcabc"
ans = sol.numberOfSubstrings(s)
print(ans)