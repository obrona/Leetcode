class Solution:
    def assignUmbrella(self, rain: list[int]) -> list[str]:
        out = []
        a, b = 0, 0
        for i in range(len(rain)):
            alice_need = i < len(rain) - 1 and rain[i] == 1 and rain[i + 1] == 1
            bob_need = rain[i] == 1
            #print(alice_need, bob_need)
            if alice_need and not bob_need:
                out.append('Alice')
                a += 1
            elif bob_need and not alice_need:
                out.append('Bob')
                b += 1
            elif alice_need and bob_need:
                if a <= b:
                    out.append('Alice')
                    a += 1
                else:
                    out.append('Bob')
                    b += 1
            else:
                out.append('None')
        return out

sol = Solution()
rain = [1, 1, 0, 1, 1]
ans = sol.assignUmbrella(rain)
print(ans)