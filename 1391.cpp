/*  1391. Check if There is a Valid Path in a Grid

You are given an m x n grid. Each cell of grid represents a street. The street of grid[i][j] can be:

1 which means a street connecting the left cell and the right cell.
2 which means a street connecting the upper cell and the lower cell.
3 which means a street connecting the left cell and the lower cell.
4 which means a street connecting the right cell and the lower cell.
5 which means a street connecting the left cell and the upper cell.
6 which means a street connecting the right cell and the upper cell.

You will initially start at the street of the upper-left cell (0, 0). A valid path in the grid is a path that starts from the upper left cell (0, 0)
and ends at the bottom-right cell (m - 1, n - 1). The path should only follow the streets.

Notice that you are not allowed to change any street.

Return true if there is a valid path in the grid or false otherwise.

 

Example 1:
Input: grid = [[2,4,3],[6,5,2]]
Output: true
Explanation: As shown you can start at cell (0, 0) and visit all the cells of the grid to reach (m - 1, n - 1).
Example 2:


Input: grid = [[1,2,1],[1,2,1]]
Output: false
Explanation: As shown you the street at cell (0, 0) is not connected with any street of any other cell and you will get stuck at cell (0, 0)
Example 3:

Input: grid = [[1,1,2]]
Output: false
Explanation: You will get stuck at cell (0, 1) and you cannot reach cell (0, 2).
 

Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 300
1 <= grid[i][j] <= 6   */

class Solution {
public:
    bool hasValidPath(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        queue<pair<int,int>> q;
        vector<vector<int>> vis(m, vector<int>(n,0));

        q.push({0,0});
        vis[0][0] = 1;

        // directions: up, down, left, right
        vector<vector<int>> dir = {{-1,0},{1,0},{0,-1},{0,1}};

        // allowed movements for each street type
        map<int, vector<int>> mp;
        mp[1] = {2,3};
        mp[2] = {0,1};
        mp[3] = {1,2};
        mp[4] = {1,3};
        mp[5] = {0,2};
        mp[6] = {0,3};

        // compatible street types when entering from direction
        vector<vector<int>> compatible = {
            {2,3,4}, // from up
            {2,5,6}, // from down
            {1,4,6}, // from left
            {1,3,5}  // from right
        };

        while(!q.empty()){
            auto [x,y] = q.front();
            q.pop();

            if(x == m-1 && y == n-1)
                return true;

            int type = grid[x][y];

            for(int d : mp[type]){
                int nx = x + dir[d][0];
                int ny = y + dir[d][1];

                if(nx>=0 && ny>=0 && nx<m && ny<n && !vis[nx][ny]){
                    int nextType = grid[nx][ny];

                    for(int c : compatible[d]){
                        if(c == nextType){
                            vis[nx][ny] = 1;
                            q.push({nx,ny});
                        }
                    }
                }
            }
        }

        return false;
    }
};
