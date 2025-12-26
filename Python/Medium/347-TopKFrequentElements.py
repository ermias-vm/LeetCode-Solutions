# Description: https://leetcode.com/problems/top-k-frequent-elements/description/

"""
    Approach: Bucket Sort

    Count frequencies of each element using a dictionary (defaultdict).
    Create buckets where index represents frequency (max frequency = n).
    Place each unique element into its corresponding frequency bucket.
    Iterate from highest frequency bucket to collect top k elements.
    Stop when k elements have been collected.
    This avoids sorting and achieves linear time complexity.

    Time complexity: O(n) - Linear frequency counting and bucket collection.
    Space complexity: O(n) - Dictionary and buckets storage.
"""

from typing import List
from collections import defaultdict
class Solution:
    def topKFrequent(self, nums: List[int], k: int) -> List[int]:
        freq_map = defaultdict(int)
        for num in nums:
            freq_map[num] += 1
        
        buckets = [[] for _ in range(len(nums) + 1)]
        for num, freq in freq_map.items():
            buckets[freq].append(num)
        
        result = []
        for i in range(len(buckets) - 1, -1, -1):
            for num in buckets[i]:
                result.append(num)
                if len(result) == k:
                    return result
        
        return result

# Test
if __name__ == '__main__':
    solution = Solution()
    
    nums1 = [1, 1, 1, 2, 2, 3]
    k1 = 2
    print(f"Input: nums = {nums1}, k = {k1}")
    print(f"Output: {solution.topKFrequent(nums1, k1)}")
    print()
    
    nums2 = [1]
    k2 = 1
    print(f"Input: nums = {nums2}, k = {k2}")
    print(f"Output: {solution.topKFrequent(nums2, k2)}")
    print()
    
    nums3 = [4, 1, -1, 2, -1, 2, 3]
    k3 = 2
    print(f"Input: nums = {nums3}, k = {k3}")
    print(f"Output: {solution.topKFrequent(nums3, k3)}")
