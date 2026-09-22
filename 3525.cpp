/*  3525. Find X Value of Array II

You are given an array of positive integers nums and a positive integer k. You are also given a 2D array queries, where queries[i] = [indexi, valuei, starti, xi].

You are allowed to perform an operation once on nums, where you can remove any suffix from nums such that nums remains non-empty.

The x-value of nums for a given x is defined as the number of ways to perform this operation so that the product of the remaining 
elements leaves a remainder of x modulo k.

For each query in queries you need to determine the x-value of nums for xi after performing the following actions:

Update nums[indexi] to valuei. Only this step persists for the rest of the queries.
Remove the prefix nums[0..(starti - 1)] (where nums[0..(-1)] will be used to represent the empty prefix).
Return an array result of size queries.length where result[i] is the answer for the ith query.

A prefix of an array is a subarray that starts from the beginning of the array and extends to any point within it.

A suffix of an array is a subarray that starts at any point within the array and extends to the end of the array.

Note that the prefix and suffix to be chosen for the operation can be empty.

Note that x-value has a different definition in this version.

 

Example 1:

Input: nums = [1,2,3,4,5], k = 3, queries = [[2,2,0,2],[3,3,3,0],[0,1,0,1]]

Output: [2,2,2]

Explanation:

For query 0, nums becomes [1, 2, 2, 4, 5], and the empty prefix must be removed. The possible operations are:
Remove the suffix [2, 4, 5]. nums becomes [1, 2].
Remove the empty suffix. nums becomes [1, 2, 2, 4, 5] with a product 80, which gives remainder 2 when divided by 3.
For query 1, nums becomes [1, 2, 2, 3, 5], and the prefix [1, 2, 2] must be removed. The possible operations are:
Remove the empty suffix. nums becomes [3, 5].
Remove the suffix [5]. nums becomes [3].
For query 2, nums becomes [1, 2, 2, 3, 5], and the empty prefix must be removed. The possible operations are:
Remove the suffix [2, 2, 3, 5]. nums becomes [1].
Remove the suffix [3, 5]. nums becomes [1, 2, 2].
Example 2:

Input: nums = [1,2,4,8,16,32], k = 4, queries = [[0,2,0,2],[0,2,0,1]]

Output: [1,0]

Explanation:

For query 0, nums becomes [2, 2, 4, 8, 16, 32]. The only possible operation is:
Remove the suffix [2, 4, 8, 16, 32].
For query 1, nums becomes [2, 2, 4, 8, 16, 32]. There is no possible way to perform the operation.
Example 3:

Input: nums = [1,1,2,1,1], k = 2, queries = [[2,1,0,1]]

Output: [5]

 

Constraints:

1 <= nums[i] <= 109
1 <= nums.length <= 105
1 <= k <= 5
1 <= queries.length <= 2 * 104
queries[i] == [indexi, valuei, starti, xi]
0 <= indexi <= nums.length - 1
1 <= valuei <= 109
0 <= starti <= nums.length - 1
0 <= xi <= k - 1    */

class Solution {
public:
    struct Node {
        int prod;
        int cnt[5];

        Node() {
            prod = 1;
            memset(cnt, 0, sizeof(cnt));
        }
    };

    int k;
    vector<Node> seg;

    Node merge(const Node& L, const Node& R) {
        Node res;

        res.prod = (L.prod * R.prod) % k;

        // Prefixes completely inside left
        for (int r = 0; r < k; r++) {
            res.cnt[r] = L.cnt[r];
        }

        // Prefixes containing all of left + prefix of right
        for (int r = 0; r < k; r++) {
            int nr = (L.prod * r) % k;
            res.cnt[nr] += R.cnt[r];
        }

        return res;
    }

    void build(int p, int l, int r, const vector<int>& nums) {
        if (l == r) {
            int rem = nums[l] % k;

            seg[p].prod = rem;
            seg[p].cnt[rem] = 1;

            return;
        }

        int mid = (l + r) >> 1;

        build(p << 1, l, mid, nums);
        build(p << 1 | 1, mid + 1, r, nums);

        seg[p] = merge(seg[p << 1], seg[p << 1 | 1]);
    }

    void update(int p, int l, int r, int pos, int val) {
        if (l == r) {
            int rem = val % k;

            seg[p].prod = rem;

            memset(seg[p].cnt, 0, sizeof(seg[p].cnt));
            seg[p].cnt[rem] = 1;

            return;
        }

        int mid = (l + r) >> 1;

        if (pos <= mid)
            update(p << 1, l, mid, pos, val);
        else
            update(p << 1 | 1, mid + 1, r, pos, val);

        seg[p] = merge(seg[p << 1], seg[p << 1 | 1]);
    }

    // Accumulate the queried segment into ans.
    void query(
        int p,
        int l,
        int r,
        int ql,
        int qr,
        Node& ans,
        bool& empty
    ) {
        if (ql <= l && r <= qr) {
            if (empty) {
                ans = seg[p];
                empty = false;
            } else {
                ans = merge(ans, seg[p]);
            }
            return;
        }

        int mid = (l + r) >> 1;

        if (ql <= mid)
            query(p << 1, l, mid, ql, qr, ans, empty);

        if (qr > mid)
            query(p << 1 | 1, mid + 1, r, ql, qr, ans, empty);
    }

    vector<int> resultArray(
        vector<int>& nums,
        int K,
        vector<vector<int>>& queries
    ) {
        k = K;

        int n = nums.size();

        seg.resize(4 * n + 5);

        build(1, 0, n - 1, nums);

        vector<int> answer;
        answer.reserve(queries.size());

        for (const auto& q : queries) {
            int index = q[0];
            int value = q[1];
            int start = q[2];
            int x = q[3];

            // Persistent update
            update(1, 0, n - 1, index, value);

            Node res;
            bool empty = true;

            query(
                1,
                0,
                n - 1,
                start,
                n - 1,
                res,
                empty
            );

            answer.push_back(res.cnt[x]);
        }

        return answer;
    }
};
