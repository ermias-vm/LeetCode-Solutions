// Description: https://leetcode.com/problems/top-k-frequent-elements/description/

/*
    Approach: Bucket Sort

    Count frequencies of each element using a hash map.
    Create buckets where index represents frequency (max frequency = n).
    Place each unique element into its corresponding frequency bucket.
    Iterate from highest frequency bucket to collect top k elements.
    Stop when k elements have been collected.
    This avoids sorting and achieves linear time complexity.

    Time complexity: O(n) - Linear frequency counting and bucket collection.
    Space complexity: O(n) - Hash map and buckets storage.
*/

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> freqMap;
        for (int num : nums) freqMap[num]++;

        vector<vector<int>> buckets(nums.size() + 1);
        for (auto& pair : freqMap) { buckets[pair.second].push_back(pair.first); }

        vector<int> result;
        for (int i = buckets.size() - 1; i >= 0; --i) {
            for (int num : buckets[i]) {
                result.push_back(num);
                if (result.size() == static_cast<size_t>(k)) return result;
            }
        }

        return result;
    }
};

// Test

int main() {
    Solution solution;
    vector<int> nums = {1, 1, 1, 2, 2, 3};
    int k = 2;

    vector<int> result = solution.topKFrequent(nums, k);
    cout << "Top " << k << " frequent elements: ";
    for (int num : result) { cout << num << " "; }
    cout << endl;

    return 0;
}
