
# intuition says it is greedy.

class Solution:
    def maxDepthAfterSplit(self, seq: str) -> list[int]:
        a = 0
        max_a = 0
        b = 0
        max_b = 0
        out = []

        for c in seq:
            if c == '(':
                if a <= b:
                    a += 1
                    max_a = max(max_a, a)
                    out.append(0)
                else:
                    b += 1
                    max_b = max(max_b, b)
                    out.append(1)

            else:
                if a >= b:
                    a -= 1
                    out.append(0)
                else:
                    b -=1 
                    out.append(1)

        return out
