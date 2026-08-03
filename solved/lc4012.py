
# have to binary search prefix sums to get the number of tasks we can complete
# starting from some arbitary index.

class prefix_sums:
    def __init__(self, lst: list[int]):
        self.arr = []
        s = 0
        for i in range(len(lst)):
            s += lst[i]
            self.arr.append(s)

    def range_query(self, l: int, r: int) -> int:
        return self.arr[r] - (self.arr[l - 1] if l > 0 else 0)
    
    def binary_search(self, start: int, limit: int):
        s, e = start, len(self.arr) - 1
        while s < e:
            m = (s + e + 1) >> 1
            sum = self.range_query(start, m)
            if sum <= limit:
                s = m
            else:
                e = m - 1

        return s if self.range_query(start, s) <= limit else -1


class Solution:
    def countTasks(self, tasks: list[int], shifts: list[int]) -> list[int]:
        prefixes = prefix_sums(tasks)
        out = []
        prev_idx, prev_time = -1, 0

        def reset():
            nonlocal prev_idx, prev_time
            prev_idx = -1
            prev_time = 0

        for i in range(len(shifts)):
            time = shifts[i]
            if time < prev_time:
                prev_time -= time
                out.append(len(tasks) - prev_idx)
            
            else:
                time -= prev_time
                start = prev_idx + 1
                if start == len(tasks):
                    reset()
                    out.append(len(tasks) - start)
                    continue
                
                end = prefixes.binary_search(start, time)

                if end == -1:
                    if prev_idx == len(tasks) - 1:
                        reset()
                    else:
                        prev_idx += 1
                        prev_time = tasks[prev_idx] - time
                    out.append(len(tasks) - start)

                else:
                    if end == len(tasks) - 1:
                        reset()
                    else:
                        prev_idx = end + 1
                        prev_time = tasks[prev_idx] - (time - prefixes.range_query(start, end))
                    out.append(len(tasks) - end - 1)

        return out

                
sol = Solution()
tasks = [1,1,3,3,8]
shifts = [2,9,5,3,9]
ans = sol.countTasks(tasks, shifts)
print(ans)
