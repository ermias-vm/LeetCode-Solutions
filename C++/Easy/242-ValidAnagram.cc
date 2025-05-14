#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

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

// Approach 2

 /* 
    Time complexity:    O(n)
    Space complexity:   O(k) : where 'k' is the number of distinct characters across both input 

    This code replaces the fixed-size vectors with unordered_map to count the frequency of each 
    character in the input strings. This approach is more flexible and can handle any set of characters, 
    making it suitable for Unicode characters as well. 

*/

class Solution2 {
public:
    bool isAnagram(string s, string t) {
        if (s.size() != t.size()) return false;

        unordered_map<char, int> countS;
        unordered_map<char, int> countT;

        for (int i = 0; i < s.size(); ++i) {
            countS[s[i]]++;
            countT[t[i]]++;
        }

        return countS == countT;
    }
};




// Test
int main() {
    //Approach 1
    Solution solution;
    cout << boolalpha;
    cout << "Example 1: " << solution.isAnagram("anagram", "nagaram") << endl; // Output: true
    cout << "Example 2: " << solution.isAnagram("rat", "car") << endl; // Output: false

    //Approach 2
    Solution2 solution_unicode;
    cout << "Unicode Example 1: " << solution_unicode.isAnagram("मनीमनी", "नीम") << endl;       // Output: false
    cout << "Unicode Example 2: " << solution_unicode.isAnagram("心心相印", "心相心印") << endl; // Output: true
    cout << "Unicode Example 3: " << solution_unicode.isAnagram("🍏🍏🍏", "🍎🍎🍎") << endl;  // Output: false
    cout << "Unicode Example 4: " << solution_unicode.isAnagram("🍎🍏", "🍏🍎") << endl;      // Output: true
    
    return 0;
}