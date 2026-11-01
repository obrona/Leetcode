from collections import deque

# bitmask dp.
# we can use alpha beta pruning to reduce search time.
# dp(ipos, bitmask)
# side = 0 means it is alice who is trying to maximise.
# side = 1 means it is bob who is trying to minimise.
# we can remove side. recover side by storing how many pawns have been killed
# even # of pawns killed = Alice
# odd # of pawns killed = Bob
# ipos is index of position. 
# the positions we care about are the positions of the pawns + initial position of the knight.

# cannot use alpha beta pruning. Because dp needs the correct val, but with pruning we only return a 
# upper/lower bound

NEG_INF = -999999999
POS_INF = 999999999

KNIGHT_DIRECTIONS = [
    (2, 1), (2, -1),
    (-2, 1), (-2, -1),
    (1, 2), (1, -2),
    (-1, 2), (-1, -2),
]

def in_bounds(r: int, c: int) -> bool:
    return r >= 0 and r < 50 and c >= 0 and c < 50

def set_bits(mask: int):
    while mask:
        low = mask & -mask
        yield low.bit_length() - 1
        mask &= mask - 1

def single_source_shortest_path(r: int, c: int) -> list[list[int]]:
    dists = [[None for _ in range(50)] for _ in range(50)]
    pushed = [[False for _ in range(50)] for _ in range(50)]
    wave = 0
    q = deque[tuple[int,int]]()

    pushed[r][c] = True
    q.append((r, c))

    while (l := len(q)) > 0:
        for _ in range(l):
            nr, nc = q.popleft()
            if dists[nr][nc] == None:
                dists[nr][nc] = wave

            for dr, dc in KNIGHT_DIRECTIONS:
                nnr, nnc = nr + dr, nc + dc
                if not in_bounds(nnr, nnc) or pushed[nnr][nnc]:
                    continue
                pushed[nnr][nnc] = True
                q.append((nnr, nnc))

        wave += 1

    return dists

class Solution:
    def maxMoves(self, kx: int, ky: int, positions: list[list[int]]) -> int:
        N = len(positions)
        BM = 1 << len(positions)
        positions.append([kx, ky])
        dist_store = [single_source_shortest_path(x, y) for x, y in positions]
        dp_store = [None] * len(positions) * BM

        def to_index(ipos: int, bm: int) -> int:
            return ipos * BM + bm

        def dp(ipos: int, bm: int) -> int:
            side = (N - bm.bit_count()) & 1
            idx = to_index(ipos, bm)

            if dp_store[idx] != None:
                return dp_store[idx]

            if bm == 0:
                dp_store[idx] = 0
                return 0

            if side == 0:
                best = NEG_INF
                for nipos in set_bits(bm):
                    nr, nc = positions[nipos]
                    res = dist_store[ipos][nr][nc] + dp(nipos, bm - (1 << nipos))
                    best = max(best, res)
                
                dp_store[idx] = best
                return best

            else:
                best = POS_INF
                for nipos in set_bits(bm):
                    nr, nc = positions[nipos]
                    res = dist_store[ipos][nr][nc] + dp(nipos, bm - (1 << nipos))
                    best = min(best, res)
                
                dp_store[idx] = best
                return best

        return dp(len(positions) - 1, BM - 1)

sol = Solution()
kx = 0
ky = 2
positions = [[1,1],[2,2],[3,3]]

ans = sol.maxMoves(kx, ky, positions)

print(ans)

            


        



