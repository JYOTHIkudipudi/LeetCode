/* Ways to Express as Sum of Consecutives

Given a number n, find the number of ways to represent this number as a sum of 2 or more consecutive natural numbers.

Examples:

Input: n = 10
Output: 1
Explanation: There is only one way, 10 = 1+2+3+4.
Input: n = 15
Output: 3
Explanation: There are 3 ways, (15 = 1+2+3+4+5), (15 = 4+5+6) and (15 = 7+8).
Constraints:
1 ≤ n ≤ 108  */

class Solution {
public:
    int getCount(int n) {
        int ans = 0;

        for (long long k = 2; k * (k + 1) / 2 <= n; k++) {
            long long t = n - k * (k - 1) / 2;
            if (t > 0 && t % k == 0)
                ans++;
        }

        return ans;
    }
};
