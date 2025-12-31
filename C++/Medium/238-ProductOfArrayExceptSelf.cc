// Description: https://leetcode.com/problems/product-of-array-except-self/description/

/*
    Approach: Prefix and Suffix Products

    Use two passes to calculate products without using division.
    First pass (left to right): store cumulative left products in result array.
    Second pass (right to left): multiply each position by cumulative right product.
    After both passes, result[i] contains product of all elements except nums[i].
    Track running products with single variables instead of extra arrays.
    This achieves O(1) extra space (excluding the output array).

    Time complexity: O(n) - Two passes through the array.
    Space complexity: O(1) - Only uses the output array.
*/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> result(n, 1);

        int leftProduct = 1;
        for (int i = 0; i < n; ++i) {
            result[i] = leftProduct;
            leftProduct *= nums[i];
        }

        int rightProduct = 1;
        for (int i = n - 1; i >= 0; --i) {
            result[i] *= rightProduct;
            rightProduct *= nums[i];
        }

        return result;
    }
};

// Test
void printVector(const vector<int>& v) {
    cout << "Output: [";
    for (size_t i = 0; i < v.size(); i++) {
        cout << v[i];
        if (i < v.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

int main() {
    Solution solution;

    // Example 1: nums = [1,2,3,4]
    vector<int> example1 = {1, 2, 3, 4};
    vector<int> result1 = solution.productExceptSelf(example1);
    printVector(result1);

    // Example 2: nums = [-1,1,0,-3,3]
    vector<int> example2 = {-1, 1, 0, -3, 3};
    vector<int> result2 = solution.productExceptSelf(example2);
    printVector(result2);

    return 0;
}
