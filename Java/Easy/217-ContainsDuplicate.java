import java.util.HashSet;
import java.util.Set;
import java.util.Arrays;

// Description: https://leetcode.com/problems/contains-duplicate/description/

// Solution
class Solution {
    public boolean containsDuplicate(int[] nums) {
        Set<Integer> seen = new HashSet<>();
        for (int num : nums) {
            if (seen.contains(num)) return true;
            seen.add(num);
        }
        return false;
    }
}

// Test
class Test {
    public static void main(String[] args) {
        Solution solution = new Solution();
        
        int[] nums1 = {1, 2, 3, 1};
        System.out.println("Input: nums = " + Arrays.toString(nums1));
        System.out.println("Output: " + solution.containsDuplicate(nums1));
        System.out.println();
        
        int[] nums2 = {1, 2, 3, 4};
        System.out.println("Input: nums = " + Arrays.toString(nums2));
        System.out.println("Output: " + solution.containsDuplicate(nums2));
        System.out.println();
        
        int[] nums3 = {1, 1, 1, 3, 3, 4, 3, 2, 4, 2};
        System.out.println("Input: nums = " + Arrays.toString(nums3));
        System.out.println("Output: " + solution.containsDuplicate(nums3));
    }
}