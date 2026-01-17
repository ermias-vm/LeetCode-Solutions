// Description: https://leetcode.com/problems/valid-anagram/description/

/*
    Approach: Character Count

    First check if strings have equal length; if not, they can't be anagrams.
    Use two vectors of size 26 to count character frequencies.
    Iterate through both strings simultaneously, incrementing respective counts.
    Compare the frequency vectors at the end.
    If identical, strings are anagrams; otherwise, they are not.
    This approach works for lowercase English letters only.

    Time complexity: O(n) - Single pass through both strings.
    Space complexity: O(1) - Fixed size arrays of 26 elements.
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    bool isAnagram(string s, string t) {
        if (s.size() != t.size()) return false;

        vector<int> countS(26, 0);
        vector<int> countT(26, 0);

        for (int i = 0; i < s.size(); ++i) {
            countS[s[i] - 'a']++;
            countT[t[i] - 'a']++;
        }

        return countS == countT;
    }
};

// Test
int main() {
    Solution solution;

    // Example 1: s = "anagram", t = "nagaram"
    cout << "Output: " << (solution.isAnagram("anagram", "nagaram") ? "true" : "false") << endl;

    // Example 2: s = "rat", t = "car"
    cout << "Output: " << (solution.isAnagram("rat", "car") ? "true" : "false") << endl;

    return 0;
}
