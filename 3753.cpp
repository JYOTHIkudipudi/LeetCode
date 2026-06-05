/*  3753. Total Waviness of Numbers in Range II

You are given two integers num1 and num2 representing an inclusive range [num1, num2].

The waviness of a number is defined as the total count of its peaks and valleys:

A digit is a peak if it is strictly greater than both of its immediate neighbors.
A digit is a valley if it is strictly less than both of its immediate neighbors.
The first and last digits of a number cannot be peaks or valleys.
Any number with fewer than 3 digits has a waviness of 0.
Return the total sum of waviness for all numbers in the range [num1, num2].
 

Example 1:

Input: num1 = 120, num2 = 130

Output: 3

Explanation:

In the range [120, 130]:

120: middle digit 2 is a peak, waviness = 1.
121: middle digit 2 is a peak, waviness = 1.
130: middle digit 3 is a peak, waviness = 1.
All other numbers in the range have a waviness of 0.
Thus, total waviness is 1 + 1 + 1 = 3.

Example 2:

Input: num1 = 198, num2 = 202

Output: 3

Explanation:

In the range [198, 202]:

198: middle digit 9 is a peak, waviness = 1.
201: middle digit 0 is a valley, waviness = 1.
202: middle digit 0 is a valley, waviness = 1.
All other numbers in the range have a waviness of 0.
Thus, total waviness is 1 + 1 + 1 = 3.

Example 3:

Input: num1 = 4848, num2 = 4848

Output: 2

Explanation:

Number 4848: the second digit 8 is a peak, and the third digit 4 is a valley, giving a waviness of 2.

 

Constraints:

1 <= num1 <= num2 <= 1015​​​​​​​  */


  class Solution {
public:
    struct Node {
        long long cnt;
        long long wav;
    };

    Node dp[16][11][11][2][2];
    bool vis[16][11][11][2][2];
    string num;

    Node solve(int pos, int pp, int p, bool tight, bool started) {
        if (pos == (int)num.size()) {
            return {1, 0};
        }

        int ppi = pp + 1;
        int pi = p + 1;

        if (vis[pos][ppi][pi][tight][started])
            return dp[pos][ppi][pi][tight][started];

        vis[pos][ppi][pi][tight][started] = true;

        Node res = {0, 0};

        int limit = tight ? num[pos] - '0' : 9;

        for (int d = 0; d <= limit; d++) {
            bool ntight = tight && (d == limit);

            if (!started && d == 0) {
                Node child = solve(pos + 1, -1, -1, ntight, false);
                res.cnt += child.cnt;
                res.wav += child.wav;
            }
            else if (!started) {
                Node child = solve(pos + 1, -1, d, ntight, true);
                res.cnt += child.cnt;
                res.wav += child.wav;
            }
            else {
                bool wave = false;

                if (pp != -1) {
                    wave = ((p > pp && p > d) ||
                            (p < pp && p < d));
                }

                Node child = solve(pos + 1, p, d, ntight, true);

                res.cnt += child.cnt;
                res.wav += child.wav;

                if (wave)
                    res.wav += child.cnt;
            }
        }

        return dp[pos][ppi][pi][tight][started] = res;
    }

    long long count(long long n) {
        if (n < 0) return 0;

        num = to_string(n);
        memset(vis, 0, sizeof(vis));

        return solve(0, -1, -1, true, false).wav;
    }

    long long totalWaviness(long long num1, long long num2) {
        return count(num2) - count(num1 - 1);
    }
};
