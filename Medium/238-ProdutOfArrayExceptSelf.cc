#include <iostream>
#include <vector>
using namespace std;


// Description:  https://leetcode.com/problems/product-of-array-except-self/description/


//  Approach 1  (without using division operation)

/* 
    Time complexity: O(N)
    Space complexity: O(1) (excluding the output array)

    This approach calculates the product of all elements except the current one without using division.
    It uses two passes over the array:
    1. In the first pass, it calculates the product of all elements to the left of each element and stores it in the result array.
    2. In the second pass, it calculates the product of all elements to the right of each element and multiplies it
     with the corresponding value in the result array.
    This way, each element in the result array contains the product of all elements except itself.
*/

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> result(n, 1);

        // Calculate left products
        int leftProduct = 1;
        for (int i = 0; i < n; ++i) {
            result[i] = leftProduct;
            leftProduct *= nums[i];
        }

        // Calculate right products and final result
        int rightProduct = 1;
        for (int i = n - 1; i >= 0; --i) {
            result[i] *= rightProduct;
            rightProduct *= nums[i];
        }

        return result;
    }
};





//  Approach 2  (using division operation)

/* 
    Time complexity: O(N)

    Space complexity:O(1)

    This approach calculates the product of all elements except the current one using division.
    It first calculates the product of all elements in the array.
    Then, for each element, it divides the total product by the current element to get the product of all other elements.
    This approach is simpler but does not meet the problem's constraint of not using division.
*/


class Solution2 {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int numsProduct = 1;
        unsigned int zeroCount = 0;
        unsigned int zeroIndex;

        for (unsigned int i = 0; i < nums.size(); i++) {
            if (nums[i] == 0) {
                ++zeroCount;
                zeroIndex = i;
            }
            else numsProduct *= nums[i];
        }

        if (zeroCount > 1) {
            vector<int> zerosVec(nums.size());
            return zerosVec;
        }

        if (zeroCount == 1) {
            vector<int> zerosVec(nums.size());
            zerosVec[zeroIndex] = numsProduct;
            return zerosVec;
        }
           
        for (unsigned int i = 0; i < nums.size(); ++i) nums[i] = numsProduct / nums[i];

        return nums;   
    }
};


//Test
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

