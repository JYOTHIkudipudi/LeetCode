/*  3225. Maximum Score From Grid Operations

You are given a 2D matrix grid of size n x n. Initially, all cells of the grid are colored white. 
In one operation, you can select any cell of indices (i, j), and color black all the cells of the jth column starting from the top row down to the ith row.

The grid score is the sum of all grid[i][j] such that cell (i, j) is white and it has a horizontally adjacent black cell.

Return the maximum score that can be achieved after some number of operations.

Example 1:
Input: grid = [[0,0,0,0,0],[0,0,3,0,0],[0,1,0,0,0],[5,0,0,3,0],[0,0,0,0,2]]
Output: 11

Explanation:
In the first operation, we color all cells in column 1 down to row 3, and in the second operation, 
we color all cells in column 4 down to the last row. The score of the resulting grid is grid[3][0] + grid[1][2] + grid[3][3] which is equal to 11.

Example 2:
Input: grid = [[10,9,0,0,15],[7,1,0,8,0],[5,20,0,11,0],[0,0,0,1,2],[8,12,1,10,3]]
Output: 94

Explanation:
We perform operations on 1, 2, and 3 down to rows 1, 4, and 0, respectively. 
The score of the resulting grid is grid[0][0] + grid[1][0] + grid[2][1] + grid[4][1] + grid[1][3] + grid[2][3] + grid[3][3] + grid[4][3] + grid[0][4] 
which is equal to 94.


Constraints:
1 <= n == grid.length <= 100
n == grid[i].length
0 <= grid[i][j] <= 109  */

class Solution {
public:
    long long maximumScore(vector<vector<int>>& grid) {
        const int n = grid.size();

        // prefix[j][i] = sum of first i elements in column j
        vector<vector<long>> prefix(n, vector<long>(n + 1));

        // prevPick[i] = max score up to prev col, where prev col has height i
        vector<long> prevPick(n + 1);

        // prevSkip[i] = max score up to prev col, where col BEFORE prev has height i
        //               (meaning prev col was skipped / height = 0)
        vector<long> prevSkip(n + 1);

        for (int j = 0; j < n; ++j)
            for (int i = 0; i < n; ++i)
                prefix[j][i + 1] = prefix[j][i] + grid[i][j];

        for (int j = 1; j < n; ++j) {
            vector<long> currPick(n + 1);
            vector<long> currSkip(n + 1);

            for (int curr = 0; curr <= n; ++curr)
                for (int prev = 0; prev <= n; ++prev)
                    if (curr > prev) {
                        // curr column deeper than prev
                        // white cells in col j-1, rows [prev..curr) score
                        // (they're white since prev col height = prev,
                        //  and col j is black up to curr > those rows)
                        const long score = prefix[j-1][curr] - prefix[j-1][prev];
                        currPick[curr] = max(currPick[curr], prevSkip[prev] + score);
                        currSkip[curr] = max(currSkip[curr], prevSkip[prev] + score);
                    } else {
                        // prev column deeper than curr
                        // white cells in col j, rows [curr..prev) score
                        // (col j is white there, col j-1 is black there)
                        const long score = prefix[j][prev] - prefix[j][curr];
                        currPick[curr] = max(currPick[curr], prevPick[prev] + score);
                        currSkip[curr] = max(currSkip[curr], prevPick[prev]);
                        //                                   ↑ no score: col j skipped
                    }

            prevPick = move(currPick);
            prevSkip = move(currSkip);
        }

        return ranges::max(prevPick);
    }
};
