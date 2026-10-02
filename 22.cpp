/*  22. Generate Parentheses

Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.


Example 1:

Input: n = 3
Output: ["((()))","(()())","(())()","()(())","()()()"]
Example 2:

Input: n = 1
Output: ["()"]
 

Constraints:

1 <= n <= 8  */

class Solution {
public:
    void solve(int n, int open, int close, string current,
               vector<string>& ans) {

        // Complete valid parentheses string
        if (current.length() == 2 * n) {
            ans.push_back(current);
            return;
        }

        // We can add '(' if we still have opening brackets left
        if (open < n) {
            solve(n, open + 1, close, current + '(', ans);
        }

        // We can add ')' only if there is an unmatched '('
        if (close < open) {
            solve(n, open, close + 1, current + ')', ans);
        }
    }

    vector<string> generateParenthesis(int n) {
        vector<string> ans;

        solve(n, 0, 0, "", ans);

        return ans;
    }
};
