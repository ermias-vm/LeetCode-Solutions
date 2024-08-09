#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;


// Description:  https://leetcode.com/problems/longest-consecutive-sequence/description/


//  Approach : Using unordered_set 

/* 
    Time complexity: O(n) 
    Space complexity: O(n)

    Explanation:
    - We use an unordered_set to store the elements of the array. 
      This allows us to have O(1) average time complexity for insertions and lookups.
    - We then iterate through each element in the array. For each element, we check if it is the start 
      of a sequence by verifying that the element minus one is not in the set.
    - If it is the start of a sequence, we then count the length of the sequence by incrementing 
      the element and checking if the incremented element is in the set.
    - We keep track of the maximum length of any sequence we find.
*/


class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        if (nums.empty()) return 0;

        unordered_set<int> numSet(nums.begin(), nums.end());
        int longestStreak = 0;

        for (int num: nums) {
            if (numSet.find(num -1) == numSet.end()) {
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
int main() {
    Solution sol;
    vector<int> nums = {100, 4, 200, 1, 3, 2};
    cout << "Longest consecutive sequence length: " << sol.longestConsecutive(nums) << endl;
    return 0;
}

