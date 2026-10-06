from collections import deque

# for O(1) for each operation, use 2 queue
# 1 queue for the 1st half, another queue for the 2nd half.
# then all push/pop on front/middle/back are just operations on the front/back 
# of the respective queue.
# invariant:
# len of 1st half is either equal or 1 less than len of 2nd half.

class FrontMiddleBackQueue:

    def __init__(self):
        self.first_half = deque[int]()
        self.second_half = deque[int]()
        

    def pushFront(self, val: int) -> None:
        self.first_half.appendleft(val)
        if len(self.first_half) > len(self.second_half):
            self.second_half.appendleft(self.first_half.pop())
        

    def pushMiddle(self, val: int) -> None:
        if len(self.first_half) < len(self.second_half):
            self.first_half.append(val)
        else:
            self.second_half.appendleft(val)

    def pushBack(self, val: int) -> None:
        self.second_half.append(val)
        if len(self.second_half) >= len(self.first_half) + 2:
            self.first_half.append(self.second_half.popleft())


    def popFront(self) -> int:
        if len(self.first_half) + len(self.second_half) == 0:
            return -1
        elif len(self.first_half) == 0:
            return self.second_half.popleft()
        
        res = self.first_half.popleft()
        if len(self.first_half) + 2 <= len(self.second_half):
            self.first_half.append(self.second_half.popleft())
        return res

    def popMiddle(self) -> int:
        if len(self.first_half) + len(self.second_half) == 0:
            return -1
        
        if len(self.first_half) == len(self.second_half):
            return self.first_half.pop()
        else:
            return self.second_half.popleft()

    def popBack(self) -> int:
        if len(self.first_half) + len(self.second_half) == 0:
            return -1
        
        res = self.second_half.pop()
        if len(self.second_half) < len(self.first_half):
            self.second_half.appendleft(self.first_half.pop())
        return res

    def print(self):
        print([x for x in self.first_half] + [x for x in self.second_half])

q = FrontMiddleBackQueue()
q.pushFront(1)
q.print()

q.pushBack(2)
q.print()

q.pushMiddle(3)
q.print()

q.pushMiddle(4)
q.print()

q.popFront()
q.print()

q.popMiddle()
q.print()

q.popMiddle()
q.print()

q.popBack()
q.print()