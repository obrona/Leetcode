
# just practice manacher algorithm.

def manacher_odd(s: str) -> list[int]:
    N = len(s)
    out = [0] * N
    p = 0
    r = -1
    for i in range(N):
        if i > r:
            p = i
            d = 1
            while d < min(N - i, i + 1) and s[i + d] == s[i - d]:
                d += 1
            out[i] = d - 1
            r = i + d - 1

        else:
            m = p - (i - p)
            if i + out[m] < r:
                out[i] = out[m]
            else:
                p = i
                d = r - i + 1
                while d < min(N - i, i + 1) and s[i + d] == s[i - d]:
                    d += 1
                out[i] = d - 1
                r = i + d - 1
    return out

def manacher_even(s: str) -> list[int]:
    N = len(s)
    out = [-1] * N
    p = 0
    r = -1
    for i in range(1, N):
        if s[i - 1] != s[i]:
            continue

        if i > r:
            p = i
            d = 1
            while d < min(N - i, i) and s[i - 1 - d] == s[i + d]:
                d += 1
            out[i] = d - 1
            r = i + d - 1

        else:
            m = p - 1 - (i - p - 1)
            if i + out[m] < r:
                out[i] = out[m]
            else:
                p = i
                d = r - i + 1
                while d < min(N - i, i) and s[i - 1 - d] == s[i + d]:
                    d += 1
                out[i] = d - 1
                r = i + d - 1
    return out

class Solution:
    def longestPalindrome(self, s: str) -> str:
        odd = manacher_odd(s)
        even = manacher_even(s)

        best_idx = -1
        best_len = 0
        for i in range(len(s)):
            l = max(1 + 2 * odd[i], 2 * (even[i] + 1))
            if l > best_len:
                best_idx = i
                best_len = l

        if best_len % 2 == 1:
            return s[best_idx - best_len // 2:best_idx + best_len // 2 + 1]
        else:
            return s[best_idx - best_len // 2:best_idx + best_len // 2]

        
sol = Solution()
s = 'cbbd'
print(sol.longestPalindrome(s))