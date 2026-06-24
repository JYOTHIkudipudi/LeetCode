class Solution {
public:
    static const long long MOD = 1000000007LL;

    using Matrix = vector<vector<long long>>;

    Matrix multiply(const Matrix &A, const Matrix &B) {
        int n = A.size();
        Matrix C(n, vector<long long>(n, 0));

        for (int i = 0; i < n; i++) {
            for (int k = 0; k < n; k++) {
                if (A[i][k] == 0) continue;
                long long aik = A[i][k];
                for (int j = 0; j < n; j++) {
                    if (B[k][j] == 0) continue;
                    C[i][j] = (C[i][j] + aik * B[k][j]) % MOD;
                }
            }
        }
        return C;
    }

    Matrix power(Matrix base, long long exp) {
        int n = base.size();
        Matrix res(n, vector<long long>(n, 0));

        for (int i = 0; i < n; i++) res[i][i] = 1;

        while (exp) {
            if (exp & 1) res = multiply(res, base);
            base = multiply(base, base);
            exp >>= 1;
        }
        return res;
    }

    vector<long long> matVec(const Matrix &A, const vector<long long> &v) {
        int n = A.size();
        vector<long long> res(n, 0);

        for (int i = 0; i < n; i++) {
            long long cur = 0;
            for (int j = 0; j < n; j++) {
                cur = (cur + A[i][j] * v[j]) % MOD;
            }
            res[i] = cur;
        }
        return res;
    }

    int zigZagArrays(int n, int l, int r) {
        int m = r - l + 1;

        Matrix A(m, vector<long long>(m, 0));
        Matrix B(m, vector<long long>(m, 0));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < m; j++) {
                if (j < i) A[i][j] = 1; // next move is up
                if (j > i) B[i][j] = 1; // next move is down
            }
        }

        vector<long long> U2(m), D2(m);
        for (int i = 0; i < m; i++) {
            U2[i] = i;           // count of smaller previous values
            D2[i] = m - 1 - i;   // count of larger previous values
        }

        long long k = n - 2;

        Matrix AB = multiply(A, B);
        Matrix BA = multiply(B, A);

        vector<long long> U, D;

        if (k % 2 == 0) {
            long long p = k / 2;

            Matrix P = power(AB, p);
            Matrix Q = power(BA, p);

            U = matVec(P, U2);
            D = matVec(Q, D2);
        } else {
            long long p = k / 2;

            Matrix P = power(AB, p);
            Matrix Q = power(BA, p);

            vector<long long> tempU = matVec(P, U2);
            vector<long long> tempD = matVec(Q, D2);

            D = matVec(B, tempU);
            U = matVec(A, tempD);
        }

        long long ans = 0;
        for (long long x : U) ans = (ans + x) % MOD;
        for (long long x : D) ans = (ans + x) % MOD;

        return (int)ans;
    }
};
