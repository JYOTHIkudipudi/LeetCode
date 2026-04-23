/*  2615. Sum of Distances

You are given a 0-indexed integer array nums. There exists an array arr of length nums.length, where arr[i] is the sum of |i - j| over all j 
such that nums[j] == nums[i] and j != i. If there is no such j, set arr[i] to be 0.

Return the array arr.

 

Example 1:

Input: nums = [1,3,1,1,2]
Output: [5,0,3,4,0]
Explanation: 
When i = 0, nums[0] == nums[2] and nums[0] == nums[3]. Therefore, arr[0] = |0 - 2| + |0 - 3| = 5. 
When i = 1, arr[1] = 0 because there is no other index with value 3.
When i = 2, nums[2] == nums[0] and nums[2] == nums[3]. Therefore, arr[2] = |2 - 0| + |2 - 3| = 3. 
When i = 3, nums[3] == nums[0] and nums[3] == nums[2]. Therefore, arr[3] = |3 - 0| + |3 - 2| = 4. 
When i = 4, arr[4] = 0 because there is no other index with value 2. 

Example 2:

Input: nums = [0,5,3]
Output: [0,0,0]
Explanation: Since each element in nums is distinct, arr[i] = 0 for all i.
 

Constraints:

1 <= nums.length <= 105
0 <= nums[i] <= 109
 

Note: This question is the same as 2121: Intervals Between Identical Elements.  */

class Solution {
public:
    vector<long long> distance(vector<int>& nums) {
        int n = nums.size();
        vector<long long> ans(n, 0);
        
        unordered_map<int, vector<int>> mp;
        
        // Step 1: group indices
        for (int i = 0; i < n; i++) {
            mp[nums[i]].push_back(i);
        }
        
        // Step 2: process each group
        for (auto &it : mp) {
            vector<int> &idx = it.second;
            int k = idx.size();
            
            vector<long long> prefix(k, 0);
            
            // prefix sum of indices
            prefix[0] = idx[0];
            for (int i = 1; i < k; i++) {
                prefix[i] = prefix[i - 1] + idx[i];
            }
            
            for (int i = 0; i < k; i++) {
                long long left = 0, right = 0;
                
                // left part
                if (i > 0) {
                    left = (long long)idx[i] * i - prefix[i - 1];
                }
                
                // right part
                if (i < k - 1) {
                    right = (prefix[k - 1] - prefix[i]) - (long long)idx[i] * (k - i - 1);
                }
                
                ans[idx[i]] = left + right;
            }
        }
        
        return ans;
    }
};
