import java.util.Arrays;

// Description: https://leetcode.com/problems/product-of-array-except-self/description/

// Solution
class Solution {
    public int[] productExceptSelf(int[] nums) {
        int n = nums.length;
        int[] result = new int[n];
        
        // Calculate left products
        int leftProduct = 1;
        for (int i = 0; i < n; i++) {
            result[i] = leftProduct;
            leftProduct *= nums[i];
        }
        
        // Calculate right products and final result
        int rightProduct = 1;
        for (int i = n - 1; i >= 0; i--) {
            result[i] *= rightProduct;
            rightProduct *= nums[i];
        }
        
        return result;
    }
}

// Test
class Test {
    public static void main(String[] args) {
        Solution solution = new Solution();
        
        int[] nums1 = {1, 2, 3, 4};
        System.out.println("Input: nums = " + Arrays.toString(nums1));
        System.out.println("Output: " + Arrays.toString(solution.productExceptSelf(nums1)));
        System.out.println();
        
        int[] nums2 = {-1, 1, 0, -3, 3};
        System.out.println("Input: nums = " + Arrays.toString(nums2));
        System.out.println("Output: " + Arrays.toString(solution.productExceptSelf(nums2)));
    }
}