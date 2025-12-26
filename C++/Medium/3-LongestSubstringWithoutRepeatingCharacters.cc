// Description: https://leetcode.com/problems/longest-substring-without-repeating-characters/description/

/*
    Approach: Sliding Window with Vector

    Use a vector of size 128 to track the last seen index of each ASCII character.
    Maintain a sliding window with start pointer and end pointer (loop variable).
    When a duplicate is found (last index >= start), move start past that index.
    Update the character's last seen index at each step.
    Track the maximum window length (end - start + 1) throughout iteration.
    The fixed-size array provides O(1) character index lookups.

    Time complexity: O(n) - Single pass through the string.
    Space complexity: O(1) - Fixed size array of 128 elements.
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n = s.length();
        int maxLength = 0;
        vector<int> charIndex(128, -1);
        int start = 0;
        for (int end = 0; end < n; end++) {
            if (charIndex[s[end]] >= start) start = charIndex[s[end]] + 1;
            charIndex[s[end]] = end;
            maxLength = max(maxLength, end - start + 1);
        }
        return maxLength;
    }
};

// Test
int main() {
    Solution solution;
    cout << "Example 1: " << solution.lengthOfLongestSubstring("abcabcbb") << endl; // Output: 3
    cout << "Example 2: " << solution.lengthOfLongestSubstring("bbbbb") << endl; // Output: 1
    cout << "Example 3: " << solution.lengthOfLongestSubstring("pwwkew") << endl; // Output: 3
    return 0;
}