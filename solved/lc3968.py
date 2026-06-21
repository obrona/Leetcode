
# is just math.
# 1st just process the letters U, D, L, R and find the final displacement.
# suppose the final displacement is (3, 4) and we have 10 blanks, then just make all 10 blanks up or right.
# if final displacement is (-3, -4) then make all 10 blanks down or left.

class Solution:
    def maxDistance(self, moves: str) -> int:
        x, y, empty = 0, 0, 0
        for c in moves:
            if c == 'U':
                y += 1
            elif c == 'D':
                y -=1 
            elif c == 'R':
                x += 1
            elif c == 'L':
                x -= 1
            else:
                empty += 1

        if x < 0:
            x -= empty
        else:
            x += empty

        return abs(x) + abs(y)