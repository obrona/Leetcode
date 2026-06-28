

def merge_intervals(intervals: list[list[int]]) -> list[list[int]]:
    if len(intervals) == 0:
        return []
    
    lst = sorted(intervals, key=lambda i: (i[0], -i[1]))
    out = []
    s, e = lst[0][0], lst[0][1]
    for l, r in lst[1:]:
        if l <= e + 1:
            e = max(e, r)
        else:
            out.append([s, e])
            s, e = l, r
    out.append([s, e])
    return out



class Solution:
    def filterOccupiedIntervals(self, occupiedIntervals: list[list[int]], freeStart: int, freeEnd: int) -> list[list[int]]:
        merged = merge_intervals(occupiedIntervals)
        out = []
        for l, r in merged:
            if r < freeStart or l > freeEnd:
                out.append([l, r])
                continue

            if l < freeStart:
                out.append([l, freeStart - 1])
            if r > freeEnd:
                out.append([freeEnd + 1, r])

        return out
    
sol = Solution()
occupiedIntervals = [[2,6],[4,8],[10,10],[10,12],[14,16]]
freeStart = 7
freeEnd = 11

ans = sol.filterOccupiedIntervals(occupiedIntervals, freeStart, freeEnd)
print(ans)