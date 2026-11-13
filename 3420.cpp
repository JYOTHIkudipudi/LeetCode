/*  3420. Count Non-Decreasing Subarrays After K Operations

You are given an array nums of n integers and an integer k.

For each subarray of nums, you can apply up to k operations on it. In each operation, you increment any element of the subarray by 1.

Note that each subarray is considered independently, meaning changes made to one subarray do not persist to another.

Return the number of subarrays that you can make non-decreasing ​​​​​after performing at most k operations.

An array is said to be non-decreasing if each element is greater than or equal to its previous element, if it exists.

 

Example 1:

Input: nums = [6,3,1,2,4,4], k = 7

Output: 17

Explanation:

Out of all 21 possible subarrays of nums, only the subarrays [6, 3, 1], [6, 3, 1, 2], [6, 3, 1, 2, 4] and [6, 3, 1, 2, 4, 4]
cannot be made non-decreasing after applying up to k = 7 operations. Thus, the number of non-decreasing subarrays is 21 - 4 = 17.

Example 2:

Input: nums = [6,3,1,3,6], k = 4

Output: 12

Explanation:

The subarray [3, 1, 3, 6] along with all subarrays of nums with three or fewer elements, 
except [6, 3, 1], can be made non-decreasing after k operations. 
There are 5 subarrays of a single element, 4 subarrays of two elements, and 2 subarrays of three elements except [6, 3, 1],
so there are 1 + 5 + 4 + 2 = 12 subarrays that can be made non-decreasing.

 

Constraints:

1 <= nums.length <= 105
1 <= nums[i] <= 109
1 <= k <= 109  */
 class Solution {
public:
    long long countNonDecreasingSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        vector<long long> pre(n + 1, 0);
        for (int i = 0; i < n; i++) pre[i + 1] = pre[i] + nums[i];

        // Each entry is (prefix-max value, how many window elements have it).
        // front = leftmost segment, back = rightmost. Values increase left to right.
        deque<pair<long long, long long>> dq;
        long long sumM = 0;   // sum of prefix maxima over the current window [l..r]
        long long ans = 0;
        int r = n - 1;

        for (int l = n - 1; l >= 0; l--) {
            // Add nums[l] on the left: it becomes the prefix max
            // for every segment whose value is <= nums[l].
            long long cnt = 1;
            while (!dq.empty() && dq.front().first <= nums[l]) {
                cnt += dq.front().second;
                sumM -= dq.front().first * dq.front().second;
                dq.pop_front();
            }
            dq.push_front({nums[l], cnt});
            sumM += (long long)nums[l] * cnt;

            // Shrink from the right while cost = sum(prefixMax) - sum(nums) exceeds k.
            while (sumM - (pre[r + 1] - pre[l]) > k) {
                sumM -= dq.back().first;
                if (--dq.back().second == 0) dq.pop_back();
                r--;
            }
            ans += r - l + 1;
        }
        return ans;
    }
};

