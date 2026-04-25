/*  
3464. Maximize the Distance Between Points on a Square

You are given an integer side, representing the edge length of a square with corners at (0, 0), (0, side), (side, 0), and (side, side) on a Cartesian plane.

You are also given a positive integer k and a 2D integer array points, where points[i] = [xi, yi] represents the coordinate of a point lying 
on the boundary of the square.

You need to select k elements among points such that the minimum Manhattan distance between any two points is maximized.

Return the maximum possible minimum Manhattan distance between the selected k points.

The Manhattan Distance between two cells (xi, yi) and (xj, yj) is |xi - xj| + |yi - yj|.

 

Example 1:

Input: side = 2, points = [[0,2],[2,0],[2,2],[0,0]], k = 4

Output: 2

Explanation:



Select all four points.

Example 2:

Input: side = 2, points = [[0,0],[1,2],[2,0],[2,2],[2,1]], k = 4

Output: 1

Explanation:



Select the points (0, 0), (2, 0), (2, 2), and (2, 1).

Example 3:

Input: side = 2, points = [[0,0],[0,1],[0,2],[1,2],[2,0],[2,2],[2,1]], k = 5

Output: 1

Explanation:



Select the points (0, 0), (0, 1), (0, 2), (1, 2), and (2, 2).

 

Constraints:

1 <= side <= 109
4 <= points.length <= min(4 * side, 15 * 103)
points[i] == [xi, yi]
The input is generated such that:
points[i] lies on the boundary of the square.
All points[i] are unique.
4 <= k <= min(25, points.length)  */

struct Sequence {
  int startX;
  int startY;
  int endX;
  int endY;
  int length;
};
class Solution {
 public:
  int maxDistance(int side, vector<vector<int>>& points, int k) {
    const vector<pair<int, int>> ordered = getOrderedPoints(side, points);
    int l = 0;
    int r = side;

    while (l < r) {
      const int m = (l + r + 1) / 2;
      if (isValidDistance(ordered, k, m))
        l = m;
      else
        r = m - 1;
    }

    return l;
  }

 private:
  // Returns true if we can select `k` points such that the minimum Manhattan
  // distance between any two consecutive chosen points is at least `m`.
  bool isValidDistance(const vector<pair<int, int>>& ordered, int k, int d) {
    deque<Sequence> dq{{ordered[0].first, ordered[0].second, ordered[0].first,
                        ordered[0].second, 1}};
    int maxLength = 1;

    for (int i = 1; i < ordered.size(); ++i) {
      const auto& [x, y] = ordered[i];
      int startX = x;
      int startY = y;
      int length = 1;
      while (!dq.empty() &&
             (abs(x - dq.front().endX) + abs(y - dq.front().endY) >= d)) {
        if (abs(x - dq.front().startX) + abs(y - dq.front().startY) >= d &&
            dq.front().length + 1 >= length) {
          startX = dq.front().startX;
          startY = dq.front().startY;
          length = dq.front().length + 1;
          maxLength = max(maxLength, length);
        }
        dq.pop_front();
      }
      dq.emplace_back(startX, startY, x, y, length);
    }

    return maxLength >= k;
  }

  // Returns the ordered points on the perimeter of a square of side length
  // `side`, starting from left, top, right, and bottom boundaries.
  vector<pair<int, int>> getOrderedPoints(int side,
                                          vector<vector<int>>& points) {
    vector<pair<int, int>> left;
    vector<pair<int, int>> top;
    vector<pair<int, int>> right;
    vector<pair<int, int>> bottom;

    for (const vector<int>& point : points) {
      const int x = point[0];
      const int y = point[1];
      if (x == 0 && y > 0)
        left.emplace_back(x, y);
      else if (x > 0 && y == side)
        top.emplace_back(x, y);
      else if (x == side && y < side)
        right.emplace_back(x, y);
      else
        bottom.emplace_back(x, y);
    }

    ranges::sort(left);
    ranges::sort(top);
    ranges::sort(right, greater<>());
    ranges::sort(bottom, greater<>());
    left.insert(left.end(), top.begin(), top.end());
    left.insert(left.end(), right.begin(), right.end());
    left.insert(left.end(), bottom.begin(), bottom.end());
    return left;
  }
};



