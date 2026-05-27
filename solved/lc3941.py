from collections import Counter

class Solution:
    def passwordStrength(self, password: str) -> int:
        lower_case = set()
        upper_case = set()
        digits = set()

        special = set('!@#$')
        special_set = set()

        for c in password:
            if c.islower():
                lower_case.add(c)
            elif c.isupper():
                upper_case.add(c)
            elif c.isdigit():
                digits.add(c)
            elif c in special:
                special_set.add(c)

        return len(lower_case) * 1 + len(upper_case) * 2 + len(digits) * 3 + len(special_set) * 5


cnter = Counter()
cnter[1] = 10
print(cnter)

