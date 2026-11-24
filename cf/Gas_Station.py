from typing import List


class Solution:
    def canCompleteCircuit(self, g: List[int], c: List[int]) -> int:
        n = len(g)

        def test(i):
            tank = 0
            for t in range(n):
                k = (i + t) % n
                tank += g[k] - c[k]
                if tank < 0:
                    return t
            return n

        i = 0
        while i < n:
            T = test(i)
            if T == n:
                return i
            i = i + T + 1
        return -1
