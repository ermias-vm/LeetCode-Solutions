import java.util.HashSet;
import java.util.Set;
import java.util.Arrays;

// Description: https://leetcode.com/problems/longest-consecutive-sequence/

// Solution
class Solution {
    public int longestConsecutive(int[] nums) {
        Set<Integer> numSet = new HashSet<>();
        for (int num : nums) numSet.add(num);
        int longestStreak = 0;

        for (int n : numSet) {
            if (!numSet.contains(n - 1)) { // Check if num is the start of a sequence
                int currentNum = n;
                int currentStreak = 1;
                
                while (numSet.contains(currentNum + 1)) {
                    currentNum++;
                    currentStreak++;
                }
                longestStreak = Math.max(currentStreak, longestStreak);
            }
        }
        return longestStreak; 
    }
}

// Test
class Test {  // ❌ Cambiar "public class" por "class"
    public static void main(String[] args) {
        Solution solution = new Solution();

        int[] nums1 = {100, 4, 200, 1, 3, 2};
        System.out.println("Input: nums = " + Arrays.toString(nums1));
        System.out.println("Output: " + solution.longestConsecutive(nums1));
        System.out.println();

        int[] nums2 = {0, 3, 7, 2, 5, 8, 4, 6, 0, 1};
        System.out.println("Input: nums = " + Arrays.toString(nums2));
        System.out.println("Output: " + solution.longestConsecutive(nums2));
        System.out.println();

        int[] nums3 = {1, 0, 1, 2};
        System.out.println("Input: nums = " + Arrays.toString(nums3));
        System.out.println("Output: " + solution.longestConsecutive(nums3));
    }
}