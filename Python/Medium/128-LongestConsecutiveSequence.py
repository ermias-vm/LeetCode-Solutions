from typing import List


# Description:  https://leetcode.com/problems/longest-consecutive-sequence/description/

class Solution:
    def longestConsecutive(self, nums: List[int]) -> int:
        numSet = set(nums)
        longestStreak = 0

        for n in numSet:
            if (n - 1) not in numSet:
                currentStreak = 1
                currentNum = n
                while (currentNum + 1) in numSet:
                    currentNum += 1
                    currentStreak += 1
                longestStreak = max(currentStreak, longestStreak)
        return longestStreak


if __name__ == '__main__':
    solution = Solution()

    nums1 = [100, 4, 200, 1, 3, 2]
    print(f"Input: nums = {nums1}")
    print(f"Output: {solution.longestConsecutive(nums1)}\n")

    nums2 = [0,3,7,2,5,8,4,6,0,1]
    print(f"Input: nums = j{nums2}")
    print(f"Output: {solution.longestConsecutive(nums2)}\n")

    nums3 = [1,0,1,2]
    print(f"Input: nums = j{nums3}")
    print(f"Output: {solution.longestConsecutive(nums3)}\n")


    


    
