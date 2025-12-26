# Description: https://leetcode.com/problems/contains-duplicate/description/

"""
    Approach: Hash Set

    Use a set to track numbers seen during iteration.
    For each number, check if it already exists in the set.
    If found, return True immediately as a duplicate exists.
    Otherwise, add the number to the set and continue.
    If iteration completes without finding duplicates, return False.
    Python set provides O(1) average time for add and membership test.

    Time complexity: O(n) - Single pass through the array.
    Space complexity: O(n) - Set stores at most n elements.
"""

from typing import List

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