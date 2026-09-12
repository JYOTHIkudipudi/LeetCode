/* 3414. Maximum Score of Non-overlapping Intervals

You are given a 2D integer array intervals, where intervals[i] = [li, ri, weighti]. Interval i starts at position li and ends at ri,
and has a weight of weighti. You can choose up to 4 non-overlapping intervals. The score of the chosen intervals is defined as the total sum of their weights.

Return the lexicographically smallest array of at most 4 indices from intervals with maximum score, representing your choice of non-overlapping intervals.

Two intervals are said to be non-overlapping if they do not share any points. In particular, intervals sharing a left or right boundary are considered overlapping.

 

Example 1:

Input: intervals = [[1,3,2],[4,5,2],[1,5,5],[6,9,3],[6,7,1],[8,9,1]]

Output: [2,3]

Explanation:

You can choose the intervals with indices 2, and 3 with respective weights of 5, and 3.

Example 2:

Input: intervals = [[5,8,1],[6,7,7],[4,7,3],[9,10,6],[7,8,2],[11,14,3],[3,5,5]]

Output: [1,3,5,6]

Explanation:

You can choose the intervals with indices 1, 3, 5, and 6 with respective weights of 7, 6, 3, and 5.

 

Constraints:

1 <= intevals.length <= 5 * 104
intervals[i].length == 3
intervals[i] = [li, ri, weighti]
1 <= li <= ri <= 109
1 <= weighti <= 109
*/

class Solution {
public:
    struct Node {
        int l, r, idx;
        long long w;
    };

    vector<int> maximumWeight(vector<vector<int>>& intervals) {

        int n = intervals.size();

        vector<Node> a(n);

        for (int i = 0; i < n; i++) {
            a[i] = {
                intervals[i][0],
                intervals[i][1],
                i,
                intervals[i][2]
            };
        }

        // Sort by starting position
        sort(a.begin(), a.end(), [](Node& x, Node& y) {
            return x.l < y.l;
        });

        vector<int> starts(n);

        for (int i = 0; i < n; i++) {
            starts[i] = a[i].l;
        }

        // dp[i][k] = maximum score from i onward
        // using at most k intervals
        vector<vector<long long>> dp(n + 1, vector<long long>(5, 0));

        // Store selected original indices
        vector<vector<vector<int>>> ans(
            n + 1,
            vector<vector<int>>(5)
        );

        for (int i = n - 1; i >= 0; i--) {

            for (int k = 1; k <= 4; k++) {

                // Option 1: Skip current interval
                dp[i][k] = dp[i + 1][k];
                ans[i][k] = ans[i + 1][k];

                // Find next non-overlapping interval
                int nxt = upper_bound(
                    starts.begin(),
                    starts.end(),
                    a[i].r
                ) - starts.begin();

                // Option 2: Take current interval
                long long take =
                    a[i].w + dp[nxt][k - 1];

                vector<int> takeAns = ans[nxt][k - 1];

                takeAns.push_back(a[i].idx);

                sort(takeAns.begin(), takeAns.end());

                if (take > dp[i][k]) {

                    dp[i][k] = take;
                    ans[i][k] = takeAns;

                }
                else if (take == dp[i][k] &&
                         takeAns < ans[i][k]) {

                    ans[i][k] = takeAns;
                }
            }
        }

        return ans[0][4];
    }
};
