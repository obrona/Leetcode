# simple bookwork.
# store the curr pos and the curr dir.
# then use the same dir vector if possible, if not you need to change the dir vector.

class Solution:
    def generateMatrix(self, n: int) -> list[list[int]]:
        dirs = [(0, 1), (1, 0), (0, -1), (-1, 0)]

        curr_pos = (0, 0)
        dir = (0, 1)
        grid = [[0 for _ in range(n)] for _ in range(n)]

        def in_bounds(r: int, c: int) -> bool:
            return r >= 0 and r < n and c >= 0 and c < n

        for i in range(n**2):
            grid[curr_pos[0]][curr_pos[1]] = i + 1
            if i == n**2 - 1:
                break

            nr, nc = curr_pos[0] + dir[0], curr_pos[1] + dir[1]
            if not in_bounds(nr, nc) or grid[nr][nc] != 0:
                idx = dirs.index(dir)
                idx = (idx + 1) % 4
                dir = dirs[idx]
                nr, nc = curr_pos[0] + dir[0], curr_pos[1] + dir[1]

            curr_pos = (nr, nc)

        return grid

sol = Solution()
n = 3
ans = sol.generateMatrix(n)
print(ans)


