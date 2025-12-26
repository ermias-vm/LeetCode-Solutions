# Description: https://leetcode.com/problems/container-with-most-water/description/

"""
    Approach: Two Pointers

    Start with pointers at both ends for maximum width container.
    Calculate area as min(height[left], height[right]) * (right - left).
    Move the pointer with smaller height inward to potentially find larger area.
    This greedy choice ensures we don't miss the optimal solution.
    Track the maximum area found during the iteration.
    Continue until both pointers meet.

    Time complexity: O(n) - Single pass through the array.
    Space complexity: O(1) - Only pointer and area variables used.
"""

from typing import List
class Solution:
    def maxArea(self, height: List[int]) -> int:
        left = 0
        right = len(height) - 1
        max_area = 0
        
        while left < right:
            width = right - left
            current_height = min(height[left], height[right])
            current_area = width * current_height
            max_area = max(max_area, current_area)
            
            if height[left] < height[right]:
                left += 1
            else:
                right -= 1
        
        return max_area

# Test
if __name__ == '__main__':
    solution = Solution()
    
    height1 = [1, 8, 6, 2, 5, 4, 8, 3, 7]
    print(f"Input: height = {height1}")
    print(f"Output: {solution.maxArea(height1)}")
    print()
    
    height2 = [1, 1]
    print(f"Input: height = {height2}")
    print(f"Output: {solution.maxArea(height2)}")
