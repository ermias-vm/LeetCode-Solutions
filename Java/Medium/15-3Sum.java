import java.util.*;

// Description: https://leetcode.com/problems/3sum/description/

// Solution
class Solution {
    public List<List<Integer>> threeSum(int[] nums) {
        Arrays.sort(nums);
        
        List<List<Integer>> result = new ArrayList<>();
        for (int i = 0; i < nums.length; i++) {
            if (i > 0 && nums[i] == nums[i - 1]) continue; // Skip duplicates
            
            int left = i + 1;
            int right = nums.length - 1;
            
            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];
                
                if (sum == 0) {
                    result.add(Arrays.asList(nums[i], nums[left], nums[right]));
                    while (left < right && nums[left] == nums[left + 1]) left++; // Skip duplicates
                    while (left < right && nums[right] == nums[right - 1]) right--; // Skip duplicates
                    left++;
                    right--;
                } else if (sum < 0) {
                    left++;
                } else {
                    right--;
                }
            }
        }
        return result;
    }
}

// Test
class Test {
    public static void main(String[] args) {
        Solution solution = new Solution();
        
        int[] nums1 = {-1, 0, 1, 2, -1, -4};
        System.out.println("Input: nums = " + Arrays.toString(nums1));
        System.out.println("Output: " + solution.threeSum(nums1));
        System.out.println();
        
        int[] nums2 = {0, 1, 1};
        System.out.println("Input: nums = " + Arrays.toString(nums2));
        System.out.println("Output: " + solution.threeSum(nums2));
        System.out.println();
        
        int[] nums3 = {0, 0, 0};
        System.out.println("Input: nums = " + Arrays.toString(nums3));
        System.out.println("Output: " + solution.threeSum(nums3));
    }
}