# Description: https://leetcode.com/problems/valid-palindrome/description/

"""
    Approach: Two Pointers

    Use two pointers starting from both ends of the string.
    Skip non-alphanumeric characters using isalnum() method.
    Compare characters in lowercase using lower() method.
    If any mismatch is found, return False immediately.
    Move pointers toward center until they meet.
    Return True if all comparisons passed.

    Time complexity: O(n) - Single pass through the string.
    Space complexity: O(1) - Only two pointer variables used.
"""

# Solution
class Solution:
    def isPalindrome(self, s: str) -> bool:
        left, right = 0, len(s) - 1
        while left < right:
            while left < right and not s[left].isalnum():
                left += 1
            while left < right and not s[right].isalnum():
                right -= 1

            if s[left].lower() != s[right].lower():
                return False
    
            left += 1
            right -= 1
        return True

# Test
if __name__ == "__main__":
    solution = Solution()
    s1 = "A man, a plan, a canal: Panama"
    s2 = "race a car"
    s3 = " "
    
    print(f"Input: {s1}")
    print(f"Output: {solution.isPalindrome(s1)}")  # True
    
    print(f"Input: {s2}")
    print(f"Output: {solution.isPalindrome(s2)}")  # False
    
    print(f"Input: {s3}")
    print(f"Output: {solution.isPalindrome(s3)}")  # True
