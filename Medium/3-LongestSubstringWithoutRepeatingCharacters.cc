#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;


// Description: https://leetcode.com/problems/longest-substring-without-repeating-characters/description/



/*
    Solution:

    Time complexity:    O(n)

    Space complexity:   O(n)
    
*/


// Approach 1: unordered_map
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        // This map stores characters and their latest indices in the string.
        unordered_map<char, int> charIndexMap;
        // maxLength will hold the length of the longest substring without repeating characters.
        int maxLength = 0;
        // start is the beginning index of the current window without repeating characters.
        int start = 0;
        int n = s.length();
        // Iterate through the string with 'end' marking the current character's index.
        for (int end = 0; end < n; ++end) {
            // If the current character is already in the map (i.e., it has appeared before),
            // move 'start' to the position right after where the character was last seen.
            // This ensures the window only contains unique characters.
            if (charIndexMap.find(s[end]) != charIndexMap.end()) {
                start = max(start, charIndexMap[s[end]] + 1);
            }
            // Update maxLength with the size of the current window if it's larger than the previous maximum.
            // The size of the current window is calculated as 'end - start + 1'.
            maxLength = max(maxLength, end - start + 1);
            // Update the map with the current character's latest index.
            charIndexMap[s[end]] = end;
        }
        
        // Return the maximum length found.
        return maxLength;
    }
};


// Approach 2: Vector instead of unordered_map
class Solution2 {
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


/*
    Submission   95.56%% faster than other C++ submissions (28/06/2024):

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

    


*/

//Test
int main() {
    Solution solution;
    cout << "Example 1: " << solution.lengthOfLongestSubstring("abcabcbb") << endl; // Output: 3
    cout << "Example 2: " << solution.lengthOfLongestSubstring("bbbbb") << endl; // Output: 1
    cout << "Example 3: " << solution.lengthOfLongestSubstring("pwwkew") << endl; // Output: 3
    return 0;
}