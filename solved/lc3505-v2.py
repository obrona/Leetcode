from sortedcontainers import SortedList
from functools import cache

# when using median, we use the left median if the length is even
# get the score if we take subarray [i, i + x)
# then do dynamic programming.

class State:
    def __init__(self):
        self._elems = SortedList[int]()
        self._left_sum = 0    # sum of elems <= median
        self._right_sum = 0   # sum of elems > median

    def add(self, x: int):
        N = len(self._elems)
        if N == 0:
            self._left_sum += x
            self._elems.add(x)
            return

        median = self._elems[(N - 1) // 2]
        if N % 2 == 0:
            if x < median:
                self._left_sum += x
                self._elems.add(x)
            else:
                self._right_sum += x
                self._elems.add(x)

                to_move = self._elems[len(self._elems) // 2]
                self._left_sum += to_move
                self._right_sum -= to_move

        else:
            if x <= median:
                self._left_sum += x
                self._elems.add(x)

                to_move = self._elems[len(self._elems) // 2]
                self._left_sum -= to_move
                self._right_sum += to_move
            else:
                self._right_sum += x
                self._elems.add(x)

    def remove(self, x: int):
        N = len(self._elems)
        median = self._elems[(N - 1) // 2]
        if N % 2 == 0:
            if x <= median:
                self._left_sum -= x
                self._elems.remove(x)

                to_move = self._elems[len(self._elems) // 2]
                self._left_sum += to_move
                self._right_sum -= to_move
            else:
                self._right_sum -= x
                self._elems.remove(x)

        else:
            if x <= median:
                self._left_sum -= x
                self._elems.remove(x)
            else:
                self._right_sum -= x
                self._elems.remove(x)

                to_move = self._elems[len(self._elems) // 2]
                self._left_sum -= to_move
                self._right_sum += to_move

    def score(self):
        N = len(self._elems)
        I = (N - 1)// 2
        median = self._elems[I]

        return (I + 1) * median - self._left_sum + self._right_sum - (N - I - 1) * median
 
class Solution:
    def minOperations(self, nums: list[int], x: int, k: int) -> int:
        INVALID = int(1e12)
        scores = [0] * (len(nums) - x + 1)
        state = State()
        store = [[None for _ in range(k + 1)] for _ in range(len(scores))]

        for e in nums[0:x]:
            state.add(e)
        
        for i in range(0, len(nums) - x + 1):
            scores[i] = state.score()
            if i + 1 <= len(nums) - x:
                state.remove(nums[i])
                state.add(nums[i + x])

        print(scores)


        def dp(i: int, c: int) -> int:
            if c == 0:
                return 0
            
            if i >= len(nums) - x + 1:
                return INVALID

            if store[i][c] != None:
                return store[i][c]

            take = scores[i] + dp(i + x, c - 1)
            notake = dp(i + 1, c)
            store[i][c] = min(take, notake)
            return store[i][c]

        return dp(0, k)


sol = Solution()
nums = [5,-2,1,3,7,3,6,4,-1]
x = 3
k = 2

ans = sol.minOperations(nums, x, k)
print(ans)

            

        