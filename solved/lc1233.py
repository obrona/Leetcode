
# sort in increasing file name length.
# then use a trie to check if the prefix exists.

class Trie:
    def __init__(self):
        self.end: bool = False
        self.nexts: dict[str, Trie] = {}

    def insert(self, i: int, path: list[str]):
        if i == len(path):
            self.end = True
            return

        curr = path[i]
        if curr not in self.nexts:
            self.nexts[curr] = Trie()

        self.nexts[curr].insert(i + 1, path)

    def is_subchild(self, i: int, path: list[str]):
        if self.end:
            return True

        if i == len(path):
            return False

        curr = self.nexts.get(path[i])
        if curr is None:
            return False

        return curr.is_subchild(i + 1, path)

class Solution:
    def removeSubfolders(self, folder: list[str]) -> list[str]:
        folder.sort(key=lambda s: len(s))
        root = Trie()

        res = []
        for f in folder:
            path = list(s for s in f.split('/') if len(s) > 0)
            is_subchild = root.is_subchild(0, path)
            if not is_subchild:
                root.insert(0, path)
                res.append(f)

        return res

sol = Solution()
folder = ["/a","/a/b","/c/d","/c/d/e","/c/f"]

ans = sol.removeSubfolders(folder)
print(ans)