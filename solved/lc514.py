from functools import cache
# dp(idx, idx of ring at 12.00)
# it is optimal to go to the 1st left, right char we seek.

class Solution:
    def findRotateSteps(self, ring: str, key: str) -> int:
        @cache 
        def dp(i: int, ptr: int) -> int:
            if i == len(key):
                return 0

            if key[i] == ring[ptr]:
                return 1 + dp(i + 1, ptr)

            best = 999999999
            for d in range(1, len(ring)):
                next_right_ring_idx = (ptr + d) % len(ring)
                if key[i] == ring[next_right_ring_idx]:
                    best = min(best, d + 1 + dp(i + 1, next_right_ring_idx))

                next_left_ring_idx = (ptr - d) % len(ring)
                if key[i] == ring[next_left_ring_idx]:
                    best = min(best, d + 1 + dp(i + 1, next_left_ring_idx))

            return best

        return dp(0, 0)


sol = Solution()
ring = 'godding'
key = 'gd'
ans = sol.findRotateSteps(ring, key)
print(ans)