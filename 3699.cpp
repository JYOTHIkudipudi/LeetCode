/*   3699. Number of ZigZag Arrays I

You are given three integers n, l, and r.

A ZigZag array of length n is defined as follows:

Each element lies in the range [l, r].
No two adjacent elements are equal.
No three consecutive elements form a strictly increasing or strictly decreasing sequence.
Return the total number of valid ZigZag arrays.

Since the answer may be large, return it modulo 109 + 7.

A sequence is said to be strictly increasing if each element is strictly greater than its previous one (if exists).

A sequence is said to be strictly decreasing if each element is strictly smaller than its previous one (if exists).

 

Example 1:

Input: n = 3, l = 4, r = 5

Output: 2

Explanation:

There are only 2 valid ZigZag arrays of length n = 3 using values in the range [4, 5]:

[4, 5, 4]
[5, 4, 5]​​​​​​​
Example 2:

Input: n = 3, l = 1, r = 3

Output: 10

Explanation:

There are 10 valid ZigZag arrays of length n = 3 using values in the range [1, 3]:

[1, 2, 1], [1, 3, 1], [1, 3, 2]
[2, 1, 2], [2, 1, 3], [2, 3, 1], [2, 3, 2]
[3, 1, 2], [3, 1, 3], [3, 2, 3]
All arrays meet the ZigZag conditions.

 

Constraints:

3 <= n <= 2000
1 <= l < r <= 2000   */
class Solution {
public:
    static constexpr int MOD = 1000000007;

    int zigZagArrays(int n, int l, int r) {
        int m = r - l + 1;

        // Use single allocation, reuse across iterations
        vector<long long> up(m + 1), down(m + 1);
        vector<long long> pUp(m + 2, 0), pDown(m + 2, 0);

        for (int v = 1; v <= m; v++) {
            up[v] = v - 1;
            down[v] = m - v;
        }

        for (int len = 3; len <= n; len++) {
            // Build prefix sums in-place
            pUp[0] = pDown[0] = 0;
            for (int v = 1; v <= m; v++) {
                pUp[v]  = (pUp[v-1]  + up[v])   % MOD;
                pDown[v] = (pDown[v-1] + down[v]) % MOD;
            }

            long long totalUp = pUp[m];

            // Update in reverse to avoid needing separate newUp/newDown
            // But up[v] depends on pDown[v-1], down[v] depends on totalUp - pUp[v]
            // Both only read prefix arrays (not up/down being written), safe to overwrite directly
            for (int v = 1; v <= m; v++) {
                up[v]   = pDown[v - 1];
                down[v] = (totalUp - pUp[v] + MOD) % MOD;
            }
        }

        long long ans = 0;
        for (int v = 1; v <= m; v++) {
            ans = (ans + up[v] + down[v]) % MOD;
        }

        return (int)ans;
    }
};
