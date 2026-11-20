from functools import cache

class Solution:
    def canMeasureWater(self, x: int, y: int, target: int) -> bool:

        def next_states(cx: int, cy: int) -> list[tuple[int,int]]:
            out = []
            
            out.append((x, cy))
            out.append((cx, y))

            out.append((0, cy))
            out.append((cx, 0))

            txy = min(cx, y - cy)
            out.append((cx - txy, cy + txy))
            tyx = min(cy, x - cx)
            out.append((cx + tyx, cy - tyx))

            return out


        def can_end(cx: int, cy: int) -> bool:
            return cx == target or cy == target or cx + cy == target


        visited = set[tuple[int,int]]()

        def dfs(cx: int, cy: int) -> bool:
            visited.add((cx, cy))
            return can_end(cx, cy) or max((dfs(nx, ny) for nx, ny in next_states(cx, cy) if (nx, ny) not in visited), default=False)

        return dfs(0, 0)


sol = Solution()
print(sol.canMeasureWater(3, 4, 5))
