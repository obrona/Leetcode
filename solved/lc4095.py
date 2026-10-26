from collections import deque
from sortedcontainers import SortedList
from dataclasses import dataclass
import math
from collections.abc import Iterable, Iterator

# at index i, we want the distinct elems of nums[i:] in order of first occurrence.
# sweep from right to left and keep this order in a doubly linked list (order).
# when moving from i + 1 to i, nums[i] becomes the first distinct elem:
# remove its node (if present) and append it to the front. both are O(1).
# poss[val] stores the indexes val occurs at, in decreasing order,
# so poss[val][-k] is the kth occurrence of val at or after i.

# for the jth distinct value (0 indexed), the subarray must contain its (j + 1)th occurrence,
# so p = max over these is the earliest valid end.
# no_cross = min over the (j + 2)th occurrences: if the subarray ends at no_cross or greater,
# some value occurs too many times, so we can never make a valid subarray.

# time complexity is O(n * sqrt(n)), space is O(n).
# a staircase with j + 1 distinct elems has length (j + 1)(j + 2) / 2,
# so for each index we look at at most O(sqrt(n)) distinct elems.
# updating the distinct elem order is O(1).



class Node[T]:
    def __init__(self, val: T):
        self.val: T = val
        self.next: Node[T] | None = None
        self.prev: Node[T] | None = None

    def clip(self):
        self.next = None
        self.prev = None

class DLL[T]:
    def __init__(self):
        self.head: Node[T] | None = None
        self.tail: Node[T] | None = None
        # empty when head == tail == None

    def appendleft(self, val: T):
        self.appendleft_node(Node[T](val))

    def appendright(self, val: T):
        self.appendright_node(Node[T](val))

    def appendleft_node(self, node: Node[T]):
        node.next = self.head
                
        if self.head != None:
            self.head.prev = node
        self.head = node
        if self.tail == None:
            self.tail = node

    def appendright_node(self, node: Node[T]):
        node.prev = self.tail
        
        if self.tail != None:
            self.tail.next = node
        self.tail = node
        if self.head == None:
            self.head = node

    def remove(self, node: Node[T]):
        if node.prev != None:
            node.prev.next = node.next

        if node.next != None:
            node.next.prev = node.prev

        if self.head == node:
            self.head = node.next

        if self.tail == node:
            self.tail = node.prev

        node.clip()

    def __iter__(self):
        curr = self.head
        while curr != None:
            yield curr.val
            curr = curr.next

class Solution:
    def countStaircase(self, nums: list[int]) -> int:
        N = len(nums)
        ans = 0
        poss = dict[int, list[int]]()
        val_to_node = dict[int, Node[int]]()
        order = DLL[int]()

        for i in range(N - 1, -1, -1):
            val = nums[i]
            prev_node = val_to_node.get(val, None)

            if prev_node != None:
                order.remove(prev_node)
                order.appendleft_node(prev_node)
            else:
                prev_node = val_to_node.setdefault(val, Node(val))
                order.appendleft_node(prev_node)

            poss.setdefault(val, []).append(i)

            p = i
            no_cross = N
            for j, x in enumerate(order):
                len_needed = math.comb(j + 2, 2)
                if len_needed > N - i:
                    break

                lst = poss[x]
                if len(lst) < j + 1:
                    break

                p = max(p, lst[-j - 1])
                if len(lst) >= j + 2:
                    no_cross = min(no_cross, lst[-j - 2])
                    if p >= no_cross:
                        break

                if p - i + 1 == len_needed:
                    ans += 1

        return ans

sol = Solution()
nums = [5,8,8,4,4,4]
ans = sol.countStaircase(nums)
print(ans)

                


                


