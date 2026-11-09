class Solution:
    def findMismatchedSegments(self, s1: str, s2: str) -> list[list[str]]:
        out = []
        p = 0
        while p < len(s1):
            s = p
            while p < len(s1) and s1[p] != s2[p]:
                p += 1

            if s == p:
                p += 1
            else:
                out.append((s1[s:p], s2[s:p]))
        return out

sol = Solution()
s1 = "earth"
s2 = "empty"
print(sol.findMismatchedSegments(s1, s2))