/*   3691. Maximum Total Subarray Value II

You are given an integer array nums of length n and an integer k.

You must select exactly k distinct subarrays nums[l..r] of nums.
Subarrays may overlap, but the exact same subarray (same l and r) cannot be chosen more than once.

The value of a subarray nums[l..r] is defined as: max(nums[l..r]) - min(nums[l..r]).

The total value is the sum of the values of all chosen subarrays.

Return the maximum possible total value you can achieve.

 

Example 1:

Input: nums = [1,3,2], k = 2

Output: 4

Explanation:

One optimal approach is:

Choose nums[0..1] = [1, 3]. The maximum is 3 and the minimum is 1, giving a value of 3 - 1 = 2.
Choose nums[0..2] = [1, 3, 2]. The maximum is still 3 and the minimum is still 1, so the value is also 3 - 1 = 2.
Adding these gives 2 + 2 = 4.

Example 2:

Input: nums = [4,2,5,1], k = 3

Output: 12

Explanation:

One optimal approach is:

Choose nums[0..3] = [4, 2, 5, 1]. The maximum is 5 and the minimum is 1, giving a value of 5 - 1 = 4.
Choose nums[1..3] = [2, 5, 1]. The maximum is 5 and the minimum is 1, so the value is also 4.
Choose nums[2..3] = [5, 1]. The maximum is 5 and the minimum is 1, so the value is again 4.
Adding these gives 4 + 4 + 4 = 12.

 

Constraints:

1 <= n == nums.length <= 5 * 10​​​​​​​4
0 <= nums[i] <= 109
1 <= k <= min(105, n * (n + 1) / 2)  */

class SparseTableRMQ {
public:
    int n, maxLog;
    vector<vector<int>> mx, mn;
    vector<int> lg;

    SparseTableRMQ(vector<int>& nums) {
        n = nums.size();
        maxLog = 32 - __builtin_clz(n) + 1;

        mx.assign(n, vector<int>(maxLog));
        mn.assign(n, vector<int>(maxLog));
        lg.assign(n + 1, 0);

        for (int i = 2; i <= n; i++)
            lg[i] = lg[i >> 1] + 1;

        for (int i = 0; i < n; i++) {
            mx[i][0] = nums[i];
            mn[i][0] = nums[i];
        }

        for (int j = 1; j < maxLog; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                mx[i][j] = max(mx[i][j - 1],
                               mx[i + (1 << (j - 1))][j - 1]);

                mn[i][j] = min(mn[i][j - 1],
                               mn[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    int queryMax(int l, int r) {
        int k = lg[r - l + 1];
        return max(mx[l][k], mx[r - (1 << k) + 1][k]);
    }

    int queryMin(int l, int r) {
        int k = lg[r - l + 1];
        return min(mn[l][k], mn[r - (1 << k) + 1][k]);
    }
};

class Solution {
public:
    long long maxTotalValue(vector<int>& nums, int k) {
        int n = nums.size();
        SparseTableRMQ st(nums);

        using T = tuple<long long, int, int>;

        priority_queue<T> pq;

        for (int l = 0; l < n; l++) {
            long long val =
                (long long)st.queryMax(l, n - 1) -
                st.queryMin(l, n - 1);

            pq.push({val, l, n - 1});
        }

        long long ans = 0;

        while (k--) {
            auto [val, l, r] = pq.top();
            pq.pop();

            ans += val;

            if (r > l) {
                long long nxt =
                    (long long)st.queryMax(l, r - 1) -
                    st.queryMin(l, r - 1);

                pq.push({nxt, l, r - 1});
            }
        }

        return ans;
    }
};
