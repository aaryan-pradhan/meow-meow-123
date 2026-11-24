from typing import List


class Solution:
    def productExceptSelf(self, a: List[int]) -> List[int]:
        n = len(a)
        pre = [0] * n
        pre[0] = a[0]
        for i in range(1, n):
            pre[i] = pre[i - 1] * a[i]
        suf = [0] * n
        suf[n - 1] = a[n - 1]
        for i in range(n - 2, -1, -1):
            suf[i] = suf[i + 1] * a[i]
        ans = [0] * n
        ans[0] = suf[1]
        ans[n - 1] = pre[n - 2]
        for i in range(1, n - 1):
            ans[i] = pre[i - 1] * suf[i + 1]
        return ans
