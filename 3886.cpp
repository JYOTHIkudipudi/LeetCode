/* 3886. Sum of Sortable Integers

You are given an integer array nums of length n.

An integer k is called sortable if k divides n and you can sort nums in non-decreasing order by sequentially performing the following operations:

Partition nums into consecutive subarrays of length k.
Cyclically rotate each subarray independently any number of times to the left or to the right.
Return an integer denoting the sum of all possible sortable integers k.

 

Example 1:

Input: nums = [3,1,2]

Output: 3

Explanation:​​​​​​​

For n = 3, possible divisors are 1 and 3.
For k = 1: each subarray has one element. No rotation can sort the array.
For k = 3: the single subarray [3, 1, 2] can be rotated once to produce [1, 2, 3], which is sorted.
Only k = 3 is sortable. Hence, the answer is 3.
Example 2:

Input: nums = [7,6,5]

Output: 0

Explanation:

For n = 3, possible divisors are 1 and 3.
For k = 1: each subarray has one element. No rotation can sort the array.
For k = 3: the single subarray [7, 6, 5] cannot be rotated into non-decreasing order.
No k is sortable. Hence, the answer is 0.
Example 3:

Input: nums = [5,8]

Output: 3

Explanation:​​​​​​​

For n = 2, possible divisors are 1 and 2.
Since [5, 8] is already sorted, every divisor is sortable. Hence, the answer is 1 + 2 = 3.
 

Constraints:

1 <= n == nums.length <= 105
1 <= nums[i] <= 105
 
*/


class Solution {
public:
    int sortableIntegers(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;

        for (int k = 1; k <= n; k++) {
            if (n % k != 0)
                continue;

            bool valid = true;
            int prevMax = -1;

            for (int start = 0; start < n; start += k) {
                int descents = 0;
                int descentIndex = -1;

                // Count circular descents in this block
                for (int j = 0; j < k; j++) {
                    int curr = start + j;
                    int next = start + (j + 1) % k;

                    if (nums[curr] > nums[next]) {
                        descents++;
                        descentIndex = j;
                    }
                }

                // Cannot rotate this block into sorted order
                if (descents > 1) {
                    valid = false;
                    break;
                }

                int first, last;

                if (descents == 1) {
                    // Sorted rotation starts after the descent
                    first = nums[start + (descentIndex + 1) % k];
                    last = nums[start + descentIndex];
                } else {
                    // All elements in this circular block are equal
                    first = nums[start];
                    last = nums[start];
                }

                // Check the boundary between consecutive blocks
                if (prevMax > first) {
                    valid = false;
                    break;
                }

                prevMax = last;
            }

            if (valid)
                ans += k;
        }

        return ans;
    }
};


