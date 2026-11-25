/* 3934. Smallest Unique Subarray

You are given an integer array nums.

Find the minimum length of a subarray that is not identical to any other subarray in nums.

Return an integer denoting the minimum possible length of such a subarray.

Two subarrays are considered identical if they have the same length and the same elements in corresponding positions.

 

Example 1:

Input: nums = [3,3,3]

Output: 3

Explanation:

Subarrays of length 1: [3] → appears 3 times
Subarrays of length 2: [3, 3] → appears 2 times
Subarrays of length 3: [3, 3, 3] → appears once
The subarray [3, 3, 3] is unique, so the smallest unique subarray length is 3.

Example 2:

Input: nums = [2,1,2,3,3]

Output: 1

Explanation:

Subarrays of length 1:

[2] → appears 2 times
[1] → appears once
[3] → appears 2 times
The subarray [1] is unique, so the smallest unique subarray length is 1.
Example 3:

Input: nums = [1,1,2,2,1]

Output: 2

Explanation:

Subarrays of length 1:

[1] → appears 3 times
[2] → appears 2 times
Subarrays of length 2:

[1, 1] → appears once
[1, 2] → appears once
[2, 2] → appears once
[2, 1] → appears once
There is at least one subarray of length 2 that is unique, so the smallest unique subarray length is 2.
 

Constraints:

1 <= nums.length <= 105
1 <= nums[i] <= 105  */


class Solution {
public:
    int minimumLength(vector<int>& nums) {
        int n = nums.size();

        const long long BASE = 31;
        const long long MOD = 1000000007;

        vector<long long> power(n + 1, 1);
        for (int i = 1; i <= n; i++) {
            power[i] = (power[i - 1] * BASE) % MOD;
        }

        vector<long long> prefix(n + 1, 0);

        for (int i = 0; i < n; i++) {
            prefix[i + 1] =
                (prefix[i] * BASE + nums[i]) % MOD;
        }

        auto check = [&](int len) {
            unordered_map<long long, int> freq;

            for (int i = 0; i + len <= n; i++) {
                long long hash =
                    (prefix[i + len] -
                     prefix[i] * power[len] % MOD + MOD) % MOD;

                freq[hash]++;
            }

            for (auto &it : freq) {
                if (it.second == 1)
                    return true;
            }

            return false;
        };

        int low = 1, high = n;
        int ans = n;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (check(mid)) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        return ans;
    }
};
