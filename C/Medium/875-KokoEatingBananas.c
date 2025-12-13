#include <stdio.h>
#include <stdbool.h>

// Description: https://leetcode.com/problems/koko-eating-bananas/description/

/*
    Approach: Binary Search on answer
    Binary search on eating speed k between 1 and max(piles).
    For each k, calculate total hours: sum of ceil(pile/k) for each pile.
    Find the minimum k where total hours <= h.
    
    Time complexity: O(n * log(max(piles))) - Binary search with O(n) verification.
    Space complexity: O(1) - We use a constant amount of extra space.
*/

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
    // Test case 1
    int piles1[] = {3, 6, 7, 11};
    int h1 = 8;
    printf("Test case 1: %d\n", minEatingSpeed(piles1, 4, h1)); // Output: 4
    
    // Test case 2
    int piles2[] = {30, 11, 23, 4, 20};
    int h2 = 5;
    printf("Test case 2: %d\n", minEatingSpeed(piles2, 5, h2)); // Output: 30
    
    // Test case 3
    int piles3[] = {30, 11, 23, 4, 20};
    int h3 = 6;
    printf("Test case 3: %d\n", minEatingSpeed(piles3, 5, h3)); // Output: 23

    return 0;
}
