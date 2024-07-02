#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;



class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> seen; // Create an empty unordered set to keep track of seen numbers.
        for (int num : nums) { // Iterate through each number in the input vector.
            if (seen.find(num) != seen.end()) return true; // If the current number is already in the set, return true (duplicate found).
            seen.insert(num); // If not, insert the current number into the set.
        }
        return false; // If no duplicates are found after checking all numbers, return false.
    }
};

/*
    Solution:

    Time complexity: O(n) - where n is the number of elements in the array. We traverse the list once.

    Space complexity: O(n) - in the worst case, all elements are distinct, and we store each one in the hash set.

 Code: 
 
    class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> seen;
        for (int num : nums) {
            if (seen.find(num) != seen.end()) return true;
            seen.insert(num);
        }
        return false;
    }
};
    
*/


//Test
int main() {
    Solution solution;
    vector<int> nums1 = {1,2,3,1};
    cout << "Test 1 (Expected: 1): " << solution.containsDuplicate(nums1) << endl;

    vector<int> nums2 = {1,2,3,4};
    cout << "Test 2 (Expected: 0): " << solution.containsDuplicate(nums2) << endl;

    vector<int> nums3 = {1,1,1,3,3,4,3,2,4,2};
    cout << "Test 3 (Expected: 1): " << solution.containsDuplicate(nums3) << endl;

    return 0;
}
