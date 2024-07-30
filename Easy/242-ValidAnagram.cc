#include <iostream>
#include <vector>
#include <string>

using namespace std;


// Description:  https://leetcode.com/problems/valid-anagram/description/



// Approach 1  


 /* 
    Time complexity:    O(n)
    Space complexity:   O(1)

    The strategy used to solve the problem involves counting the frequency of each character in both strings. 
    Two vectors of size 26 (for each letter in the alphabet) are used to store these frequencies. 
    The characters in the strings are iterated over, and their corresponding counts are incremented. 
    Finally, the two vectors are compared; if they are identical, the strings are anagrams
*/

class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.size() != t.size()) return false;

        vector<int> countS(26,0);
        vector<int> countT(26,0);

        for (int i = 0; i < s.size(); ++i) {
            countS[s[i] -'a']++;
            countT[t[i] -'a']++;
        }
        
        return countS == countT;
    }
};



// Test
int main() {
    Solution solution;
    string s1 = "anagram";
    string t1 = "nagaram";
    string s2 = "rat";
    string t2 = "car";

    cout << boolalpha;
    cout << "Example 1: " << solution.isAnagram(s1, t1) << endl; // Output: true
    cout << "Example 2: " << solution.isAnagram(s2, t2) << endl; // Output: false

    return 0;
}