from collections import Counter

class Solution:
    def countWordOccurrences(self, chunks: list[str], queries: list[str]) -> list[int]:    
        def is_joiner_hypen(s: str, idx: int) -> bool:
            if idx == 0 or idx == len(s) - 1 or s[idx] !=  '-':
                return False
            if not s[idx - 1].islower() or not s[idx + 1].islower():
                return False
            return True
        
        s = ''.join(chunks)
        p = 0
        words = []
        while p < len(s):
            start = p
            while p < len(s) and (s[p].islower() or is_joiner_hypen(s, p)):
                p += 1
            if p - start > 0:
                words.append(s[start:p])
            p += 1
        
        #print(words)

        cnter = Counter(words)
        return [cnter[w] for w in queries]
    
sol = Solution()
chunks = ["a-b a--b ","a-","b"]
queries = ["hello","world","wor"]
print(sol.countWordOccurrences(chunks, queries))

        
