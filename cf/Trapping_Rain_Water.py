from typing import List


class Solution:
    def trap(self, height: List[int]) -> int:
        h = height
        n = len(h)

        dp1 = [0] * n
        dp1[0] = h[0]
        for i in range(1, n):
            dp1[i] = max(h[i], dp1[i - 1])

        dp2 = [0] * n
        dp2[n - 1] = h[n - 1]
        for i in range(n - 2, -1, -1):
            dp2[i] = max(h[i], dp2[i + 1])

        ans = 0
        for i in range(1, n - 1):
            water = min(dp1[i - 1], dp2[i + 1]) - h[i]
            if water < 0:
                water = 0
            ans += water
        return ans
