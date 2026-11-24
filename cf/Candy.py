from typing import List


class Solution:
    def candy(self, a: List[int]) -> int:
        n = len(a)
        L = [1] * n
        for i in range(1, n):
            if a[i] > a[i - 1]:
                L[i] = L[i - 1] + 1
        R = [1] * n
        for i in range(n - 2, -1, -1):
            if a[i] > a[i + 1]:
                R[i] = R[i + 1] + 1
        ans = 0
        for i in range(n):
            ans += max(L[i], R[i])
        return ans
