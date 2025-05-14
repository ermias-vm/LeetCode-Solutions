from typing import List, Dict

# Solution
class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        num_map: Dict[int, int] = {}
        for i, num in enumerate(nums):
            complement = target - num
            if complement in num_map:
                return [num_map[complement], i]
            num_map[num] = i
        return []

# Test
if __name__ == '__main__':
    solution = Solution()
    nums = [2, 7, 11, 15]
    target = 9
    result = solution.twoSum(nums, target)
    print(f"Input: nums = {nums}, target = {target}")
    print(f"Output: {result}")
