# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def zigzagLevelOrder(self, root: TreeNode | None) -> list[list[int]]:
        if root is None:
            return []
        
        out = []
        q: list[TreeNode] = []
        q.append(root)
        lvl = 0

        while len(q) > 0:
            c = q.copy()
            c = [node.val for node in c]
            if lvl % 2 == 1:
                c.reverse()
            out.append(c)

            new_lst = []
            for node in q:
                if node.left is not None:
                    new_lst.append(node.left)
                if node.right is not None:
                    new_lst.append(node.right)
            q = new_lst

            lvl += 1

        return out







        