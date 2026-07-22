from collections import Counter

# given a string, need to find the lexicographically smallest cyclic shift.
# 2 strings are equivalent if the even and odd indices strings are cyclic shifts of each other.
# do this for the even indices and the odd indices, concat the canonical representaions and use dict to store the groups.

def least_rotation(s: str) -> int:
    """Booth's lexicographically minimal string rotation algorithm."""
    n = len(s)
    f = [-1] * (2 * n)
    k = 0
    for j in range(1, 2 * n):
        i = f[j - k - 1]
        while i != -1 and s[j % n] != s[(k + i + 1) % n]:
            if s[j % n] < s[(k + i + 1) % n]:
                k = j - i - 1
            i = f[i]
        if i == -1 and s[j % n] != s[(k + i + 1) % n]:
            if s[j % n] < s[(k + i + 1) % n]:
                k = j
            f[j - k] = -1
        else:
            f[j - k] = i + 1
    return k

def booth_algo(s: str) -> str:
    n = len(s)
    f = [0] * 2 * n
    k = 0 # the starting index of the best candidate found so far.
    
    for j in range(1, 2 * n):
        # here f[0:j - k] contains the KMP values for s[k:j]
        # j is the next character we are comparing, BUT not the start index of the next candidate string.
        
        # since k is the best candidate, the starting index of the next candidate, m, must have s[k] == s[m].
        # if s[m] < s[k] k is not the best candidate, if s[m] > s[k] then we can break immediately.
        # this means we want the KMP value of s[j - 1] w.r.t to k, which is f[j - 1 - k]

        # changing k does not need changing f.
        # because the invariant f[0:j - k] containting the KMP values for s[k:j] is maintained 
        # even when we change k.
        
        i = f[j - 1 - k]
        while i > 0 and s[j % n] != s[(k + i) % n]:
            if s[j % n] < s[(k + i) % n]:
                k = j - i  # found a better starting index, switch k
            i = f[i - 1]

        if i == 0 and s[j % n] != s[k % n]:
            if s[j % n] < s[k % n]:
                k = j
            f[j - k] = 0
        else:
            f[j - k] = i + 1

    return s[k:] + s[:k]


def get_kmp_vals(s: str) -> list[int]:
    n = len(s)
    out = [0] * n
    for i in range(1, n):
        l = out[i - 1]
        while l > 0 and s[l] != s[i]:
            l = out[l - 1]
        if l == 0:
            out[i] = int(s[0] == s[i])
        else:
            out[i] = l + 1
    return out

class Solution:
    def minimumGroups(self, words: list[str]) -> int:
        cnter = Counter[str]()
        for w in words:
            e = ''.join(c for i, c in enumerate(w) if i % 2 == 0)
            o = ''.join(c for i, c in enumerate(w) if i % 2 == 1)
            
            e = booth_algo(e)
            o = booth_algo(o)
            cnter[e + o] += 1

        return len(cnter)


sol = Solution()
words = ["abc","cab","bac","acb","bca","cba"]
print(sol.minimumGroups(words))