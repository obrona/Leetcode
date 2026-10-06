# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def mergeNodes(self, head: ListNode | None) -> ListNode | None:
        store: ListNode | None = None
        curr = head

        while True:
            if curr.next == None:
                break
            res = 0
            ptr: ListNode = curr.next
            while ptr.val != 0:
                res += ptr.val
                ptr = ptr.next

            curr.val = res
            if store == None:
                store = curr
            else:
                store.next = curr
                store = curr

            curr = ptr
            
        store.next = None
        return head

