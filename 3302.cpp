/*  3302. Find the Lexicographically Smallest Valid Sequence

You are given two strings word1 and word2.

A string x is called almost equal to y if you can change at most one character in x to make it identical to y.

A sequence of indices seq is called valid if:

The indices are sorted in ascending order.
Concatenating the characters at these indices in word1 in the same order results in a string that is almost equal to word2.
Return an array of size word2.length representing the lexicographically smallest valid sequence of indices. 
If no such sequence of indices exists, return an empty array.

Note that the answer must represent the lexicographically smallest array, not the corresponding string formed by those indices.

 

Example 1:

Input: word1 = "vbcca", word2 = "abc"

Output: [0,1,2]

Explanation:

The lexicographically smallest valid sequence of indices is [0, 1, 2]:

Change word1[0] to 'a'.
word1[1] is already 'b'.
word1[2] is already 'c'.
Example 2:

Input: word1 = "bacdc", word2 = "abc"

Output: [1,2,4]

Explanation:

The lexicographically smallest valid sequence of indices is [1, 2, 4]:

word1[1] is already 'a'.
Change word1[2] to 'b'.
word1[4] is already 'c'.
Example 3:

Input: word1 = "aaaaaa", word2 = "aaabc"

Output: []

Explanation:

There is no valid sequence of indices.

Example 4:

Input: word1 = "abc", word2 = "ab"

Output: [0,1]

 

Constraints:

1 <= word2.length < word1.length <= 3 * 105
word1 and word2 consist only of lowercase English letters.  */

class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();

        vector<int> pos[26];
        for (int i = 0; i < n; i++) {
            pos[word1[i] - 'a'].push_back(i);
        }

        vector<int> exact(m + 1, -1);
        vector<int> one(m + 1, -1);

        exact[m] = n;
        one[m] = n;

        for (int j = m - 1; j >= 0; j--) {
            int c = word2[j] - 'a';

            int limit = exact[j + 1] - 1;
            if (limit >= 0) {
                auto &v = pos[c];
                auto it = upper_bound(v.begin(), v.end(), limit);
                if (it != v.begin()) {
                    --it;
                    exact[j] = *it;
                }
            }

            limit = one[j + 1] - 1;
            if (limit >= 0) {
                auto &v = pos[c];
                auto it = upper_bound(v.begin(), v.end(), limit);
                if (it != v.begin()) {
                    --it;
                    one[j] = *it;
                }
            }

            limit = exact[j + 1] - 1;
            if (limit >= 0) {
                for (int ch = 0; ch < 26; ch++) {
                    if (ch == c || pos[ch].empty())
                        continue;
                    auto it = upper_bound(pos[ch].begin(), pos[ch].end(), limit);
                    if (it != pos[ch].begin()) {
                        --it;
                        one[j] = max(one[j], *it);
                    }
                }
            }
        }

        vector<int> ans;
        int cur = 0;
        bool mismatchUsed = false;

        for (int j = 0; j < m; j++) {
            bool found = false;

            while (cur < n) {
                if (word1[cur] == word2[j]) {
                    if (exact[j + 1] > cur) {
                        ans.push_back(cur++);
                        found = true;
                        break;
                    }
                    if (!mismatchUsed && one[j + 1] > cur) {
                        ans.push_back(cur++);
                        found = true;
                        break;
                    }
                }
                else if (!mismatchUsed && exact[j + 1] > cur) {
                    ans.push_back(cur++);
                    mismatchUsed = true;
                    found = true;
                    break;
                }
                cur++;
            }

            if (!found)
                return {};
        }

        return ans;
    }
};
