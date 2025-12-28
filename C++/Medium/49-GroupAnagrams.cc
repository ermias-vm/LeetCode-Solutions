// Description: https://leetcode.com/problems/group-anagrams/description/

/*
    Approach: Sorted String as Key

    Use a hash map where the key is the sorted version of each string.
    Sorting a string's characters creates a canonical form for all its anagrams.
    All anagrams will have the same sorted form and group together.
    Iterate through input strings, sort each one, and add to corresponding group.
    Finally, collect all groups from the hash map values.
    This leverages sorting for anagram identification.

    Time complexity: O(n * k log k) - n strings, each of max length k, sorted.
    Space complexity: O(n * k) - Storing all strings in hash map.
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

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
        for (auto& group : anagramGroups) { result.push_back(group.second); }
        return result;
    }
};

// Test

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
