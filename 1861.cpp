/*  1861. Rotating the Box

You are given an m x n matrix of characters boxGrid representing a side-view of a box. Each cell of the box is one of the following:

A stone '#'
A stationary obstacle '*'
Empty '.'
The box is rotated 90 degrees clockwise, causing some of the stones to fall due to gravity. Each stone falls down until it lands on an obstacle, 
another stone, or the bottom of the box. Gravity does not affect the obstacles' positions, and the inertia from the box's rotation does not affect the stones' 
horizontal positions.

It is guaranteed that each stone in boxGrid rests on an obstacle, another stone, or the bottom of the box.

Return an n x m matrix representing the box after the rotation described above.

Example 1:
Input: boxGrid = [["#",".","#"]]
Output: [["."],
         ["#"],
         ["#"]]
Example 2:
Input: boxGrid = [["#",".","*","."],
              ["#","#","*","."]]
Output: [["#","."],
         ["#","#"],
         ["*","*"],
         [".","."]]
Example 3:
Input: boxGrid = [["#","#","*",".","*","."],
              ["#","#","#","*",".","."],
              ["#","#","#",".","#","."]]
Output: [[".","#","#"],
         [".","#","#"],
         ["#","#","*"],
         ["#","*","."],
         ["#",".","*"],
         ["#",".","."]]
 

Constraints:
m == boxGrid.length
n == boxGrid[i].length
1 <= m, n <= 500
boxGrid[i][j] is either '#', '*', or '.'.  */


class Solution {
public:
    vector<vector<char>> rotateTheBox(vector<vector<char>>& boxGrid) {
        int m = boxGrid.size();
        int n = boxGrid[0].size();

        // result after rotation will be n x m
        vector<vector<char>> res(n, vector<char>(m));

        // process each row
        for (int i = 0; i < m; i++) {
            int write = n - 1;  // where stones fall to (right side)
            
            for (int j = n - 1; j >= 0; j--) {
                if (boxGrid[i][j] == '*') {
                    res[j][m - i - 1] = '*';
                    write = j - 1; // reset segment
                }
                else if (boxGrid[i][j] == '#') {
                    res[write][m - i - 1] = '#';
                    write--;
                }
            }
            
            // fill remaining cells with '.'
            for (int j = 0; j < n; j++) {
                if (res[j][m - i - 1] != '#' && res[j][m - i - 1] != '*') {
                    res[j][m - i - 1] = '.';
                }
            }
        }

        return res;
    }
};
