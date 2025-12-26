# Description: https://leetcode.com/problems/two-sum/description/

"""
    Approach: Hash Map

    Use a dictionary to store each number and its index as we iterate.
    For each element, calculate its complement (target - current number).
    Check if the complement already exists in the dictionary.
    If found, return the complement's index and current index.
    Otherwise, store the current number and index in the dictionary.
    This achieves single-pass lookup with O(1) average time per operation.

    Time complexity: O(n) - Single pass through the array.
    Space complexity: O(n) - Dictionary stores at most n elements.
"""

from typing import List, Dict

# Solution
class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        num_map: Dict[int, int] = {}
        for i, num in enumerate(nums):
            complement = target - num
            if complement in num_map:
                return [num_map[complement], i]
            num_map[num] = i
        return []

# Test
if __name__ == '__main__':
    solution = Solution()
    nums = [2, 7, 11, 15]
    target = 9
    result = solution.twoSum(nums, target)
    print(f"Input: nums = {nums}, target = {target}")
    print(f"Output: {result}")
