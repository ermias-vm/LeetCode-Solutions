#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;


// Description:  https://leetcode.com/problems/top-k-frequent-elements/description/


//  Approach 1 : Bucket sort


/* 
    Time complexity: O(n)

    Space complexity: O(n)

    We use a hash map to count the frequency of each element, which takes O(n) time.
    Then, we use a list of lists (buckets) to group elements by their frequencies, which also takes O(n) time.
    Finally, we collect the top k frequent elements from the buckets, which takes O(n) time in the worst case.
*/


class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> freqMap;
        for (int num : nums) freqMap[num]++;

        vector<vector<int>> buckets(nums.size() +1);
        for (auto& pair : freqMap) {
            buckets[pair.second].push_back(pair.first);
        }

        vector<int> result;
        for (int i = buckets.size() -1; i >= 0 ; --i) {
            for (int num : buckets[i]) {
                result.push_back(num);
                if (result.size() == k) return result;
            }
        }
    
        return result;
    }
};


//----------------------------------------------------------------------

// Approach 2 : Min-Heap

/* 
    Time complexity: O(n log k)
    Space complexity: O(n)

    We use a hash map to count the frequency of each element, which takes O(n) time.
    Then, we use a min-heap to keep track of the top k frequent elements, which takes O(n log k) time.
*/

class Solution2 {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> freqMap;
        for (int num : nums) {
            freqMap[num]++;
        }
        
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
        for (auto& pair : freqMap) {
            minHeap.push({pair.second, pair.first});
            if (minHeap.size() > k) {
                minHeap.pop();
            }
        }
        
        vector<int> result;
        while (!minHeap.empty()) {
            result.push_back(minHeap.top().second);
            minHeap.pop();
        }
        
        return result;
    }
};


int main() {
    Solution solution1;
    vector<int> nums = {1, 1, 1, 2, 2, 3};
    int k = 2;

    // Test Bucket Sort approach
    vector<int> resultBucketSort = solution1.topKFrequent(nums, k);
    cout << "Top " << k << " frequent elements using Bucket Sort: ";
    for (int num : resultBucketSort) {
        cout << num << " ";
    }
    cout << endl;

    // Test Min-Heap approach
    Solution2 solution2;
    vector<int> resultMinHeap = solution2.topKFrequent(nums, k);
    cout << "Top " << k << " frequent elements using Min-Heap: ";
    for (int num : resultMinHeap) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}