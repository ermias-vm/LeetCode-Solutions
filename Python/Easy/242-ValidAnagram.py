from typing import Dict
from collections import defaultdict

# Description: https://leetcode.com/problems/valid-anagram/description/

# Approach 1: Using frequency list (for lowercase English letters only)
"""
    Time complexity:    O(n)
    Space complexity:   O(1)
    
    The strategy used to solve the problem involves counting the frequency of each character in both strings.
    Two lists of size 26 (for each letter in the alphabet) are used to store these frequencies.
    The characters in the strings are iterated over, and their corresponding counts are incremented.
    Finally, the two lists are compared; if they are identical, the strings are anagrams.
"""
class Solution:
    def isAnagram(self, s: str, t: str) -> bool:
        if len(s) != len(t):
            return False
        
        count_s = [0] * 26
        count_t = [0] * 26
        
        for i in range(len(s)):
            count_s[ord(s[i]) - ord('a')] += 1
            count_t[ord(t[i]) - ord('a')] += 1
        
        return count_s == count_t

# Approach 2: Using dictionary (for any Unicode characters)
"""
    Time complexity:    O(n)
    Space complexity:   O(k) where 'k' is the number of distinct characters across both input
    
    This code replaces the fixed-size lists with dictionary to count the frequency of each
    character in the input strings. This approach is more flexible and can handle any set of characters,
    making it suitable for Unicode characters as well.
"""
class Solution2:
    def isAnagram(self, s: str, t: str) -> bool:
        if len(s) != len(t):
            return False
        
        count_s = defaultdict(int)
        count_t = defaultdict(int)
        
        for i in range(len(s)):
            count_s[s[i]] += 1
            count_t[t[i]] += 1
        
        return count_s == count_t

# Test
if __name__ == '__main__':
    # Approach 1
    solution = Solution()
    print("=== Approach 1 (List) ===")
    print('Input: s = "anagram", t = "nagaram"')
    print(f"Output: {solution.isAnagram('anagram', 'nagaram')}")
    print()
    
    print('Input: s = "rat", t = "car"')
    print(f"Output: {solution.isAnagram('rat', 'car')}")
    print()
    
    # Approach 2
    solution2 = Solution2()
    print("=== Approach 2 (Dictionary - Unicode support) ===")
    print('Input: s = "anagram", t = "nagaram"')
    print(f"Output: {solution2.isAnagram('anagram', 'nagaram')}")
    print()
    
    print('Input: s = "rat", t = "car"')
    print(f"Output: {solution2.isAnagram('rat', 'car')}")
    print()
    
    # Unicode examples
    print('Unicode Input: s = "🍎🍏", t = "🍏🍎"')
    print(f"Output: {solution2.isAnagram('🍎🍏', '🍏🍎')}")
    print()
    
    print('Unicode Input: s = "🍏🍏🍏", t = "🍎🍎🍎"')
    print(f"Output: {solution2.isAnagram('🍏🍏🍏', '🍎🍎🍎')}")
    print()
    
    print('Unicode Input: s = "मनीमनी", t = "नीम"')
    print(f"Output: {solution2.isAnagram('मनीमनी', 'नीम')}")
    print()
    
    print('Unicode Input: s = "心心相印", t = "心相心印"')
    print(f"Output: {solution2.isAnagram('心心相印', '心相心印')}")
