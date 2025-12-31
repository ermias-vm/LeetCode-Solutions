// Description: https://leetcode.com/problems/valid-palindrome/description/

/*
    Approach: Two Pointers

    Use two pointers starting from both ends of the string.
    Skip non-alphanumeric characters using isalnum() function.
    Compare characters in lowercase using tolower() function.
    If any mismatch is found, return false immediately.
    Move pointers toward center until they meet.
    Return true if all comparisons passed.

    Time complexity: O(n) - Single pass through the string.
    Space complexity: O(1) - Only two pointer variables used.
*/

#include <iostream>
#include <string>
#include <cctype>

using namespace std;

class Solution {
public:
    bool isPalindrome(string s) {
        int left = 0, right = s.size() - 1;
        while (left < right) {
            while (left < right && !isalnum(s[left])) left++;
            while (left < right && !isalnum(s[right])) right--;

            if (tolower(s[left]) != tolower(s[right])) return false;

            left++;
            right--;
        }
        return true;
    }
};

// Test
int main() {
    Solution solution;
    
    // Example 1: s = "A man, a plan, a canal: Panama"
    cout << "Output: " << (solution.isPalindrome("A man, a plan, a canal: Panama") ? "true" : "false") << endl;
    
    // Example 2: s = "race a car"
    cout << "Output: " << (solution.isPalindrome("race a car") ? "true" : "false") << endl;
    
    // Example 3: s = " "
    cout << "Output: " << (solution.isPalindrome(" ") ? "true" : "false") << endl;

    return 0;
}
