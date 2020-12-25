/*
    Author: Nguyen Tan Bao
    Statement: https://lqdoj.edu.vn/problem/forest3
    Status: AC
    Idea: Binary Indexed Tree 2D
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
        t.resize(N+1);
        FOR(i,0,N) t[i].resize(M+1);
        FOR(i,0,N) FOR(j,0,M) t[i][j] = 0;
    }

    void update(int u, int v, ll val) {
        if (u <= 0 || u > N || v <= 0 || v > M) return;
        for (int i = u; i <= N; i = i + (i & (-i)))
            for (int j = v; j <= M; j = j + (j & (-j))) t[i][j] += val;
    }
 
    ll get(int u, int v) {
        ll res = 0;
        for (int i = u; i > 0; i = i - (i & (-i)))
            for (int j = v; j > 0; j = j - (j & (-j))) res += t[i][j];
        return res;
    }

    private:
    vector<vector<ll> > t;
    int N, M;
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m >> q;
    BinaryIndexedTree2D bit(n, m);
    while (q--) {
        int ch, x, y, u, v, c;
        cin >> ch >> x >> y;
        if (ch == 1) {
            cin >> u >> v >> c;
            bit.update(x, y, c);
            bit.update(x, v+1, -c);
            bit.update(u+1, y, -c);
            bit.update(u+1, v+1, c);
        } else {
            cout << bit.get(x, y) + 1 << "\n";
        }
    }
    return 0;
}
