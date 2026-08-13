# simple backtracking.
# for optimisation store which row, col and diag are already consume, insteed of comparing to each of the queens.

class Solution:
    def totalNQueens(self, n: int) -> int:
        cols_used = [False] * n
        left_diags_used = [False] * (2 * n - 1)
        right_diags_used = [False] * (2 * n - 1)

        def left_diag_idx(r: int, c: int):
            return r + c

        def right_diag_idx(r: int, c: int):
            return r + n - 1 - c

        def dp(row: int) -> int:
            if row == n:
                return 1

            res = 0
            for c in range(n):
                l = left_diag_idx(row, c)
                rd = right_diag_idx(row, c)
                if cols_used[c] or left_diags_used[l] or right_diags_used[rd]:
                    continue

                cols_used[c] = left_diags_used[l] = right_diags_used[rd] = True
                res += dp(row + 1)
                cols_used[c] = left_diags_used[l] = right_diags_used[rd] = False
            return res

        return dp(0)

sol = Solution()
print(sol.totalNQueens(4))
