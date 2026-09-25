/*  1096. Brace Expansion II

Under the grammar given below, strings can represent a set of lowercase words. Let R(expr) denote the set of words the expression represents.

The grammar can best be understood through simple examples:

Single letters represent a singleton set containing that word.
R("a") = {"a"}
R("w") = {"w"}
When we take a comma-delimited list of two or more expressions, we take the union of possibilities.
R("{a,b,c}") = {"a","b","c"}
R("{{a,b},{b,c}}") = {"a","b","c"} (notice the final set only contains each word at most once)
When we concatenate two expressions, we take the set of possible concatenations between two words where the first word comes from the first expression and the second word comes from the second expression.
R("{a,b}{c,d}") = {"ac","ad","bc","bd"}
R("a{b,c}{d,e}f{g,h}") = {"abdfg", "abdfh", "abefg", "abefh", "acdfg", "acdfh", "acefg", "acefh"}
Formally, the three rules for our grammar:

For every lowercase letter x, we have R(x) = {x}.
For expressions e1, e2, ... , ek with k >= 2, we have R({e1, e2, ...}) = R(e1) ∪ R(e2) ∪ ...
For expressions e1 and e2, we have R(e1 + e2) = {a + b for (a, b) in R(e1) × R(e2)}, where + denotes concatenation, and × denotes the cartesian product.
Given an expression representing a set of words under the given grammar, return the sorted list of words that the expression represents.

 

Example 1:

Input: expression = "{a,b}{c,{d,e}}"
Output: ["ac","ad","ae","bc","bd","be"]
Example 2:

Input: expression = "{{a,z},a{b,c},{ab,z}}"
Output: ["a","ab","ac","z"]
Explanation: Each distinct word is written only once in the final answer.
 

Constraints:

1 <= expression.length <= 60
expression[i] consists of '{', '}', ','or lowercase English letters.
The given expression represents a set of words based on the grammar given in the description.  */

class Solution {
public:
    int index = 0;

    set<string> concatenate(set<string>& a, set<string>& b) {
        set<string> result;

        for (string x : a) {
            for (string y : b) {
                result.insert(x + y);
            }
        }

        return result;
    }

    // Handles concatenation
    set<string> parseTerm(string& s) {

        set<string> result;
        result.insert("");

        while (index < s.length() &&
               s[index] != '}' &&
               s[index] != ',') {

            set<string> next;

            if (s[index] == '{') {

                index++; // skip '{'

                next = parseExpression(s);

                index++; // skip '}'

            } 
            else {

                // Single character
                next.insert(string(1, s[index]));
                index++;
            }

            result = concatenate(result, next);
        }

        return result;
    }

    // Handles union
    set<string> parseExpression(string& s) {

        set<string> result = parseTerm(s);

        while (index < s.length() && s[index] == ',') {

            index++; // skip ','

            set<string> next = parseTerm(s);

            // Union
            result.insert(next.begin(), next.end());
        }

        return result;
    }

    vector<string> braceExpansionII(string expression) {

        set<string> result = parseExpression(expression);

        vector<string> answer(result.begin(), result.end());

        return answer;
    }
};
