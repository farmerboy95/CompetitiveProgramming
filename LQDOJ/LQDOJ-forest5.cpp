/*
    Author: Nguyen Tan Bao
    Statement: https://lqdoj.edu.vn/problem/forest5
    Status: AC
    Idea:
        - 2D Binary Indexed Tree
        - As BIT can only update one element per time, we can perform range updates
        via a normal BIT that stores linear functions instead of just a value like in
        https://petr-mitrichev.blogspot.com/2013/05/fenwick-tree-range-updates.html
*/

#include <bits/stdc++.h>
#define FI first
#define SE second
#define EPS 1e-9
#define ALL(a) a.begin(),a.end()
#define SZ(a) int((a).size())
#define MS(s, n) memset(s, n, sizeof(s))
#define FOR(i,a,b) for (int i = (a); i <= (b); i++)
#define FORE(i,a,b) for (int i = (a); i >= (b); i--)
#define FORALL(it, a) for (__typeof((a).begin()) it = (a).begin(); it != (a).end(); it++)
//__builtin_ffs(x) return 1 + index of least significant 1-bit of x
//__builtin_clz(x) return number of leading zeros of x
//__builtin_ctz(x) return number of trailing zeros of x

using namespace std;
using ll = long long;
using ld = double;
typedef pair<int, int> II;
typedef pair<II, int> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;

const ll MODBASE = 1000000007LL;
const int MAXN = 110;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, m, q;

struct BinaryIndexedTree2D {
    public:
    // 1-indexed
    BinaryIndexedTree2D(int n, int m) {
        N = n;
        M = m;
        dataXY.resize(N+1);
        FOR(i,0,N) dataXY[i].resize(M+1);

        dataX.resize(N+1);
        FOR(i,0,N) dataX[i].resize(M+1);

        dataY.resize(N+1);
        FOR(i,0,N) dataY[i].resize(M+1);

        data1.resize(N+1);
        FOR(i,0,N) data1[i].resize(M+1);
    }

    void update(int u, int v, ll dXY, ll dX, ll dY, ll d1) {
        for (int i = u; i <= N; i = i + (i & (-i)))
            for (int j = v; j <= M; j = j + (j & (-j))) {
                dataXY[i][j] += dXY;
                dataX[i][j] += dX;
                dataY[i][j] += dY;
                data1[i][j] += d1;
            }
    }

    void update2(int x, int y, ll val) {
        update(x, y, val, -val * (y-1), -val * (x-1), val * (x-1) * (y-1));
    }

    void addRange(int x, int y, int u, int v, ll val) {
        update2(x, y, val);
        update2(x, v+1, -val);
        update2(u+1, y, -val);
        update2(u+1, v+1, val);
    }
 
    ll get(int u, int v) {
        ll dXY = 0, dX = 0, dY = 0, d1 = 0;
        for (int i = u; i > 0; i = i - (i & (-i)))
            for (int j = v; j > 0; j = j - (j & (-j))) {
                dXY += dataXY[i][j];
                dX += dataX[i][j];
                dY += dataY[i][j];
                d1 += data1[i][j];
            }
        return dXY * u * v + dX * u + dY * v + d1;
    }

    ll getRange(int x, int y, int u, int v) {
        return get(u, v) - get(x-1, v) - get(u, y-1) + get(x-1, y-1);
    }

    private:
    vector<vector<ll> > dataXY, dataX, dataY, data1;
    int N, M;
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m >> q;
    BinaryIndexedTree2D bit(n, m);
    bit.addRange(1,1,n,m,1);
    while (q--) {
        int ch, x, y, u, v, c;
        cin >> ch >> x >> y >> u >> v;
        if (ch == 1) {
            cin >> c;
            bit.addRange(x, y, u, v, c);
        } else {
            cout << bit.getRange(x, y, u, v) << "\n";
        }
    }
    return 0;
}
