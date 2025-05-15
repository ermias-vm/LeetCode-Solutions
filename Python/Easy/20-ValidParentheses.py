from typing import Dict

# Description: https://leetcode.com/problems/valid-parentheses/

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
