import itertools

# quite a complex question.
# we binary search the max length.
# 1. we build dp[p][r][c], which is 1 if the square with top left (r, c) and length 2^p is a filled square.
# do it for p = 0, 1, 2, 3, ... 8
# for p = i, use p = i - 1 to compute faster.
# 2. now we try to find the pairs.
# for (r, c) with length k, get p s.t 2^p >= 1/2 * k, then compute accordingly.
# we keep 2 prefix sums row prefix and col prefix.
# for each candidate square with top left (r, c) we check the right col space and the bottom row space.
# time complexity is O(500 * 500 * log2(500))

def in_bounds(r: int, c: int, R: int, C: int) -> bool:
    return r >= 0 and r < R and c >= 0 and c < C

# return dp[p][r][c] which is 1 if the square with top left (r, c) and length 2^p is a filled square.
def binary_squares(mat: list[list[int]]) -> list[list[list[bool]]]:
    R, C = len(mat), len(mat[0])
    lvls = [[row[:] for row in mat]]
    p = min(R, C).bit_length() - 1
    
    for e in range(1, p + 1):
        grid = [[0 for _ in range(C)] for _ in range(R)]
        prev = lvls[-1]
        for r, c in itertools.product(range(R), range(C)):
            l = 1 << e
            if not in_bounds(r + l - 1, c + l - 1, R, C):
                continue
            h = l >> 1
            grid[r][c] = prev[r][c] and prev[r][c + h] and prev[r + h][c] and prev[r + h][c + h]
        lvls.append(grid)

    return lvls

# given mat, returns grid, where grid[r][c] is 1 if the square with left corner at (r, c) is a square of length k
# guaranteed that the largest p s.t 2^p <= k is in binary_lvls.
def is_square(mat: list[list[int]], binary_lvls: list[list[list[bool]]], k: int) -> list[list[int]]:
    R, C = len(mat), len(mat[0])
    grid = [[False for _ in range(C)] for _ in range(R)]
    p = k.bit_length() - 1

    for r, c in itertools.product(range(R), range(C)):
        if not in_bounds(r + k - 1, c + k - 1, R, C):
            continue
        rr = r + k - (1 << p)
        cc = c + k - (1 << p)
        grid[r][c] = binary_lvls[p][r][c] and binary_lvls[p][r][cc] and binary_lvls[p][rr][c] and binary_lvls[p][rr][cc]

    return grid


def prefix_query(prefix: list[int], l: int, r: int) -> int:
    return prefix[r] - (0 if l == 0 else prefix[l - 1])

def get_row_prefix(grid: list[list[bool]]):
    out = [0 for _ in range(len(grid))]
    store = 0
    for i, r in enumerate(grid):
        store += sum(r)
        out[i] = store
    return out

def get_col_prefix(grid: list[list[bool]]):
    return get_row_prefix(list(zip(*grid)))

class Solution:
    def maxArea(self, mat: list[list[int]]) -> int:
        R, C = len(mat), len(mat[0])
        binary_lvls = binary_squares(mat)

        start, end = 0, min(R, C)
        while start < end:
            mid = (start + end + 1) // 2
            grid = is_square(mat, binary_lvls, mid)
            row_prefix = get_row_prefix(grid)
            col_prefix = get_col_prefix(grid)

            feasible = False
            for r, c in itertools.product(range(R), range(C)):
                if not grid[r][c]:
                    continue

                if prefix_query(row_prefix, r + mid, R - 1) > 0 or prefix_query(col_prefix, c + mid, C - 1) > 0:
                    feasible = True
                    break

            if feasible:
                start = mid
            else:
                end = mid - 1

        return start * start



