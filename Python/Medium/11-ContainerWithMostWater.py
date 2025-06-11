from typing import List

# Description: https://leetcode.com/problems/container-with-most-water/


"""
    Time complexity: O(n) - We traverse the array only once.
    Space complexity: O(1) - We use a constant amount of extra space.
"""
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
