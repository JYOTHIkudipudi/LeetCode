/*  411. Maximum Subarray With Equal Products

You are given an array of positive integers nums.

An array arr is called product equivalent if prod(arr) == lcm(arr) * gcd(arr), where:

prod(arr) is the product of all elements of arr.
gcd(arr) is the GCD of all elements of arr.
lcm(arr) is the LCM of all elements of arr.
Return the length of the longest product equivalent subarray of nums.

Example 1:

Input: nums = [1,2,1,2,1,1,1]

Output: 5

Explanation: 

The longest product equivalent subarray is [1, 2, 1, 1, 1], where prod([1, 2, 1, 1, 1]) = 2, gcd([1, 2, 1, 1, 1]) = 1, and lcm([1, 2, 1, 1, 1]) = 2.

Example 2:

Input: nums = [2,3,4,5,6]

Output: 3

Explanation: 

The longest product equivalent subarray is [3, 4, 5].

Example 3:

Input: nums = [1,2,3,1,4,5,1]

Output: 5

Constraints:

2 <= nums.length <= 100
1 <= nums[i] <= 10  */

class Solution {
public:
    int maxLength(vector<int>& nums) {
        int n = nums.size();
        int ans = 2; // any 2-element subarray always qualifies (n >= 2)

        for (int i = 0; i < n; i++) {
            long long prod = 1;
            long long g = 0;
            long long l = 1;

            for (int j = i; j < n; j++) {
                prod *= nums[j];
                g = gcd(g, (long long)nums[j]);
                l = lcm(l, (long long)nums[j]);

                if (prod > 25200) break; // prod can only grow; lcm*gcd <= 2520*10

                if (prod == l * g) {
                    ans = max(ans, j - i + 1);
                }
            }
        }

        return ans;
    }
};


