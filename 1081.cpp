/* 1081. Smallest Subsequence of Distinct Characters

Given a string s, return the lexicographically smallest subsequence of s that contains all the distinct characters of s exactly once.

Example 1:

Input: s = "bcabc"
Output: "abc"
Example 2:

Input: s = "cbacdcbc"
Output: "acdb"
 

Constraints:

1 <= s.length <= 1000
s consists of lowercase English letters.   */

class Solution {
public:
    string smallestSubsequence(string s) {
        vector<int> last(26);

        // Store last occurrence of each character
        for (int i = 0; i < s.size(); i++)
            last[s[i] - 'a'] = i;

        vector<bool> used(26, false);
        string st;

        for (int i = 0; i < s.size(); i++) {
            char ch = s[i];

            // Skip if already included
            if (used[ch - 'a'])
                continue;

            // Remove larger characters if they appear later
            while (!st.empty() &&
                   st.back() > ch &&
                   last[st.back() - 'a'] > i) {
                used[st.back() - 'a'] = false;
                st.pop_back();
            }

            st.push_back(ch);
            used[ch - 'a'] = true;
        }

        return st;
    }
};
