/*  3116. Kth Smallest Amount With Single Denomination Combination

You are given an integer array coins representing coins of different denominations and an integer k.

You have an infinite number of coins of each denomination. However, you are not allowed to combine coins of different denominations.

Return the kth smallest amount that can be made using these coins.

 

Example 1:

Input: coins = [3,6,9], k = 3

Output: 9

Explanation: The given coins can make the following amounts:
Coin 3 produces multiples of 3: 3, 6, 9, 12, 15, etc.
Coin 6 produces multiples of 6: 6, 12, 18, 24, etc.
Coin 9 produces multiples of 9: 9, 18, 27, 36, etc.
All of the coins combined produce: 3, 6, 9, 12, 15, etc.

Example 2:

Input: coins = [5,2], k = 7

Output: 12

Explanation: The given coins can make the following amounts:
Coin 5 produces multiples of 5: 5, 10, 15, 20, etc.
Coin 2 produces multiples of 2: 2, 4, 6, 8, 10, 12, etc.
All of the coins combined produce: 2, 4, 5, 6, 8, 10, 12, 14, 15, etc.

 

Constraints:

1 <= coins.length <= 15
1 <= coins[i] <= 25
1 <= k <= 2 * 109
coins contains pairwise distinct integers.  */


class Solution {
public:
    using ll = long long;

    long long gcd(long long a, long long b) {
        while (b) {
            long long temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    long long lcm(long long a, long long b) {
        return a / gcd(a, b) * b;
    }

    long long findKthSmallest(vector<int>& coins, int k) {
        int n = coins.size();

        auto count = [&](long long x) -> long long {
            long long total = 0;

            for (int mask = 1; mask < (1 << n); mask++) {
                long long currentLCM = 1;
                int bits = 0;
                bool valid = true;

                for (int i = 0; i < n; i++) {
                    if (mask & (1 << i)) {
                        bits++;

                        currentLCM = lcm(currentLCM, coins[i]);

                        // Prevent unnecessary large LCM
                        if (currentLCM > x) {
                            valid = false;
                            break;
                        }
                    }
                }

                if (!valid) continue;

                long long multiples = x / currentLCM;

                if (bits % 2 == 1)
                    total += multiples;
                else
                    total -= multiples;
            }

            return total;
        };

        long long left = 1;
        long long right = 1LL * (*min_element(coins.begin(), coins.end())) * k;

        while (left < right) {
            long long mid = left + (right - left) / 2;

            if (count(mid) >= k)
                right = mid;
            else
                left = mid + 1;
        }

        return left;
    }
};
