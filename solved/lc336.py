import itertools

# to get O(sum of words length) need to use trie and Manacher algo.
# for now we consider word[i] to be the suffix.
# check word[i] in reverse, match in the trie.
# once we hit the end, check the next character to see if word_x[i:n] is a palindrome.
# use manacher algo for this.
# eg abccb, s[1:n] is a palindrome.
# handle the case of an empty string seperately.

# there can be only O(sum of words length) palindrome pairs.
# let x be the number of times word[i] is the longer string in the pair.
# for i in range(len(word[i])), there can be at most 1 other word of len i
# making the pair, since all words are unique.
# *2 because word[i] can be suffix or prefix.


# length of longest palindrome is out[i] * 2 + 1
def manacher_odd(s: str) -> list[int]:
    out = [0 for _ in range(len(s))]
    l, r = 0, -1
    for i in range(len(s)):
        if i > r:
            d = 1
            while d <= min(i, len(s) - i - 1) and s[i - d] == s[i + d]:
                d += 1
            d -= 1
            l, r = i - d, i + d
            out[i] = d
        
        else:
            d = min(out[l + r - i],  r - i)
            if i + d == r:
                while d <= min(i, len(s) - i - 1) and s[i - d] == s[i + d]:
                    d += 1
                d -= 1
                l, r = i - d, i + d
            out[i] = d
    return out

# if out[i] = -1, means canot have an even palindrome here.
# length of longest palindrome is (out[i] + 1) * 2
def manacher_even(s: str) -> list[int]:
    out = [-1 for _ in range(len(s))]
    l, r = 0, -1
    for i in range(len(s) - 1):
        if s[i] != s[i + 1]:
            continue

        if i + 1 > r:
            d = 1
            while d <= min(i, len(s) - i - 2) and s[i - d] == s[i + 1 + d]:
                d += 1
            d -= 1
            l, r = i - d, i + 1 + d
            out[i] = d

        else:
            j = l + r - i - 1
            d = min(out[j], r - i - 1)
            if i + 1 + d == r:
                while d <= min(i, len(s) - i - 2) and s[i - d] == s[i + 1 + d]:
                    d += 1
                d -= 1
                l, r = i - d, i + 1 + d
            out[i] = d
    return out

# returns whether s[i:n] is a palindrome (can be odd/even)
def is_suffix_palindrome(s: str) -> list[bool]:
    out = [False for _ in range(len(s))]

    for i, d in enumerate(manacher_odd(s)):
        if i + d == len(s) - 1:
            out[i - d] = True

    for i, d in enumerate(manacher_even(s)):
        if d !=-1 and i + 1 + d == len(s) - 1:
            out[i - d] = True
    
    return out

class Trie:
    def __init__(self):
        self.end_idxs: set[int] = set()
        self.suffix_palindrome_idxs: set[int] = set()
        self.nexts: dict[str, Trie] = {}

    def insert(self, s: str, suffix_palindrome: list[bool], my_idx: int, i: int = 0):
        curr_node = self
        if len(s) == 0:
            curr_node.end_idxs.add(my_idx)
            return
        
        for i in range(len(s)):
            c = s[i]
            trie = curr_node.nexts.setdefault(c, Trie())
            if suffix_palindrome[i]:
                curr_node.suffix_palindrome_idxs.add(my_idx)
            curr_node = trie

        curr_node.end_idxs.add(my_idx)

    def search_palindrome_pairs(self, s: str, suffix_palindrome: list[bool], i: int = 0) -> set[int]:
        out: set[int] = set()
        curr_node = self
        for i in range(len(s)):
            if suffix_palindrome[i]:
                out.update(curr_node.end_idxs)
            next = curr_node.nexts.get(s[i])
            if next == None:
                return out
            curr_node = next
        out.update(curr_node.suffix_palindrome_idxs)
        out.update(curr_node.end_idxs)
        return out
            
class Solution:
    def palindromePairs(self, words: list[str]) -> list[list[int]]:
        store: list[tuple[int,int]] = []

        # only need to consider case when word[i] is the suffix and 
        root = Trie()
        for idx, w in enumerate(words):
            root.insert(w, is_suffix_palindrome(w), idx)
        for idx, w in enumerate(words):
            r_w = w[::-1]
            ans = root.search_palindrome_pairs(r_w, is_suffix_palindrome(r_w))
            ans.discard(idx)
            store.extend(itertools.product(ans, [idx]))

        return store




sol = Solution()
words = ["a","abc","aba",""]
ans = sol.palindromePairs(words)
print(ans)


