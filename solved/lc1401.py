
# case 1: if center of circle is already inside the square done.
# case 2:
# divide the space into 8 regions, i.e top, top right, right, down right, down, down left, left, top left
# if centre is in right, left, top, down, the shortest distance is the perpendicular distance from centre to line.
# if centre is in the diagonals, then the shortest distance is to the corners.

class Solution:
    def checkOverlap(self, radius: int, xCenter: int, yCenter: int, x1: int, y1: int, x2: int, y2: int) -> bool:
        def case_1(xCenter: int, yCenter: int, x1: int, y1: int, x2: int, y2: int) -> bool:
            cx = xCenter - x1
            cy = yCenter - y1
            len_square = x2 - x1
            return 0 <= cx <= len_square and 0 <= cy <= len_square

        def case_2(xCenter: int, yCenter: int, x1: int, y1: int, x2: int, y2: int) -> bool:
            # top
            if x1 <= xCenter <= x2 and yCenter >= y2:
                return yCenter - y2 <= radius

            # right
            if y1 <= yCenter <= y2 and xCenter >= x2:
                return xCenter - x2 <= radius

            # bottom
            if x1 <= xCenter <= x2 and yCenter <= y1:
                return y1 - yCenter <= radius

            # left
            if y1 <= yCenter <= y2 and xCenter <= x1:
                return x1 - xCenter <= radius

            # top right
            if xCenter >= x2 and yCenter >= y2:
                return (xCenter - x2)**2 + (yCenter - y2)**2 <= radius**2

            # bottom right
            if xCenter >= x2 and yCenter <= y1:
                return (xCenter - x2)**2 + (yCenter - y1)**2 <= radius**2

            # bottom left
            if xCenter <= x1 and yCenter <= y1:
                return (xCenter - x1)**2 + (yCenter - y1)**2 <= radius**2

            # top left
            if xCenter <= x1 and yCenter >= y2:
                return (xCenter - x1)**2 + (yCenter - y2)**2 <= radius**2

        return case_1(xCenter, yCenter, x1, y1, x2, y2) or case_2(xCenter, yCenter, x1, y1, x2, y2)
