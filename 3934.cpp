/* 3934. Smallest Unique Subarray

You are given an integer array nums.

Find the minimum length of a subarray that is not identical to any other subarray in nums.

Return an integer denoting the minimum possible length of such a subarray.

Two subarrays are considered identical if they have the same length and the same elements in corresponding positions.

 

Example 1:

Input: nums = [3,3,3]

Output: 3

Explanation:

Subarrays of length 1: [3] → appears 3 times
Subarrays of length 2: [3, 3] → appears 2 times
Subarrays of length 3: [3, 3, 3] → appears once
The subarray [3, 3, 3] is unique, so the smallest unique subarray length is 3.

Example 2:

Input: nums = [2,1,2,3,3]

Output: 1

Explanation:

Subarrays of length 1:

[2] → appears 2 times
[1] → appears once
[3] → appears 2 times
The subarray [1] is unique, so the smallest unique subarray length is 1.
Example 3:

Input: nums = [1,1,2,2,1]

Output: 2

Explanation:

Subarrays of length 1:

[1] → appears 3 times
[2] → appears 2 times
Subarrays of length 2:

[1, 1] → appears once
[1, 2] → appears once
[2, 2] → appears once
[2, 1] → appears once
There is at least one subarray of length 2 that is unique, so the smallest unique subarray length is 2.
 

Constraints:

1 <= nums.length <= 105
1 <= nums[i] <= 105  */


 class Solution {
public:
    typedef unsigned long long ull;
    static const ull MOD = (1ULL << 61) - 1;

    static ull mulmod(ull a, ull b) {
        __uint128_t t = (__uint128_t)a * b;
        ull lo = (ull)(t & MOD), hi = (ull)(t >> 61);
        ull r = lo + hi;
        if (r >= MOD) r -= MOD;
        return r;
    }

    int smallestUniqueSubarray(vector<int>& nums) {
        int n = nums.size();

        mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
        ull base = rng() % (MOD - 1000) + 500;

        // prefix hashes and powers
        vector<ull> h(n + 1, 0), pw(n + 1, 1);
        for (int i = 0; i < n; i++) {
            h[i + 1] = (mulmod(h[i], base) + (ull)nums[i]) % MOD;
            pw[i + 1] = mulmod(pw[i], base);
        }

        auto hasUnique = [&](int L) -> bool {
            vector<ull> v;
            v.reserve(n - L + 1);
            for (int i = 0; i + L <= n; i++) {
                ull cur = (h[i + L] + MOD - mulmod(h[i], pw[L])) % MOD;
                v.push_back(cur);
            }
            sort(v.begin(), v.end());
            int m = v.size();
            for (int i = 0; i < m; ) {
                int j = i;
                while (j < m && v[j] == v[i]) j++;
                if (j - i == 1) return true;
                i = j;
            }
            return false;
        };

        int lo = 1, hi = n;  // L = n is always unique
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (hasUnique(mid)) hi = mid;
            else lo = mid + 1;
        }
        return lo;
    }
};
