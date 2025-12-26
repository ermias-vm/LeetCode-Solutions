// Description: https://leetcode.com/problems/top-k-frequent-elements/description/

/*
    Approach: Bucket Sort

    Count frequencies of each element using a HashMap.
    Create buckets where index represents frequency (max frequency = n).
    Place each unique element into its corresponding frequency bucket.
    Iterate from highest frequency bucket to collect top k elements.
    Stop when k elements have been collected.
    This avoids sorting and achieves linear time complexity.

    Time complexity: O(n) - Linear frequency counting and bucket collection.
    Space complexity: O(n) - HashMap and buckets storage.
*/

import java.util.*;
class Solution {
    public int[] topKFrequent(int[] nums, int k) {
        Map<Integer, Integer> freqMap = new HashMap<>();
        for (int num : nums) {
            freqMap.put(num, freqMap.getOrDefault(num, 0) + 1);
        }
        
        List<Integer>[] buckets = new List[nums.length + 1];
        for (Map.Entry<Integer, Integer> entry : freqMap.entrySet()) {
            int freq = entry.getValue();
            int num = entry.getKey();
            if (buckets[freq] == null) {
                buckets[freq] = new ArrayList<>();
            }
            buckets[freq].add(num);
        }
        
        List<Integer> result = new ArrayList<>();
        for (int i = buckets.length - 1; i >= 0; i--) {
            if (buckets[i] != null) {
                for (int num : buckets[i]) {
                    result.add(num);
                    if (result.size() == k) {
                        return result.stream().mapToInt(Integer::intValue).toArray();
                    }
                }
            }
        }
        
        return result.stream().mapToInt(Integer::intValue).toArray();
    }
}

// Test
class Test {
    public static void main(String[] args) {
        Solution solution = new Solution();
        
        int[] nums1 = {1, 1, 1, 2, 2, 3};
        int k1 = 2;
        System.out.println("Input: nums = " + Arrays.toString(nums1) + ", k = " + k1);
        System.out.println("Output: " + Arrays.toString(solution.topKFrequent(nums1, k1)));
        System.out.println();
        
        int[] nums2 = {1};
        int k2 = 1;
        System.out.println("Input: nums = " + Arrays.toString(nums2) + ", k = " + k2);
        System.out.println("Output: " + Arrays.toString(solution.topKFrequent(nums2, k2)));
        System.out.println();
        
        int[] nums3 = {4, 1, -1, 2, -1, 2, 3};
        int k3 = 2;
        System.out.println("Input: nums = " + Arrays.toString(nums3) + ", k = " + k3);
        System.out.println("Output: " + Arrays.toString(solution.topKFrequent(nums3, k3)));
    }
}
