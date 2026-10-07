/* 301. Remove Invalid Parentheses

Given a string s that contains parentheses and letters, remove the minimum number of invalid parentheses to make the input string valid.

Return a list of unique strings that are valid with the minimum number of removals. You may return the answer in any order.

 

Example 1:

Input: s = "()())()"
Output: ["(())()","()()()"]
Example 2:

Input: s = "(a)())()"
Output: ["(a())()","(a)()()"]
Example 3:

Input: s = ")("
Output: [""]
 

Constraints:

1 <= s.length <= 25
s consists of lowercase English letters and parentheses '(' and ')'.
There will be at most 20 parentheses in s.   */

class Solution {
public:
    bool isValid(string s) {
        int balance = 0;

        for (char c : s) {
            if (c == '(')
                balance++;
            else if (c == ')') {
                balance--;

                if (balance < 0)
                    return false;
            }
        }

        return balance == 0;
    }

    vector<string> removeInvalidParentheses(string s) {
        vector<string> ans;

        unordered_set<string> visited;
        queue<string> q;

        q.push(s);
        visited.insert(s);

        bool found = false;

        while (!q.empty()) {
            string curr = q.front();
            q.pop();

            // If current string is valid,
            // this is the minimum-removal level.
            if (isValid(curr)) {
                ans.push_back(curr);
                found = true;
            }

            // Once valid strings are found,
            // don't generate strings with more removals.
            if (found)
                continue;

            // Remove one character at every position
            for (int i = 0; i < curr.size(); i++) {

                // Only parentheses can make the string invalid.
                if (curr[i] != '(' && curr[i] != ')')
                    continue;

                string next = curr.substr(0, i) +
                              curr.substr(i + 1);

                // Avoid duplicate strings
                if (visited.find(next) == visited.end()) {
                    visited.insert(next);
                    q.push(next);
                }
            }
        }

        return ans;
    }
};
