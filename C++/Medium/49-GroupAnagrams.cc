#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

// Description:  https://leetcode.com/problems/group-anagrams/description/

//  Approach 1

/* 
    Time complexity: O(N * K * log K), where N is the number of strings and K is the maximum length of a string.
    Space complexity: O(N * K), where N is the number of strings and K is the maximum length of a string.

    The solution uses a hash map to group strings that are anagrams. 
    Each string is sorted, and the sorted string is used as the key in the hash map. 
    All strings that are anagrams will have the same sorted string and thus will be grouped together.)
*/

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> anagramGroups;
        for (string s : strs) {
            string sortedStr = s;
            sort(sortedStr.begin(), sortedStr.end());
            anagramGroups[sortedStr].push_back(s);
        }
        
        vector<vector<string>> result;
        for (auto& group : anagramGroups) {
            result.push_back(group.second);
        }
        return result;
    }
};

//Test

// Function to print the results
void printResults(const vector<vector<string>>& results, const string& exampleLabel) {
    cout << exampleLabel << endl;
    for (const auto& group : results) {
        for (const auto& str : group) cout << "\"" << str << "\" ";
        cout << endl;
    }
    cout << endl;
}

int main() {
    Solution solution;
    vector<string> strs1 = {"eat", "tea", "tan", "ate", "nat", "bat"};
    vector<string> strs2 = {""};
    vector<string> strs3 = {"a"};

    vector<vector<string>> result1 = solution.groupAnagrams(strs1);
    vector<vector<string>> result2 = solution.groupAnagrams(strs2);
    vector<vector<string>> result3 = solution.groupAnagrams(strs3);

    // Print results
    printResults(result1, "Example 1:");
    printResults(result2, "Example 2:");
    printResults(result3, "Example 3:");

    return 0;
}