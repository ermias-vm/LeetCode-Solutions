# Description: https://leetcode.com/problems/valid-parentheses/description/

"""
    Approach: Stack with Dictionary

    Use a list as a stack to track opening brackets during iteration.
    Store bracket pairs in a dictionary for O(1) matching lookups.
    For each opening bracket, append it to the stack.
    For each closing bracket, check if stack is non-empty and top matches.
    If mismatch or stack empty on closing bracket, return False.
    After processing, stack should be empty for valid parentheses.

    Time complexity: O(n) - Single pass through the string.
    Space complexity: O(n) - Stack stores at most n/2 opening brackets.
"""

from typing import Dict

# Solution
class Solution:
    def isValid(self, s: str) -> bool:
        openedBrackets = []
        bracketMap = {
            ')': '(',
            ']': '[',
            '}': '{'
        }
        
        for c in s:
            if c in bracketMap:  # closed bracket case
                if not openedBrackets or openedBrackets[-1] != bracketMap[c]:
                    return False
                openedBrackets.pop()
            else:
                openedBrackets.append(c)
        
        return len(openedBrackets) == 0

# Test
if __name__ == "__main__":
    solution = Solution()
    test1 = "()"
    test2 = "()[]{}"
    test3 = "(]"
    
    print(f"Input: {test1}")
    print(f"Output: {solution.isValid(test1)}")  # Output: True
    
    print(f"Input: {test2}")
    print(f"Output: {solution.isValid(test2)}")  # Output: True
    
    print(f"Input: {test3}")
    print(f"Output: {solution.isValid(test3)}")  # Output: False
