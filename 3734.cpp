/*  3734. Lexicographically Smallest Palindromic Permutation Greater Than Target

You are given two strings s and target, each of length n, consisting of lowercase English letters.

Return the lexicographically smallest string that is both a palindromic permutation of s and strictly greater than target. 
If no such permutation exists, return an empty string.

 

Example 1:

Input: s = "baba", target = "abba"

Output: "baab"

Explanation:

The palindromic permutations of s (in lexicographical order) are "abba" and "baab".
The lexicographically smallest permutation that is strictly greater than target is "baab".
Example 2:

Input: s = "baba", target = "bbaa"

Output: ""

Explanation:

The palindromic permutations of s (in lexicographical order) are "abba" and "baab".
None of them is lexicographically strictly greater than target. Therefore, the answer is "".
Example 3:

Input: s = "abc", target = "abb"

Output: ""

Explanation:

s has no palindromic permutations. Therefore, the answer is "".

Example 4:

Input: s = "aac", target = "abb"

Output: "aca"

Explanation:

The only palindromic permutation of s is "aca".
"aca" is strictly greater than target. Therefore, the answer is "aca".
 

Constraints:

1 <= n == s.length == target.length <= 300
s and target consist of only lowercase English letters.
 */

class Solution {
public:
    string lexPalindromicPermutation(string s, string target) {
        int n = s.size();
        vector<int> cnt(26, 0);
        for (char ch : s) cnt[ch - 'a']++;

        // Check palindrome feasibility
        int oddCount = 0, oddChar = -1;
        for (int i = 0; i < 26; i++) {
            if (cnt[i] % 2 == 1) { oddCount++; oddChar = i; }
        }
        int mid = n % 2;
        if ((mid == 1 && oddCount != 1) || (mid == 0 && oddCount != 0)) return "";

        int h = n / 2;
        vector<int> halfCnt(26, 0);
        for (int i = 0; i < 26; i++) halfCnt[i] = cnt[i] / 2;
        char midChar = (mid == 1) ? char('a' + oddChar) : 0;

        string T1 = target.substr(0, h);
        string T2 = target.substr(h + mid, h);

        vector<int> t1cnt(26, 0);
        for (char ch : T1) t1cnt[ch - 'a']++;
        bool exactMatch = (t1cnt == halfCnt);

        auto buildFromF = [&](const string& F) -> string {
            string rev = F;
            reverse(rev.begin(), rev.end());
            string res = F;
            if (mid == 1) res += midChar;
            res += rev;
            return res;
        };

        // Case 1: F == T1 exactly (best possible if it works)
        if (exactMatch) {
            string revT1 = T1;
            reverse(revT1.begin(), revT1.end());
            bool success = false;
            if (mid == 1) {
                if (midChar > target[h]) success = true;
                else if (midChar == target[h] && revT1 > T2) success = true;
            } else {
                if (revT1 > T2) success = true;
            }
            if (success) return buildFromF(T1);
        }

        // Case 2: find smallest F > T1 (maximize matching prefix with T1)
        vector<int> used(26, 0);
        int bestP = -1;
        vector<int> bestUsed(26, 0);

        for (int p = 0; p < h; p++) {
            int tc = T1[p] - 'a';
            bool found = false;
            for (int c = tc + 1; c < 26; c++) {
                if (halfCnt[c] - used[c] > 0) { found = true; break; }
            }
            if (found) {
                bestP = p;
                bestUsed = used; // snapshot before consuming T1[p]
            }
            if (halfCnt[tc] - used[tc] > 0) {
                used[tc]++;
            } else {
                break; // can't extend exact prefix match further
            }
        }

        if (bestP == -1) return "";

        vector<int> remaining(26);
        for (int i = 0; i < 26; i++) remaining[i] = halfCnt[i] - bestUsed[i];

        int tc = T1[bestP] - 'a';
        int chosen = -1;
        for (int c = tc + 1; c < 26; c++) {
            if (remaining[c] > 0) { chosen = c; break; }
        }
        remaining[chosen]--;

        string F = T1.substr(0, bestP);
        F += char('a' + chosen);
        for (int c = 0; c < 26; c++)
            for (int k = 0; k < remaining[c]; k++) F += char('a' + c);

        return buildFromF(F);
    }
};

