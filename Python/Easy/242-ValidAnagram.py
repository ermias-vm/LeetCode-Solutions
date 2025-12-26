# Description: https://leetcode.com/problems/valid-anagram/description/

"""
    Approach 1: Frequency List

    First check if strings have equal length; if not, they can't be anagrams.
    Use two lists of size 26 to count character frequencies.
    Convert character to index using ord(c) - ord('a').
    Iterate through both strings simultaneously, incrementing respective counts.
    Compare the frequency lists at the end.
    This approach works for lowercase English letters only.

    Time complexity: O(n) - Single pass through both strings.
    Space complexity: O(1) - Fixed size arrays of 26 elements.
"""

"""
    Approach 2: Dictionary (Unicode support)

    Use defaultdict(int) to count character frequencies for both strings.
    This approach handles any Unicode characters, not just lowercase letters.
    Iterate through both strings, incrementing character counts.
    Compare the frequency dictionaries at the end.
    More flexible but uses more space for diverse character sets.

    Time complexity: O(n) - Single pass through both strings.
    Space complexity: O(k) - Where k is the number of distinct characters.
"""

from typing import Dict
from collections import defaultdict
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
