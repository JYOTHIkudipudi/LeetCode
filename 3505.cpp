/* 3505. Minimum Operations to Make Elements Within K Subarrays Equal

You are given an integer array nums and two integers, x and k. You can perform the following operation any number of times (including zero):

Increase or decrease any element of nums by 1.
Return the minimum number of operations needed to have at least k non-overlapping subarrays of size exactly x in nums, 
where all elements within each subarray are equal.

 

Example 1:

Input: nums = [5,-2,1,3,7,3,6,4,-1], x = 3, k = 2

Output: 8

Explanation:

Use 3 operations to add 3 to nums[1] and use 2 operations to subtract 2 from nums[3]. The resulting array is [5, 1, 1, 1, 7, 3, 6, 4, -1].
Use 1 operation to add 1 to nums[5] and use 2 operations to subtract 2 from nums[6]. The resulting array is [5, 1, 1, 1, 7, 4, 4, 4, -1].
Now, all elements within each subarray [1, 1, 1] (from indices 1 to 3) and [4, 4, 4] (from indices 5 to 7) are equal. 
Since 8 total operations were used, 8 is the output.
Example 2:

Input: nums = [9,-2,-2,-2,1,5], x = 2, k = 2

Output: 3

Explanation:

Use 3 operations to subtract 3 from nums[4]. The resulting array is [9, -2, -2, -2, -2, 5].
Now, all elements within each subarray [-2, -2] (from indices 1 to 2) and [-2, -2] (from indices 3 to 4) are equal. 
Since 3 operations were used, 3 is the output.
 

Constraints:

2 <= nums.length <= 105
-106 <= nums[i] <= 106
2 <= x <= nums.length
1 <= k <= 15
2 <= k * x <= nums.length   */


class Solution {
public:
    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size();

        multiset<long long> low, high;
        long long sumLow = 0, sumHigh = 0;

        vector<long long> cost(n - x + 1);

        auto balance = [&]() {
            while (low.size() > high.size() + 1) {
                auto it = prev(low.end());
                long long val = *it;

                sumLow -= val;
                low.erase(it);

                high.insert(val);
                sumHigh += val;
            }

            while (low.size() < high.size()) {
                auto it = high.begin();
                long long val = *it;

                sumHigh -= val;
                high.erase(it);

                low.insert(val);
                sumLow += val;
            }
        };

        auto add = [&](long long val) {
            if (low.empty() || val <= *prev(low.end())) {
                low.insert(val);
                sumLow += val;
            } else {
                high.insert(val);
                sumHigh += val;
            }

            balance();
        };

        auto remove = [&](long long val) {
            auto it = low.find(val);

            if (it != low.end()) {
                low.erase(it);
                sumLow -= val;
            } else {
                it = high.find(val);
                high.erase(it);
                sumHigh -= val;
            }

            balance();
        };

        auto getCost = [&]() -> long long {
            long long median = *prev(low.end());

            return median * low.size() - sumLow
                 + sumHigh - median * high.size();
        };

        // Calculate cost of every window of size x.
        for (int i = 0; i < n; i++) {
            add(nums[i]);

            if (i >= x) {
                remove(nums[i - x]);
            }

            if (i >= x - 1) {
                cost[i - x + 1] = getCost();
            }
        }

        // DP with space optimization.
        const long long INF = LLONG_MAX / 4;

        vector<vector<long long>> dp(
            k + 1, vector<long long>(n + 1, INF)
        );

        for (int i = 0; i <= n; i++) {
            dp[0][i] = 0;
        }

        for (int j = 1; j <= k; j++) {
            for (int i = 1; i <= n; i++) {

                // Skip current element.
                dp[j][i] = dp[j][i - 1];

                // Select a window ending at i-1.
                if (i >= x && dp[j - 1][i - x] != INF) {
                    dp[j][i] = min(
                        dp[j][i],
                        dp[j - 1][i - x] + cost[i - x]
                    );
                }
            }
        }

        return dp[k][n];
    }
};

