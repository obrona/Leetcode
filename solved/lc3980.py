
# dynamic programming
# let dp(i, d) be the min num of ops to change s1[i..n] to s2[i..n]
# d is the current value of s1[i]
# if equal skip
# if 0 to 1 just do it
# but if 1 to 0, then we can either pair with the prev elem or the next elem.

# the sequence of operations in the optimal solution can be recreated in this dp.
# i don't know how to prove this.
# but let say we work from the back, i.e change i to 1 then change i + 1, i to 00
# is the same as change i to 1 and change i, i + 1 to 0

# impossible case is only when len(s1) = 1 and s1 = 1 and s2 = 0

class Solution:
    def __init__(self):
        self.N: int | None = None
        self.store: list[list[int]] = None

    def dp(self, i: int, d: int, s1: list[int], s2: list[int]) -> int:
        if i == self.N:
            return 0
        
        if self.store[i][d] != -1:
            return self.store[i][d]
        
       
        next = -1 if i + 1 >= len(s1) else s1[i + 1]
        
        if d == s2[i]:
            self.store[i][d] = self.dp(i + 1, next, s1, s2)
            return self.store[i][d]
        
        if d == 0:
            self.store[i][d] = 1 + self.dp(i + 1, next, s1, s2)
            return self.store[i][d]
        
        back, front = int(1e9), int(1e9)
        if i < len(s1) - 1:
            c = 1 if s1[i + 1] == 0 else 0
            front = c + 1 + self.dp(i + 1, 0, s1, s2)
        if i > 0:
            # if s2[i - 1] is 1, 11->00 then 0->1. 
            # if s2[i - 1] is 0, 0->1 then 11->00.
            back = 2 + self.dp(i + 1, next, s1, s2)
        self.store[i][d] = min(back, front)
        return self.store[i][d]
    

    def minOperations(self, s1: str, s2: str) -> int:
        if len(s1) == 1 and s1 == '1' and s2 == '0':
            return -1
        
        self.N = len(s1)
        self.store = [[-1, -1] for _ in range(len(s1))]
        
        lst1 = [ord(c) - ord('0') for c in s1]
        lst2 = [ord(c) - ord('0') for c in s2]
        return self.dp(0, lst1[0], lst1, lst2)
    
sol = Solution()
s1 = '01'
s2 = '10'
print(sol.minOperations(s1, s2))