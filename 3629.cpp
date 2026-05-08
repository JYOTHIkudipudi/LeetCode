/*  3629. Minimum Jumps to Reach End via Prime Teleportation

You are given an integer array nums of length n.

You start at index 0, and your goal is to reach index n - 1.

From any index i, you may perform one of the following operations:

Adjacent Step: Jump to index i + 1 or i - 1, if the index is within bounds.
Prime Teleportation: If nums[i] is a prime number p, you may instantly jump to any index j != i such that nums[j] % p == 0.
Return the minimum number of jumps required to reach index n - 1.

 

Example 1:

Input: nums = [1,2,4,6]

Output: 2

Explanation:

One optimal sequence of jumps is:

Start at index i = 0. Take an adjacent step to index 1.
At index i = 1, nums[1] = 2 is a prime number. Therefore, we teleport to index i = 3 as nums[3] = 6 is divisible by 2.
Thus, the answer is 2.

Example 2:

Input: nums = [2,3,4,7,9]

Output: 2

Explanation:

One optimal sequence of jumps is:

Start at index i = 0. Take an adjacent step to index i = 1.
At index i = 1, nums[1] = 3 is a prime number. Therefore, we teleport to index i = 4 since nums[4] = 9 is divisible by 3.
Thus, the answer is 2.

Example 3:

Input: nums = [4,6,5,8]

Output: 3

Explanation:

Since no teleportation is possible, we move through 0 → 1 → 2 → 3. Thus, the answer is 3.
 

Constraints:

1 <= n == nums.length <= 105
1 <= nums[i] <= 106
  */


#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minJumps(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) return 0;

        int max_val = *max_element(nums.begin(), nums.end());
        vector<int> spf(max_val + 1, 0);
        for (int i = 2; i <= max_val; ++i) {
            if (spf[i] == 0) {
                for (int j = i; j <= max_val; j += i) {
                    if (spf[j] == 0) spf[j] = i;
                }
            }
        }

        // Map each prime factor to the indices containing numbers divisible by it
        unordered_map<int, vector<int>> prime_to_indices;
        for (int i = 0; i < n; ++i) {
            int temp = nums[i];
            while (temp > 1) {
                int p = spf[temp];
                prime_to_indices[p].push_back(i);
                while (temp % p == 0) temp /= p;
            }
        }

        queue<int> q;
        q.push(0);
        vector<int> dist(n, -1);
        dist[0] = 0;
        vector<bool> visited_prime(max_val + 1, false);

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            if (u == n - 1) return dist[u];

            // Standard moves: i+1 and i-1
            for (int v : {u - 1, u + 1}) {
                if (v >= 0 && v < n && dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }

            // Prime Teleportation: If nums[u] is prime
            if (spf[nums[u]] == nums[u] && !visited_prime[nums[u]]) {
                visited_prime[nums[u]] = true;
                for (int v : prime_to_indices[nums[u]]) {
                    if (dist[v] == -1) {
                        dist[v] = dist[u] + 1;
                        q.push(v);
                    }
                }
            }
        }

        return -1;
    }
};

};
