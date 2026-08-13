from functools import cache
import itertools

# just dp.
# let dp(c1, c2, idx) means finger 1 is at c1, finger 2 is at c2, and we are trying to make s[idx:]

class Solution:
    def minimumDistance(self, word: str) -> int:
        chars = [chr(i + ord('A')) for i in range(26)]

        def char_to_pos(c: str) -> tuple[int, int]:
            d = ord(c) - ord('A')
            return (d // 6, d % 6)

        def pos_between_char(c1: str, c2: str) -> int:
            x1, y1 = char_to_pos(c1)
            x2, y2 = char_to_pos(c2)
            return abs(x1 - x2) + abs(y1 - y2)

        @cache
        def dp(c1: str, c2: str, idx: int) -> int:
            if idx == len(word):
                return 0

            f1 = pos_between_char(c1, word[idx]) + dp(word[idx], c2, idx + 1)
            f2 = pos_between_char(c2, word[idx]) + dp(c1, word[idx], idx + 1)
            return min(f1, f2)

        return min(dp(c1, c2, 0) for c1, c2 in itertools.product(chars, chars))

sol = Solution()
word = 'CAKE'
ans = sol.minimumDistance(word)
print(ans)