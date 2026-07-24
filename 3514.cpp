/*  3514. Number of Unique XOR Triplets II

You are given an integer array nums.

A XOR triplet is defined as the XOR of three elements nums[i] XOR nums[j] XOR nums[k] where i <= j <= k.

Return the number of unique XOR triplet values from all possible triplets (i, j, k).

 

Example 1:

Input: nums = [1,3]

Output: 2

Explanation:

The possible XOR triplet values are:

(0, 0, 0) → 1 XOR 1 XOR 1 = 1
(0, 0, 1) → 1 XOR 1 XOR 3 = 3
(0, 1, 1) → 1 XOR 3 XOR 3 = 1
(1, 1, 1) → 3 XOR 3 XOR 3 = 3
The unique XOR values are {1, 3}. Thus, the output is 2.

Example 2:

Input: nums = [6,7,8,9]

Output: 4

Explanation:

The possible XOR triplet values are {6, 7, 8, 9}. Thus, the output is 4.

 

Constraints:

1 <= nums.length <= 1500
1 <= nums[i] <= 1500  */


class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        vector<int> present(2048, 0);

        // Remove duplicates
        vector<int> vals;
        for (int x : nums) {
            if (!present[x]) {
                present[x] = 1;
                vals.push_back(x);
            }
        }

        // All possible XORs of two elements
        vector<int> pairXor(2048, 0);
        for (int a : vals) {
            for (int b : vals) {
                pairXor[a ^ b] = 1;
            }
        }

        // XOR the pair results with a third element
        vector<int> ans(2048, 0);
        for (int x = 0; x < 2048; x++) {
            if (pairXor[x]) {
                for (int y : vals) {
                    ans[x ^ y] = 1;
                }
            }
        }

        int count = 0;
        for (int x : ans) {
            count += x;
        }

        return count;
    }
};
