/* 115
Given two strings s and t, return *the number of distinct* ***subsequences**** of *s* which equals *t.

The test cases are generated so that the answer fits on a 32-bit signed integer.

**Example 1:**

```
Input: s = "rabbbit", t = "rabbit"
Output: 3
Explanation:
As shown below, there are 3 ways you can generate "rabbit" from s.
rabbbit
rabbbit
rabbbit

```

**Example 2:**

```
Input: s = "babgbag", t = "bag"
Output: 5
Explanation:
As shown below, there are 5 ways you can generate "bag" from s.
babgbag
babgbag
babgbag
babgbag
babgbag
```

**Constraints:**

- `1 <= s.length, t.length <= 1000`
- `s` and `t` consist of English letters.
*/

class Solution {
public:
    int numDistinct(string s, string t) {
        int n = s.size();
        int m = t.size();

        if (m > n)
            return 0;

        // Check whether every character of t exists in s
        vector<int> freq(256, 0);

        for (char c : s)
            freq[c]++;

        for (char c : t) {
            if (freq[c] == 0)
                return 0;
        }

        vector<unsigned long long> dp(m + 1, 0);
        dp[0] = 1;

        for (int i = 1; i <= n; i++) {
            for (int j = min(i, m); j >= 1; j--) {
                if (s[i - 1] == t[j - 1]) {
                    dp[j] += dp[j - 1];
                }
            }
        }

        return dp[m];
    }
};
