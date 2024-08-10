#include <iostream>
#include <string>
#include <cctype> // Include cctype for isalnum and tolower

using namespace std;

// Description:  https://leetcode.com/problems/valid-palindrome/description/

//  Approach 1: Two Pointers

/* 
    Time complexity: O(n)
    Space complexity: O(1)

    This approach uses two pointers to traverse the string from both ends towards the center. 
    It skips non-alphanumeric characters and compares the remaining characters in a case-insensitive manner. 
    If all corresponding characters match, the string is a palindrome; otherwise, it is not.
*/

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

//-------------------------------------------------------------

//  Approach 2: Filter and Check

/* 
    Time complexity: O(n), where n is the length of the string s. 
    We traverse the string twice: once for filtering and once for checking the palindrome.

    Space complexity: O(n) for storing the filtered string.

    This approach involves two main steps:
    1. Preprocessing the string to remove non-alphanumeric characters and convert all characters to lowercase.
    2. Using two pointers to check if the preprocessed string is a palindrome.
    - We initialize two pointers, one at the beginning and one at the end of the filtered string.
    - We compare the characters at these pointers and move them towards the center.
    - If at any point the characters do not match, we return false.
    - If the pointers cross each other, it means the string is a palindrome, and we return true.
*/

class Solution2 {
public:
    bool isPalindrome(string s) {
        string filtered;
        for (char c : s) {
            if (isalnum(c)) {
                if (c >= 'A' && c <= 'Z') c = c + 32; // Convert to lowercase
                filtered += c;
            }
        }
        
        int left = 0, right = filtered.size() - 1;
        while (left < right) {
            if (filtered[left] != filtered[right]) return false;
            left++;
            right--;
        }
        return true;
    }
};

int main() {
    Solution solution;
    Solution2 solution2;
    string s1 = "A man, a plan, a canal: Panama";
    string s2 = "race a car";
    string s3 = " ";

    cout << boolalpha;
    cout << "Test case 1 (Approach 1): " << solution.isPalindrome(s1) << endl; // true
    cout << "Test case 2 (Approach 1): " << solution.isPalindrome(s2) << endl; // false
    cout << "Test case 3 (Approach 1): " << solution.isPalindrome(s3) << endl; // true

    cout << "Test case 1 (Approach 2): " << solution2.isPalindrome(s1) << endl; // true
    cout << "Test case 2 (Approach 2): " << solution2.isPalindrome(s2) << endl; // false
    cout << "Test case 3 (Approach 2): " << solution2.isPalindrome(s3) << endl; // true

    return 0;
}