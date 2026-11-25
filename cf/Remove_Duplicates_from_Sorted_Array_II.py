from typing import List


class Solution:
    def removeDuplicates(self, nums: List[int]) -> int:
        n = len(nums)
        k = 0
        for i in range(0, n):
            x = nums[i]

            while k >= 2 and nums[k - 1] == x and nums[k - 2] == x:
                k -= 1

            nums[k] = x
            k += 1
        return k
