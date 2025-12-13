import java.util.Arrays;

// Description: https://leetcode.com/problems/koko-eating-bananas/description/


class Solution {
    public int minEatingSpeed(int[] piles, int h) {
        int left = 1;
        int right = Arrays.stream(piles).max().getAsInt();
        
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (canFinish(piles, mid, h)) right = mid;
            else left = mid + 1;
        }
        
        return left;
    }
    
    private boolean canFinish(int[] piles, int k, int h) {
        long hours = 0;
        for (int pile : piles) {
            hours += (pile + k - 1) / k;  // ceil(pile / k)
        }
        return hours <= h;
    }
}

// Test
class Test {
    public static void main(String[] args) {
        Solution solution = new Solution();
        
        int[] piles1 = {3, 6, 7, 11};
        int h1 = 8;
        System.out.println("Input: piles = " + Arrays.toString(piles1) + ", h = " + h1);
        System.out.println("Output: " + solution.minEatingSpeed(piles1, h1)); // 4
        System.out.println();
        
        int[] piles2 = {30, 11, 23, 4, 20};
        int h2 = 5;
        System.out.println("Input: piles = " + Arrays.toString(piles2) + ", h = " + h2);
        System.out.println("Output: " + solution.minEatingSpeed(piles2, h2)); // 30
        System.out.println();
        
        int[] piles3 = {30, 11, 23, 4, 20};
        int h3 = 6;
        System.out.println("Input: piles = " + Arrays.toString(piles3) + ", h = " + h3);
        System.out.println("Output: " + solution.minEatingSpeed(piles3, h3)); // 23
    }
}
