#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Description: https://leetcode.com/problems/koko-eating-bananas/description/

// Approach: Binary Search on answer
// Binary search on eating speed k between 1 and max(piles).
// For each k, calculate total hours: sum of ceil(pile/k) for each pile.
// Find the minimum k where total hours <= h.

/* 
    Time complexity: O(n * log(max(piles))) - Binary search with O(n) verification.
    Space complexity: O(1) - We use a constant amount of extra space.
*/


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
    
    vector<int> piles1 = {3, 6, 7, 11};
    int h1 = 8;
    cout << "Test case 1: " << solution.minEatingSpeed(piles1, h1) << endl; // Output: 4
    
    vector<int> piles2 = {30, 11, 23, 4, 20};
    int h2 = 5;
    cout << "Test case 2: " << solution.minEatingSpeed(piles2, h2) << endl; // Output: 30
    
    vector<int> piles3 = {30, 11, 23, 4, 20};
    int h3 = 6;
    cout << "Test case 3: " << solution.minEatingSpeed(piles3, h3) << endl; // Output: 23

    return 0;
}
