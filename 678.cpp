/*  678. Valid Parenthesis String

Given a string s containing only three types of characters: '(', ')' and '*', return true if s is valid.

The following rules define a valid string:

Any left parenthesis '(' must have a corresponding right parenthesis ')'.
Any right parenthesis ')' must have a corresponding left parenthesis '('.
Left parenthesis '(' must go before the corresponding right parenthesis ')'.
'*' could be treated as a single right parenthesis ')' or a single left parenthesis '(' or an empty string "".
 

Example 1:

Input: s = "()"
Output: true
Example 2:

Input: s = "(*)"
Output: true
Example 3:

Input: s = "(*))"
Output: true
Example 4:

Input: s = "("
Output: false
 

Constraints:

1 <= s.length <= 100
s[i] is '(', ')' or '*'.   */

class Solution {
public:
    bool checkValidString(string s) {
        int low = 0;
        int high = 0;

        for (char c : s) {

            if (c == '(') {
                low++;
                high++;
            }
            else if (c == ')') {
                low--;
                high--;
            }
            else { // '*'
                low--;   // '*' as ')'
                high++;  // '*' as '('
            }

            // Minimum cannot go below 0
            low = max(0, low);

            // Even maximum is negative -> impossible
            if (high < 0)
                return false;
        }

        return low == 0;
    }
};
