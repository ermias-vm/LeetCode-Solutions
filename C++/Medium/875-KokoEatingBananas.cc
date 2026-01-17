// Description: https://leetcode.com/problems/koko-eating-bananas/description/

/*
    Approach: Binary Search on Answer

    Binary search on the eating speed k between 1 and max(piles).
    For each candidate speed, calculate total hours needed: sum of ceil(pile/k).
    Use the formula (pile + k - 1) / k to compute ceiling without floating point.
    If total hours <= h, the speed is feasible; try a smaller speed.
    If total hours > h, the speed is too slow; try a larger speed.
    Return the minimum feasible speed when search converges.

    Time complexity: O(n * log(max(piles))) - Binary search with O(n) verification.
    Space complexity: O(1) - Only a few variables used.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int left = 1;
        int right = *max_element(piles.begin(), piles.end());

        while (left < right) {
            int mid = left + (right - left) / 2;
            if (canFinish(piles, mid, h)) right = mid;
            else left = mid + 1;
        }

        return left;
    }

private:
    bool canFinish(vector<int>& piles, int k, int h) {
        long long hours = 0;
        for (int pile : piles) {
            hours += (pile + k - 1) / k;  // ceil(pile / k)
        }
        return hours <= h;
    }
};

// Test
int main() {
    Solution solution;

    // Example 1: piles = [3,6,7,11], h = 8
    vector<int> piles1 = {3, 6, 7, 11};
    cout << "Output: " << solution.minEatingSpeed(piles1, 8) << endl;

    // Example 2: piles = [30,11,23,4,20], h = 5
    vector<int> piles2 = {30, 11, 23, 4, 20};
    cout << "Output: " << solution.minEatingSpeed(piles2, 5) << endl;

    // Example 3: piles = [30,11,23,4,20], h = 6
    vector<int> piles3 = {30, 11, 23, 4, 20};
    cout << "Output: " << solution.minEatingSpeed(piles3, 6) << endl;

    return 0;
}
