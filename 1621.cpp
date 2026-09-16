/* 1621. Number of Sets of K Non-Overlapping Line Segments

Given n points on a 1-D plane, where the ith point (from 0 to n-1) is at x = i, 
find the number of ways we can draw exactly k non-overlapping line segments such that each segment covers two or more points. 
The endpoints of each segment must have integral coordinates. The k line segments do not have to cover all n points, and they are allowed to share endpoints.

Return the number of ways we can draw k non-overlapping line segments. Since this number can be huge, return it modulo 109 + 7.

 

Example 1:


Input: n = 4, k = 2
Output: 5
Explanation: The two line segments are shown in red and blue.
The image above shows the 5 different ways {(0,2),(2,3)}, {(0,1),(1,3)}, {(0,1),(2,3)}, {(1,2),(2,3)}, {(0,1),(1,2)}.
Example 2:

Input: n = 3, k = 1
Output: 3
Explanation: The 3 ways are {(0,1)}, {(0,2)}, {(1,2)}.
Example 3:

Input: n = 30, k = 7
Output: 796297179
Explanation: The total number of possible ways to draw 7 line segments is 3796297200. Taking this number modulo 109 + 7 gives us 796297179.
 

Constraints:

2 <= n <= 1000
1 <= k <= n-1  */

class Solution {
public:
    int numberOfSets(int n, int k) {
        const long long MOD = 1e9 + 7;

        // dp[i][j] = ways to make j segments using points 0...i
        vector<vector<long long>> dp(n, vector<long long>(k + 1, 0));

        // 0 segments can always be made in 1 way
        for (int i = 0; i < n; i++) {
            dp[i][0] = 1;
        }

        for (int j = 1; j <= k; j++) {
            long long prefix = 0;

            for (int i = 1; i < n; i++) {
                // dp[i-1][j-1] can be the configuration
                // before choosing the last segment ending at i.
                prefix = (prefix + dp[i - 1][j - 1]) % MOD;

                // Either:
                // 1. We don't use point i as the end of a segment.
                // 2. We choose a segment ending at i.
                dp[i][j] = (dp[i - 1][j] + prefix) % MOD;
            }
        }

        return dp[n - 1][k];
    }
};

