
class Solution:
    def longestValidParentheses(self, s: str) -> int:
        best = 0

        # forward pass
        start = 0
        cnt = 0
        for i in range(len(s)):
            cnt += 1 if s[i] == '(' else -1
            if cnt == 0:
                best = max(best, i - start + 1)
            elif cnt == -1:
                start = i + 1
                cnt = 0

        # backward pass
        start = len(s) - 1
        cnt = 0
        for i in range(len(s) - 1, -1, -1):
            cnt += 1 if s[i] == ')' else -1
            if cnt == 0:
                best = max(best, start - i + 1)
            elif cnt == -1:
                start = i - 1
                cnt = 0

        return best

sol = Solution()
s = '(()'

print(sol.longestValidParentheses(s))