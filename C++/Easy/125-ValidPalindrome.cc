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
    string s1 = "A man, a plan, a canal: Panama";
    string s2 = "race a car";
    string s3 = " ";

    cout << boolalpha;
    cout << "Test case 1: " << solution.isPalindrome(s1) << endl;
    cout << "Test case 2: " << solution.isPalindrome(s2) << endl;
    cout << "Test case 3: " << solution.isPalindrome(s3) << endl;

    return 0;
}
