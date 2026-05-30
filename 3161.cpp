/*  3161. Block Placement Queries

There exists an infinite number line, with its origin at 0 and extending towards the positive x-axis.

You are given a 2D array queries, which contains two types of queries:

For a query of type 1, queries[i] = [1, x]. Build an obstacle at distance x from the origin. It is guaranteed that there is no obstacle at distance x when the query is asked.
For a query of type 2, queries[i] = [2, x, sz]. Check if it is possible to place a block of size sz anywhere in the range [0, x] on the line, such that the block entirely lies in the range [0, x]. A block cannot be placed if it intersects with any obstacle, but it may touch it. Note that you do not actually place the block. Queries are separate.
Return a boolean array results, where results[i] is true if you can place the block specified in the ith query of type 2, and false otherwise.

 

Example 1:

Input: queries = [[1,2],[2,3,3],[2,3,1],[2,2,2]]

Output: [false,true,true]

Explanation:



For query 0, place an obstacle at x = 2. A block of size at most 2 can be placed before x = 3.

Example 2:

Input: queries = [[1,7],[2,7,6],[1,2],[2,7,5],[2,7,6]]

Output: [true,true,false]

Explanation:



Place an obstacle at x = 7 for query 0. A block of size at most 7 can be placed before x = 7.
Place an obstacle at x = 2 for query 2. Now, a block of size at most 5 can be placed before x = 7, and a block of size at most 2 before x = 2.
 

Constraints:

1 <= queries.length <= 15 * 104
2 <= queries[i].length <= 3
1 <= queries[i][0] <= 2
1 <= x, sz <= min(5 * 104, 3 * queries.length)
The input is generated such that for queries of type 1, no obstacle exists at distance x when the query is asked.
The input is generated such that there is at least one query of type 2.  */


class Solution {
    static const int MAXX = 50001;
    int tree[4 * MAXX];
    
    void update(int node, int l, int r, int pos, int val) {
        if (l == r) { tree[node] = val; return; }
        int mid = (l + r) / 2;
        if (pos <= mid) update(2*node, l, mid, pos, val);
        else            update(2*node+1, mid+1, r, pos, val);
        tree[node] = max(tree[2*node], tree[2*node+1]);
    }
    
    int query(int node, int l, int r, int ql, int qr) {
        if (ql > qr || qr < l || r < ql) return 0;
        if (ql <= l && r <= qr) return tree[node];
        int mid = (l + r) / 2;
        return max(query(2*node, l, mid, ql, qr),
                   query(2*node+1, mid+1, r, ql, qr));
    }

public:
    vector<bool> getResults(vector<vector<int>>& queries) {
        set<int> obs = {0};   // left sentinel only
        vector<bool> ans;
        memset(tree, 0, sizeof(tree));

        auto addObstacle = [&](int x) {
            auto [it, _] = obs.insert(x);
            auto prev = std::prev(it);
            auto next = std::next(it);

            // New gap: [*prev → x], stored at right endpoint x
            update(1, 0, MAXX, x, x - *prev);

            // If a real obstacle exists to the right, shrink its gap
            if (next != obs.end()) {
                update(1, 0, MAXX, *next, *next - x);
            }
        };

        for (auto& q : queries) {
            if (q[0] == 1) {
                addObstacle(q[1]);
            } else {
                int x = q[1], sz = q[2];

                // Gap from last obstacle before x up to x (x as right wall)
                auto it = obs.upper_bound(x);  // first obstacle > x
                --it;                           // last obstacle <= x
                int gapToX = x - *it;          // gap [*it, x]

                // Max gap stored in tree with right endpoint in [1, x]
                // plus the live gap ending at x itself
                int maxGap = max(gapToX, query(1, 0, MAXX, 1, x));
                ans.push_back(maxGap >= sz);
            }
        }
        return ans;
    }
};
