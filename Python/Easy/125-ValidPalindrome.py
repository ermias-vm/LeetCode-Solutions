# Description: https://leetcode.com/problems/valid-palindrome/description/

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
