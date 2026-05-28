/*   3093. Longest Common Suffix Queries

You are given two arrays of strings wordsContainer and wordsQuery.

For each wordsQuery[i], you need to find a string from wordsContainer that has the longest common suffix with wordsQuery[i]. If there are two or more strings in wordsContainer that share the longest common suffix, find the string that is the smallest in length. If there are two or more such strings that have the same smallest length, find the one that occurred earlier in wordsContainer.

Return an array of integers ans, where ans[i] is the index of the string in wordsContainer that has the longest common suffix with wordsQuery[i].

 

Example 1:

Input: wordsContainer = ["abcd","bcd","xbcd"], wordsQuery = ["cd","bcd","xyz"]

Output: [1,1,1]

Explanation:

Let's look at each wordsQuery[i] separately:

For wordsQuery[0] = "cd", strings from wordsContainer that share the longest common suffix "cd" are at indices 0, 1, and 2. Among these, the answer is the string at index 1 because it has the shortest length of 3.
For wordsQuery[1] = "bcd", strings from wordsContainer that share the longest common suffix "bcd" are at indices 0, 1, and 2. Among these, the answer is the string at index 1 because it has the shortest length of 3.
For wordsQuery[2] = "xyz", there is no string from wordsContainer that shares a common suffix. Hence the longest common suffix is "", that is shared with strings at index 0, 1, and 2. Among these, the answer is the string at index 1 because it has the shortest length of 3.
Example 2:

Input: wordsContainer = ["abcdefgh","poiuygh","ghghgh"], wordsQuery = ["gh","acbfgh","acbfegh"]

Output: [2,0,2]

Explanation:

Let's look at each wordsQuery[i] separately:

For wordsQuery[0] = "gh", strings from wordsContainer that share the longest common suffix "gh" are at indices 0, 1, and 2. Among these, the answer is the string at index 2 because it has the shortest length of 6.
For wordsQuery[1] = "acbfgh", only the string at index 0 shares the longest common suffix "fgh". Hence it is the answer, even though the string at index 2 is shorter.
For wordsQuery[2] = "acbfegh", strings from wordsContainer that share the longest common suffix "gh" are at indices 0, 1, and 2. Among these, the answer is the string at index 2 because it has the shortest length of 6.
 

Constraints:

1 <= wordsContainer.length, wordsQuery.length <= 104
1 <= wordsContainer[i].length <= 5 * 103
1 <= wordsQuery[i].length <= 5 * 103
wordsContainer[i] consists only of lowercase English letters.
wordsQuery[i] consists only of lowercase */

struct TrieNode {
    int children[26];
    int idx;
    int len;
};

const int MAXNODES = 5000005;
TrieNode pool[MAXNODES];  // global = heap, no stack overflow
int poolSize;

int newNode() {
    for (int i = 0; i < 26; i++) pool[poolSize].children[i] = -1;
    pool[poolSize].idx = -1;
    pool[poolSize].len = INT_MAX;
    return poolSize++;
}

class Solution {
public:
    vector<int> stringIndices(vector<string>& wordsContainer, vector<string>& wordsQuery) {
        poolSize = 0;
        int root = newNode();

        for (int i = 0; i < (int)wordsContainer.size(); i++) {
            string& w = wordsContainer[i];
            int node = root;

            if ((int)w.size() < pool[node].len) {
                pool[node].len = w.size();
                pool[node].idx = i;
            }

            for (int j = (int)w.size() - 1; j >= 0; j--) {
                int c = w[j] - 'a';
                if (pool[node].children[c] == -1)
                    pool[node].children[c] = newNode();
                node = pool[node].children[c];

                if ((int)w.size() < pool[node].len) {
                    pool[node].len = w.size();
                    pool[node].idx = i;
                }
            }
        }

        vector<int> ans;
        ans.reserve(wordsQuery.size());

        for (string& q : wordsQuery) {
            int node = root;
            for (int j = (int)q.size() - 1; j >= 0; j--) {
                int c = q[j] - 'a';
                if (pool[node].children[c] == -1) break;
                node = pool[node].children[c];
            }
            ans.push_back(pool[node].idx);
        }

        return ans;
    }
};
