# Definition for a Node.
class Node:
    def __init__(self, x: int, next: 'Node' = None, random: 'Node' = None):
        self.val = int(x)
        self.next = next
        self.random = random


# just a tedious bookwork.

class Solution:
    def copyRandomList(self, head: Node | None) -> Node | None:
        if head == None:
            return None

        node_to_idx: dict[Node, int] = {}
        node_arr: list[Node] = []

        p = 0
        curr = head
        while curr != None:
            new_node = Node(curr.val)
            node_arr.append(new_node)
            node_to_idx[curr] = p

            curr = curr.next
            p += 1

        p = 0
        curr = head
        while curr != None:
            new_node = node_arr[p]
            if p < len(node_arr) - 1:
                new_node.next = node_arr[p + 1]
            if curr.random != None:
                new_node.random = node_arr[node_to_idx[curr.random]]

            curr = curr.next
            p += 1

        return node_arr[0]
            