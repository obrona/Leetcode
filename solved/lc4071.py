
def num_moves(init: int, next: int) -> int:
    a = (next - init + 10) % 10
    b = 10 - a
    return min(a, b)

class Solution:
    def minRotations(self, n: int, s: str) -> int:
        arr = [ord(c) - ord('0') for c in s]
        backwards = [0] * n
        for i in range(n - 2, -1, -1):
            backwards[i] = backwards[i + 1] + num_moves(arr[i + 1], arr[i])

        print(backwards)


        best = 999999999
        store = 0   
        prev = 0
        for i in range(n):
            best = min(best, store + num_moves(prev, arr[-1]) + backwards[i])

            store += num_moves(prev, arr[i])
            prev = arr[i]

        best = min(best, store)
        return best

sol = Solution()
n = 4
s = '2916'
ans = sol.minRotations(n, s)
print(ans)