import java.util.Arrays;

// Description: https://leetcode.com/problems/container-with-most-water/


class Solution {
    public int maxArea(int[] height) {
        int left = 0;
        int right = height.length - 1;
        int maxArea = 0;
        
        while (left < right) {
            int width = right - left;
            int currentHeight = Math.min(height[left], height[right]);
            int currentArea = width * currentHeight;
            maxArea = Math.max(maxArea, currentArea);
            
            if (height[left] < height[right]) {
                left++;
            } else {
                right--;
            }
        }
        
        return maxArea;
    }
}

// Test
class Test {
    public static void main(String[] args) {
        Solution solution = new Solution();
        
        int[] height1 = {1, 8, 6, 2, 5, 4, 8, 3, 7};
        System.out.println("Input: height = " + Arrays.toString(height1));
        System.out.println("Output: " + solution.maxArea(height1));
        System.out.println();
        
        int[] height2 = {1, 1};
        System.out.println("Input: height = " + Arrays.toString(height2));
        System.out.println("Output: " + solution.maxArea(height2));
    }
}
