# simple recursion

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def countDominantNodes(self, root: TreeNode | None) -> int:
        
        def helper(node: TreeNode | None) -> tuple[int,int]:
            if node == None:
                return (0, 0)
            lm, lc = helper(node.left)
            rm, rc = helper(node.right)
            m = max(node.val, lm, rm)
            return (m, lc + rc + int(node.val == m))
        
        return helper(root)[1]