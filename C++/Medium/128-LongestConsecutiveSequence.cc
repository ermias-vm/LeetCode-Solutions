// Description: https://leetcode.com/problems/longest-consecutive-sequence/description/

/*
    Approach: Hash Set

    Store all elements in an unordered_set for O(1) lookup.
    For each number, check if it's the start of a sequence (num-1 not in set).
    If it's a sequence start, count consecutive numbers by looking up num+1, num+2, etc.
    Track the longest sequence found during iteration.
    By only counting from sequence starts, each element is visited at most twice.
    This achieves linear time despite nested loops.

    Time complexity: O(n) - Each element visited at most twice.
    Space complexity: O(n) - Hash set stores all elements.
*/

#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;


class Solution {
public:
    int longestConsecutive(vector<int>& nums) {

        unordered_set<int> numSet(nums.begin(), nums.end());
        int longestStreak = 0;

        for (int num: numSet) {
            if (numSet.find(num -1) == numSet.end()) { // Check if num is the start of a sequence
                int currentNum = num;
                int currentStreak = 1;
            
                while (numSet.find(currentNum + 1) != numSet.end()) {
                    currentStreak++;
                    currentNum++;
                }
                longestStreak = max(longestStreak, currentStreak);
            }
        }
        return  longestStreak;
    }
};



// Test

void printVector(const vector<int>& nums) {
    cout << "[";
    for (int i = 0; i < nums.size(); i++) {
        cout << nums[i];
        if (i < nums.size() - 1) cout << ", ";
    }
    cout << "]";
}

int main() {
    Solution sol;
    
    vector<int> nums1 = {100, 4, 200, 1, 3, 2};
    cout << "Input: nums = ";
    printVector(nums1);
    cout << endl;
    cout << "Output: " << sol.longestConsecutive(nums1) << endl << endl;

    vector<int> nums2 = {0, 3, 7, 2, 5, 8, 4, 6, 0, 1};
    cout << "Input: nums = ";
    printVector(nums2);
    cout << endl;
    cout << "Output: " << sol.longestConsecutive(nums2) << endl << endl;

    vector<int> nums3 = {1, 0, 1, 2};
    cout << "Input: nums = ";
    printVector(nums3);
    cout << endl;
    cout << "Output: " << sol.longestConsecutive(nums3) << endl;
    
    return 0;
}


