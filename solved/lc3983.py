
# let front pass for s[0..i] = j which means j is the leftmost index s.t
# s[0..i] is a subsequence of t[0..j]
# let back pass for s[i..end] = k which means k is the rightmost index s.t
# s[i..end] is a subsequence of t[k..end]

# the front index must be < back index - 1, must have 1 charater for s[i] to change to.

def front_pass(s: str, t: str) -> list[int]:
    out = []
    p = 0
    for c in s:
        if p >= len(t):
            out.append(len(t))
            continue

        while p < len(t) and c != t[p]:
            p += 1
        out.append(p)
        if p < len(t):
            p += 1

    return out

def back_pass(s: str, t: str) -> list[int]:
    out = [-1] * len(s)
    p = len(t) - 1
    for i in range(len(s) - 1, -1, -1):
        if p == -1:
            continue
        while p > -1 and s[i] != t[p]:
            p -= 1
        out[i] = p
        if p > -1:
            p-= 1
    return out


class Solution:
    def canMakeSubsequence(self, s: str, t: str) -> bool:
        if len(s) > len(t):
            return False
        front = front_pass(s, t)
        back = back_pass(s, t)
        #print(front, back)
        for i in range(len(s)):
            f = -1 if i == 0 else front[i - 1]
            b = len(t) if i == len(s) - 1 else back[i + 1]
            if f < b - 1:
                #print(i, f, b)
                return True
        return False
 
sol = Solution()
s = 'qo'
t = 'npnmq'
print(sol.canMakeSubsequence(s, t))