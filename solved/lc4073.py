import numpy as np

# basically it is asking for the num of ways to partition string into
# odd length 'unit' strings, consecutive strings must change character.
# eg abab -> a b a b
# aaab -> aaa b
# we can flip i.e aaa b -> bbb a.
# so we find the underlying recurrence relation then we *2.
# so f(n) = f(n - 1) + f(n - 3) + f(n - 5) ...
# f(n - 2) = f(n - 3) + f(n - 5) ...
# so f(n) = f(n - 1) + f(n - 2)
# must find fibonacci sequence in O(logn).

# [f(n), f(n - 1)] = [f(n - 1), f(n - 2)] *  [[1, 1],
#                                             [1, 0]]]
# [f(1), f(0)] = [1, 1]

def matrix_power(matrix, p: int):
    if p == 0:
        return np.identity(2, dtype=np.int64)
    elif p & 1:
        return (matrix @ matrix_power(matrix, p - 1)) % int(1e9 + 7)
    else:
        res = matrix_power(matrix, p >> 1)
        return (res @ res) % int(1e9 + 7)

class Solution:
    def countGoodStrings(self, n: int) -> int:
        matrix = np.array([[1, 1], [1, 0]])
        init = np.array([[1], [0]])
        #print(matrix_power(matrix, 3))
        res = matrix_power(matrix, n - 1) @ init
        #print(res)
        return int((2 * res[0][0]) % int(1e9 + 7))

sol = Solution()
n = 79
print(sol.countGoodStrings(n))
