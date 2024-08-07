#include <iostream>
#include <vector>
#include <string>

using namespace std;


// Description:  https://leetcode.com/problems/encode-and-decode-strings/description/


//  Approach 1  

/* 
    Time complexity: 
        - Encoding: O(N), where N is the total length of all strings in the input vector.
        - Decoding: O(N), where N is the length of the encoded string.

    Space complexity:
        - Encoding: O(1) additional space, not counting the space required for the output string.
        - Decoding: O(N), where N is the length of the encoded string.

    The encoding function converts each string into a format that includes 
    the length of the string followed by the string itself. The decoding function reverses this process 
    by reading the lengths and extracting the corresponding substrings.)
*/


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
        unsigned int  listSize = stoi(s.substr(currentPos, hashPos - currentPos));
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


//Test
int main() {
    Solution solution; 
    vector<string> strs1 = {"hello", "world"};
    vector<string> strs2 = {"", "a", "abc", "defg"};

    string encoded1 = solution.encode(strs1);
    string encoded2 = solution.encode(strs2);

    vector<string> decoded1 = solution.decode(encoded1);
    vector<string> decoded2 = solution.decode(encoded2);

    // Print results
    cout << "Encoded 1: " << encoded1 << endl;
    cout << "Decoded 1: ";
    for (const auto& str : decoded1) {
        cout << "\"" << str << "\" ";
    }
    cout << endl;

    cout << "Encoded 2: " << encoded2 << endl;
    cout << "Decoded 2: ";
    for (const auto& str : decoded2) {
        cout << "\"" << str << "\" ";
    }
    cout << endl;

    return 0; 
}