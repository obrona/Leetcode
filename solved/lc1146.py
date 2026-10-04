class SnapshotArray:

    def __init__(self, length: int):
        self.curr_snapshot: int = 0
        self.store: list[list[list[int]]] = [[[0, 0]] for _ in range(length)] # [snap_id, val]
 
    def set(self, index: int, val: int) -> None:
        last = self.store[index][-1]
        if last[0] == self.curr_snapshot:
            last[1] = val
        else:
            self.store[index].append([self.curr_snapshot, val])
        

    def snap(self) -> int:
        temp = self.curr_snapshot
        self.curr_snapshot += 1
        return temp
        

    # binary search the version.
    # the snap_id may not exist as we can call snap consecutively.
    # so we want the val with the largest snap_id <= snap_id
    def get(self, index: int, snap_id: int) -> int:
        s = 0
        e = len(self.store[index]) - 1

        while s < e:
            m = (s + e + 1) // 2
            curr_snap_id, _ = self.store[index][m]

            if curr_snap_id <= snap_id:
                s = m
            else:
                e = m - 1

        curr_snap_id, val = self.store[index][s]
        return val

sol = SnapshotArray(3)
sol.set(0, 5)
sol.snap()
sol.set(0, 6)
print(sol.get(0, 0))