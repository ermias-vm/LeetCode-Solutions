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
int main() {
    Solution solution;

    vector<int> example1 = {1, 2, 3};
    vector<int> example2 = {-1, 1, 0, -3, 3};

    vector<int> result1 = solution.productExceptSelf(example1);
    vector<int> result2 = solution.productExceptSelf(example2);

    cout << "Example 1: ";
    for (int num : result1) {
        cout << num << " ";
    }
    cout << endl;

    cout << "Example 2: ";
    for (int num : result2) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}

