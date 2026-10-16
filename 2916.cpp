/*  2916. Subarrays Distinct Element Sum of Squares II

You are given a 0-indexed integer array nums.

The distinct count of a subarray of nums is defined as:

Let nums[i..j] be a subarray of nums consisting of all the indices from i to j such that 0 <= i <= j < nums.length. 
Then the number of distinct values in nums[i..j] is called the distinct count of nums[i..j].
Return the sum of the squares of distinct counts of all subarrays of nums.

Since the answer may be very large, return it modulo 109 + 7.

A subarray is a contiguous non-empty sequence of elements within an array.

 

Example 1:

Input: nums = [1,2,1]
Output: 15
Explanation: Six possible subarrays are:
[1]: 1 distinct value
[2]: 1 distinct value
[1]: 1 distinct value
[1,2]: 2 distinct values
[2,1]: 2 distinct values
[1,2,1]: 2 distinct values
The sum of the squares of the distinct counts in all subarrays is equal to 12 + 12 + 12 + 22 + 22 + 22 = 15.
Example 2:

Input: nums = [2,2]
Output: 3
Explanation: Three possible subarrays are:
[2]: 1 distinct value
[2]: 1 distinct value
[2,2]: 1 distinct value
The sum of the squares of the distinct counts in all subarrays is equal to 12 + 12 + 12 = 3.
 

Constraints:

1 <= nums.length <= 105
1 <= nums[i] <= 105   */


class Solution {
public:
    static const int MOD = 1e9 + 7;

    struct SegmentTree {
        int n;
        vector<long long> sum, sq, lazy;

        SegmentTree(int n) : n(n) {
            sum.assign(4 * n, 0);
            sq.assign(4 * n, 0);
            lazy.assign(4 * n, 0);
        }

        void apply(int node, int l, int r, long long x) {
            long long len = r - l + 1;

            sq[node] = (sq[node]
                       + 2LL * x % MOD * sum[node] % MOD
                       + len % MOD * x % MOD * x % MOD) % MOD;

            sum[node] = (sum[node] + len * x) % MOD;
            lazy[node] = (lazy[node] + x) % MOD;
        }

        void push(int node, int l, int r) {
            if (lazy[node] == 0 || l == r) return;

            int mid = (l + r) / 2;
            apply(node * 2, l, mid, lazy[node]);
            apply(node * 2 + 1, mid + 1, r, lazy[node]);

            lazy[node] = 0;
        }

        void update(int node, int l, int r,
                    int ql, int qr, long long x) {
            if (ql > r || qr < l) return;

            if (ql <= l && r <= qr) {
                apply(node, l, r, x);
                return;
            }

            push(node, l, r);
            int mid = (l + r) / 2;

            update(node * 2, l, mid, ql, qr, x);
            update(node * 2 + 1, mid + 1, r, ql, qr, x);

            sum[node] = (sum[node * 2] + sum[node * 2 + 1]) % MOD;
            sq[node] = (sq[node * 2] + sq[node * 2 + 1]) % MOD;
        }

        void update(int l, int r, long long x) {
            if (l <= r) update(1, 0, n - 1, l, r, x);
        }

        long long query() {
            return sq[1];
        }
    };

    int sumCounts(vector<int>& nums) {
        int n = nums.size();
        SegmentTree st(n);
        vector<int> last(100001, -1);
        long long ans = 0;

        for (int i = 0; i < n; i++) {
            int p = last[nums[i]];

            // Increase distinct counts of subarrays
            // ending at i that start in [p + 1, i].
            st.update(p + 1, i, 1);

            ans = (ans + st.query()) % MOD;
            last[nums[i]] = i;
        }

        return (int)ans;
    }
};

