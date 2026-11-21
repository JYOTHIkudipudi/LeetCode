/*  3331. Find Subtree Sizes After Changes

You are given a tree rooted at node 0 that consists of n nodes numbered from 0 to n - 1. 
The tree is represented by an array parent of size n, where parent[i] is the parent of node i. Since node 0 is the root, parent[0] == -1.

You are also given a string s of length n, where s[i] is the character assigned to node i.

We make the following changes on the tree one time simultaneously for all nodes x from 1 to n - 1:

Find the closest node y to node x such that y is an ancestor of x, and s[x] == s[y].
If node y does not exist, do nothing.
Otherwise, remove the edge between x and its current parent and make node y the new parent of x by adding an edge between them.
Return an array answer of size n where answer[i] is the size of the subtree rooted at node i in the final tree.

 

Example 1:

Input: parent = [-1,0,0,1,1,1], s = "abaabc"

Output: [6,3,1,1,1,1]

Explanation:


The parent of node 3 will change from node 1 to node 0.

Example 2:

Input: parent = [-1,0,4,0,1], s = "abbba"

Output: [5,2,1,1,1]

Explanation:


The following changes will happen at the same time:

The parent of node 4 will change from node 1 to node 0.
The parent of node 2 will change from node 4 to node 1.
 

Constraints:

n == parent.length == s.length
1 <= n <= 105
0 <= parent[i] <= n - 1 for all i >= 1.
parent[0] == -1
parent represents a valid tree.
s consists only of lowercase English letters.  */


class Solution {
public:
    vector<int> answer;

    void dfs(int node, vector<vector<int>>& adj,
             vector<int>& newParent, string& s,
             vector<int>& last) {

        int c = s[node] - 'a';
        int old = last[c];

        if (old != -1)
            newParent[node] = old;

        last[c] = node;

        for (int child : adj[node]) {
            dfs(child, adj, newParent, s, last);
        }

        last[c] = old;
    }

    int calculate(int node, vector<vector<int>>& adj) {
        int size = 1;

        for (int child : adj[node]) {
            size += calculate(child, adj);
        }

        answer[node] = size;
        return size;
    }

    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();

        vector<vector<int>> adj(n);

        // Build original tree
        for (int i = 1; i < n; i++) {
            adj[parent[i]].push_back(i);
        }

        vector<int> newParent = parent;
        vector<int> last(26, -1);

        // Find closest same-character ancestor
        dfs(0, adj, newParent, s, last);

        // Build modified tree
        vector<vector<int>> newAdj(n);

        for (int i = 1; i < n; i++) {
            newAdj[newParent[i]].push_back(i);
        }

        // Calculate subtree sizes
        answer.resize(n);
        calculate(0, newAdj);

        return answer;
    }
};

