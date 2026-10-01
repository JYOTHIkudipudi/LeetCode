/* 20. Valid Parentheses

Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.

An input string is valid if:

Open brackets must be closed by the same type of brackets.
Open brackets must be closed in the correct order.
Every close bracket has a corresponding open bracket of the same type.
 

Example 1:

Input: s = "()"

Output: true

Example 2:

Input: s = "()[]{}"

Output: true

Example 3:

Input: s = "(]"

Output: false

Example 4:

Input: s = "([])"

Output: true

Example 5:

Input: s = "([)]"

Output: false

 

Constraints:

1 <= s.length <= 104
s consists of parentheses only '()[]{}'.
 
 */

class Solution {
public:
    bool isValid(string s) {

        stack<char> st;

        for(char c : s) {

            // Opening brackets
            if(c == '(' || c == '[' || c == '{') {
                st.push(c);
            }

            // Closing brackets
            else {

                if(st.empty())
                    return false;

                char top = st.top();

                if(c == ')' && top != '(')
                    return false;

                if(c == ']' && top != '[')
                    return false;

                if(c == '}' && top != '{')
                    return false;

                st.pop();
            }
        }

        return st.empty();
    }
};
