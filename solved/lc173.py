from typing import Iterator

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


def helper(root: TreeNode) -> Iterator[int]:
    if root.left != None:
        yield from helper(root.left)
    
    yield root.val
    
    if root.right != None:
        yield from helper(root.right)


class BSTIterator:
    def __init__(self, root: TreeNode | None):
        self.gen = helper(root)
        self.curr: int | None = next(self.gen)

    def next(self) -> int:
        temp = self.curr
        self.curr = next(self.gen, None)
        return temp

    def hasNext(self) -> bool:
        return self.curr != None