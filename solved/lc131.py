
# classic backtracking problem.
# use a helper struct to compute all palindromes at once at the start.

class palindrome_checker:
    def __init__(self, s: str):
        self.store = [[False for _ in range(len(s))] for _ in range(len(s))]

        for i in range(len(s)):
            self.store[i][i] = True
        
        for i in range(len(s) - 1):
            self.store[i][i + 1] = s[i] == s[i + 1]

        for l in range(3, len(s) + 1):
            for i in range(len(s) - l + 1):
                self.store[i][i + l - 1] = s[i] == s[i + l - 1] and self.store[i + 1][i + l - 2]


    def is_palindrome(self, l: int, r: int) -> bool:
        return self.store[l][r]

class Solution:
    def partition(self, s: str) -> list[list[str]]:
        store: list[list[str]] = []
        stack: list[str] = []
        checker = palindrome_checker(s)

        def helper(s: str, i: int):
            if i == len(s):
                store.append(stack.copy())
                return
            
            for j in range(i, len(s)):
                if not checker.is_palindrome(i, j):
                    continue
                stack.append(s[i:j + 1])
                helper(s, j + 1)
                stack.pop()

        helper(s, 0)
        return store
    
sol = Solution()
s = 'aab'
ans = sol.partition(s)
print(ans)
                