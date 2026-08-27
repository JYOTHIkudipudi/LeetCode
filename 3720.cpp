class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int n = s.size();
        vector<int> cnt(26, 0);

        for (char c : s) {
            cnt[c - 'a']++;
        }

        string ans;

        // Try matching target from left to right
        for (int i = 0; i < n; i++) {

            int cur = target[i] - 'a';

            // First, try to place exactly target[i]
            if (cnt[cur] > 0) {
                cnt[cur]--;
                ans += target[i];
                continue;
            }

            // Cannot match here.
            // Find smallest available character greater than target[i]
            for (int j = cur + 1; j < 26; j++) {
                if (cnt[j] > 0) {
                    ans += char('a' + j);
                    cnt[j]--;

                    // Append all remaining characters in sorted order
                    for (int k = 0; k < 26; k++) {
                        ans.append(cnt[k], char('a' + k));
                    }

                    return ans;
                }
            }

            // No greater character available here.
            // Backtrack to previous position and try increasing it.
            while (!ans.empty()) {
                char last = ans.back();
                ans.pop_back();
                cnt[last - 'a']++;

                int pos = ans.size();
                int targetChar = target[pos] - 'a';

                // Find smallest character greater than target[pos]
                for (int j = targetChar + 1; j < 26; j++) {
                    if (cnt[j] > 0) {
                        ans += char('a' + j);
                        cnt[j]--;

                        // Append remaining characters in ascending order
                        for (int k = 0; k < 26; k++) {
                            ans.append(cnt[k], char('a' + k));
                        }

                        return ans;
                    }
                }
            }

            return "";
        }

        // We matched target exactly.
        // Need a permutation strictly greater than target,
        // so backtrack and increase some previous position.
        while (!ans.empty()) {
            char last = ans.back();
            ans.pop_back();
            cnt[last - 'a']++;

            int pos = ans.size();
            int targetChar = target[pos] - 'a';

            for (int j = targetChar + 1; j < 26; j++) {
                if (cnt[j] > 0) {
                    ans += char('a' + j);
                    cnt[j]--;

                    for (int k = 0; k < 26; k++) {
                        ans.append(cnt[k], char('a' + k));
                    }

                    return ans;
                }
            }
        }

        return "";
    }
};
