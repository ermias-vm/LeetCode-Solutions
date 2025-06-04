from typing import List

# Description: https://leetcode.com/problems/contains-duplicate/description/

# Solution
class Solution:
    def containsDuplicate(self, nums: List[int]) -> bool:
        seen = set()
        for num in nums:
            if num in seen:
                return True
            seen.add(num)
        return False

# Test
if __name__ == '__main__':
    solution = Solution()
    
    nums1 = [1, 2, 3, 1]
    print(f"Input: nums = {nums1}")
    print(f"Output: {solution.containsDuplicate(nums1)}")
    print()
    
    nums2 = [1, 2, 3, 4]
    print(f"Input: nums = {nums2}")
    print(f"Output: {solution.containsDuplicate(nums2)}")
    print()
    
    nums3 = [1, 1, 1, 3, 3, 4, 3, 2, 4, 2]
    print(f"Input: nums = {nums3}")
    print(f"Output: {solution.containsDuplicate(nums3)}")