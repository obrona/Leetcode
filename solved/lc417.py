from collections import deque
from itertools import product

# just bfs from the cells adjacent to the pacific / atlantic oceans. 
# then find cells that can be reached from both oceans.

class Solution:
    def __init__(self):
        self.dirs = [[-1, 0], [0, 1], [1, 0], [0, -1]]

    def bfs(self, heights: list[list[int]], inital_pos: list[tuple[int,int]]) -> list[list[bool]]:
        R, C = len(heights), len(heights[0])
        valid = lambda r, c: r >= 0 and r < R and c >= 0 and c < C
        out = [[False for _ in range(len(heights[0]))] for _ in range(len(heights))]
        q = deque[tuple[int,int]]()

        q.extend(inital_pos)
        while len(q) > 0:
            r, c = q.popleft()
            if out[r][c]:
                continue
            out[r][c] = True
            for dr, dc, in self.dirs:
                nr, nc = r + dr, c + dc
                if not valid(nr, nc) or out[nr][nc] or heights[nr][nc] < heights[r][c]:
                    continue
                q.append((nr, nc))

        return out

    def pacificAtlantic(self, heights: list[list[int]]) -> list[list[int]]:
        R, C = len(heights), len(heights[0])
        
        init_pacific = []
        init_pacific.extend((0, c) for c in range(C))
        init_pacific.extend((r, 0) for r in range(1, R))
        pacific_res = self.bfs(heights, init_pacific)

        init_atlantic = []
        init_atlantic.extend((r, C - 1) for r in range(R))
        init_atlantic.extend((R - 1, c) for c in range(C - 1))
        atlantic_res= self.bfs(heights, init_atlantic)

        out = []
        for r, c in product(range(R), range(C)):
            if pacific_res[r][c] and atlantic_res[r][c]:
                out.append([r, c])

        return out