/*  Complete Binary Tree Traversal with Array Input

Given an integer array arr[] representing the nodes of a Complete Binary Tree in level order traversal, return the nodes at each level in sorted ascending order.

For every level of the binary tree, sort the values present at that level independently and return the resulting levels as a 2D array, 
where the i-th row contains the sorted values of the i-th level.

Examples:

Input: arr[] = [7, 6, 5, 4, 3, 2, 1]
Output: [[7], [5, 6], [1, 2, 3, 4]]
Explanation: The complete binary tree formed from the given level order traversal is:   
        
The nodes at each level after sorting are:
Level 0: [7]
Level 1: [5, 6]
Level 2: [1, 2, 3, 4]
Input: arr[] = [7, 16, 1, 4, 13]
Output: [[7], [1, 16], [4, 13]]
Explanation: The complete binary tree formed from the given level order traversal is:      
           
The nodes at each level after sorting are:
Level 0: [7]
Level 1: [1, 16]
Level 2: [4, 13]

Constraints:

1 ≤ arr.size() ≤ 104
1 ≤ arr[i] ≤ 109   */

class Solution {
public:
    vector<vector<int>> levelSort(vector<int>& arr) {
        vector<vector<int>> ans;

        int n = arr.size();
        int i = 0;
        int levelSize = 1;

        while (i < n) {
            vector<int> level;

            // Number of nodes available at this level
            int cnt = min(levelSize, n - i);

            // Collect nodes of current level
            for (int j = 0; j < cnt; j++) {
                level.push_back(arr[i + j]);
            }

            // Sort current level
            sort(level.begin(), level.end());

            // Store in answer
            ans.push_back(level);

            // Move to next level
            i += cnt;
            levelSize *= 2;
        }

        return ans;
    }
};
