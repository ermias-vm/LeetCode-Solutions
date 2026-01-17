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

#include <stdio.h>
#include <stdbool.h>

bool canFinish(int* piles, int pilesSize, int k, int h) {
    long long hours = 0;
    for (int i = 0; i < pilesSize; i++) {
        hours += (piles[i] + k - 1) / k;  // ceil(pile / k)
    }
    return hours <= h;
}

int minEatingSpeed(int* piles, int pilesSize, int h) {
    int maxPile = 0;
    for (int i = 0; i < pilesSize; i++) {
        if (piles[i] > maxPile) maxPile = piles[i];
    }

    int left = 1;
    int right = maxPile;

    while (left < right) {
        int mid = left + (right - left) / 2;

        if (canFinish(piles, pilesSize, mid, h)) right = mid;
        else left = mid + 1;
    }

    return left;
}

// Test
int main() {
    // Example 1: piles = [3,6,7,11], h = 8
    int piles1[] = {3, 6, 7, 11};
    printf("Output: %d\n", minEatingSpeed(piles1, 4, 8));

    // Example 2: piles = [30,11,23,4,20], h = 5
    int piles2[] = {30, 11, 23, 4, 20};
    printf("Output: %d\n", minEatingSpeed(piles2, 5, 5));

    // Example 3: piles = [30,11,23,4,20], h = 6
    int piles3[] = {30, 11, 23, 4, 20};
    printf("Output: %d\n", minEatingSpeed(piles3, 5, 6));

    return 0;
}
