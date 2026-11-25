from typing import List


class Solution:
    def removeDuplicates(self, nums: List[int]) -> int:
        n = len(nums)
        k = 0
        for i in range(0, n):
            x = nums[i]

            nums[k] = x
            k += 1

            while k >= 3 and nums[k - 1] == nums[k - 3]:
                k -= 1
        return k
