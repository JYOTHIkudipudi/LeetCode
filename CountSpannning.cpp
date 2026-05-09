 class Solution {
public:

    long long determinant(vector<vector<long double>>& mat, int n) {
        long double det = 1;

        for (int i = 0; i < n; i++) {

            int pivot = i;

            for (int j = i; j < n; j++) {
                if (fabsl(mat[j][i]) > fabsl(mat[pivot][i]))
                    pivot = j;
            }

            if (fabsl(mat[pivot][i]) < 1e-9)
                return 0;

            if (pivot != i) {
                swap(mat[pivot], mat[i]);
                det *= -1;
            }

            det *= mat[i][i];

            for (int j = i + 1; j < n; j++) {

                long double factor = mat[j][i] / mat[i][i];

                for (int k = i; k < n; k++) {
                    mat[j][k] -= factor * mat[i][k];
                }
            }
        }

        return llround(det);
    }

    long long countSpanningTrees(int n, vector<vector<int>>& edges) {

        int m = edges.size();

        // Already a tree
        if (m == n - 1)
            return 1;

        vector<vector<long double>> lap(n, vector<long double>(n, 0));

        for (auto &e : edges) {

            int u = e[0];
            int v = e[1];

            lap[u][u]++;
            lap[v][v]++;

            lap[u][v]--;
            lap[v][u]--;
        }

        // Build cofactor matrix
        vector<vector<long double>> cof(n - 1,
                                        vector<long double>(n - 1));

        for (int i = 1; i < n; i++) {
            for (int j = 1; j < n; j++) {
                cof[i - 1][j - 1] = lap[i][j];
            }
        }

        return determinant(cof, n - 1);
    }
}; 
