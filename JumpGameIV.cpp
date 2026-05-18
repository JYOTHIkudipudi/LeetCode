/*   1345. Jump Game IV

Given an array of integers arr, you are initially positioned at the first index of the array.

In one step you can jump from index i to index:

i + 1 where: i + 1 < arr.length.
i - 1 where: i - 1 >= 0.
j where: arr[i] == arr[j] and i != j.
Return the minimum number of steps to reach the last index of the array.

Notice that you can not jump outside of the array at any time.

 

Example 1:

Input: arr = [100,-23,-23,404,100,23,23,23,3,404]
Output: 3
Explanation: You need three jumps from index 0 --> 4 --> 3 --> 9. Note that index 9 is the last index of the array.
Example 2:

Input: arr = [7]
Output: 0
Explanation: Start index is the last index. You do not need to jump.
Example 3:

Input: arr = [7,6,9,6,9,6,9,7]
Output: 1
Explanation: You can jump directly from index 0 to index 7 which is last index of the array.
 

Constraints:

1 <= arr.length <= 5 * 104
-108 <= arr[i] <= 108  */


#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minJumps(vector<int>& arr) {
        int n = arr.size();
        if (n == 1) return 0;

        unordered_map<int, vector<int>> mp;

        // store indices for each value
        for (int i = 0; i < n; i++) {
            mp[arr[i]].push_back(i);
        }

        vector<bool> visited(n, false);
        queue<pair<int, int>> q; // {index, steps}

        q.push({0, 0});
        visited[0] = true;

        while (!q.empty()) {
            auto [i, steps] = q.front();
            q.pop();

            // check neighbors
            vector<int> next;

            // i-1
            if (i - 1 >= 0 && !visited[i - 1]) {
                visited[i - 1] = true;
                q.push({i - 1, steps + 1});
            }

            // i+1
            if (i + 1 < n && !visited[i + 1]) {
                visited[i + 1] = true;
                q.push({i + 1, steps + 1});
            }

            // same value jumps
            if (mp.count(arr[i])) {
                for (int j : mp[arr[i]]) {
                    if (!visited[j]) {
                        visited[j] = true;
                        q.push({j, steps + 1});
                    }
                }
                // IMPORTANT: clear to avoid re-processing
                mp.erase(arr[i]);
            }

            if (i == n - 1) return steps;
        }

        return -1;
    }
};

