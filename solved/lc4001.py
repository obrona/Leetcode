# simple 2 pointers.

class Solution:
    def aggregateTimeSeries(self, series1: list[list[int]], series2: list[list[int]]) -> list[list[int]]:
        out = []
        p1, p2 = 0, 0

        def same():
            nonlocal p1, p2
            t1, v1 = series1[p1]
            _, v2 = series2[p2]
            out.append([t1, v1 + v2])
            p1 += 1
            p2 += 1

        def p0_smaller():
            nonlocal p1
            t1, v1 = series1[p1]
            _, v2 = series2[p2] if p2 < len(series2) else [0, 0]
            out.append([t1, v1 + v2])
            p1 += 1

        def p1_smaller():
            nonlocal p2
            _, v1 = series1[p1] if p1 < len(series1) else [0, 0]
            t2, v2 = series2[p2]
            out.append([t2, v1 + v2])
            p2 += 1

        while p1 < len(series1) and p2 < len(series2):
            t1 = series1[p1][0]
            t2 = series2[p2][0]
            if t1 == t2:
                same()
            elif t1 < t2:
                p0_smaller()
            else:
                p1_smaller()

        while p1 < len(series1):
            p0_smaller()

        while p2 < len(series2):
            p1_smaller()

        return out
    
sol = Solution()
series1 = [[1,3],[4,1]]
series2 = [[2,2],[5,2]]

ans = sol.aggregateTimeSeries(series1, series2)
print(ans)