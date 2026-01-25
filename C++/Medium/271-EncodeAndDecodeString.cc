// Description: https://leetcode.com/problems/encode-and-decode-strings/description/

/*
    Approach: Length Prefix Encoding

    Encode: Prefix each string with its length followed by '#' delimiter.
    Also prefix the entire message with the list size and '#'.
    This handles any characters within strings including special characters.
    Decode: First extract list size, then iteratively extract each string.
    For each string, read the length before '#', then extract that many characters.
    This encoding is unambiguous and handles empty strings correctly.

    Time complexity: O(n) - Where n is total characters across all strings.
    Space complexity: O(n) - For the encoded/decoded strings.
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    string encode(vector<string>& strs) {
        string encodedString = to_string(strs.size()) + "#";
        for (const string& str : strs) encodedString += to_string(str.size()) + '#' + str;
        return encodedString;
    }

    vector<string> decode(string s) {
        size_t currentPos = 0;
        size_t hashPos = s.find('#', currentPos);
        unsigned int listSize = stoi(s.substr(currentPos, hashPos - currentPos));
        currentPos = hashPos + 1;

        vector<string> decodedStrings(listSize);

        for (unsigned i = 0; i < listSize; ++i) {
            hashPos = s.find('#', currentPos);
            int wordSize = stoi(s.substr(currentPos, hashPos - currentPos));
            currentPos = hashPos + 1;
            decodedStrings[i] = s.substr(currentPos, wordSize);
            currentPos += wordSize;
        }
        return decodedStrings;
    }
};

// Test
void printDecoded(const vector<string>& decoded) {
    cout << "[";
    for (size_t i = 0; i < decoded.size(); i++) {
        cout << "\"" << decoded[i] << "\"";
        if (i < decoded.size() - 1) cout << ", ";
    }
    cout << "]";
}

int main() {
    Solution solution;

    // Example 1
    vector<string> strs1 = {"hello", "world"};
    cout << "Input: [\"hello\", \"world\"]" << endl;
    string encoded1 = solution.encode(strs1);
    vector<string> decoded1 = solution.decode(encoded1);
    cout << "Output: ";
    printDecoded(decoded1);
    cout << endl << endl;

    // Example 2
    vector<string> strs2 = {"", "a", "abc", "defg"};
    cout << "Input: [\"\", \"a\", \"abc\", \"defg\"]" << endl;
    string encoded2 = solution.encode(strs2);
    vector<string> decoded2 = solution.decode(encoded2);
    cout << "Output: ";
    printDecoded(decoded2);
    cout << endl << endl;

    return 0;
}
