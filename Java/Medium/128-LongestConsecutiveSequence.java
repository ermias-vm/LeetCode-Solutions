// Description: https://leetcode.com/problems/longest-consecutive-sequence/description/

/*
    Approach: Hash Set

    Store all elements in a HashSet for O(1) lookup.
    For each number, check if it's the start of a sequence (num-1 not in set).
    If it's a sequence start, count consecutive numbers by looking up num+1, num+2, etc.
    Track the longest sequence found during iteration.
    By only counting from sequence starts, each element is visited at most twice.
    This achieves linear time despite the nested loop structure.

    Time complexity: O(n) - Each element visited at most twice.
    Space complexity: O(n) - HashSet stores all elements.
*/

import java.util.HashSet;
import java.util.Set;
import java.util.Arrays;
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

class Test {
    public static void main(String[] args){
        Solution solution = new Solution();
        int[] nums1 = {100, 4, 200, 1, 3, 2};
        System.out.println("Input: nums = " + Arrays.toString(nums1) + "\n");

        int[] nums2 = {0, 3, 7, 2, 5, 8, 4, 6, 0, 1};
        System.out.println("Input: nums = " + Arrays.toString(nums2));
        System.out.println("Output: " + solution.longestConsecutive(nums2) + "\n");

        int[] nums3 = {1, 0, 1, 2};
        System.out.println("Input: nums = " + Arrays.toString(nums3));
        System.out.println("Output: " + solution.longestConsecutive(nums3));
    }

}