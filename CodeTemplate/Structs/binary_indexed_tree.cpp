/*
    Author: Nguyen Tan Bao
    Statement: https://judge.yosupo.jp/problem/point_add_range_sum
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

struct BinaryIndexedTree {
    public:
    // 1-indexed
    BinaryIndexedTree(int n) {
        N = n;
        t.resize(N+1);
        FOR(i,0,N) t[i] = 0;
    }

    void update(int u, int val) {
        while (u <= N) {
            t[u] += val;
            u = u + (u & (-u));
        }
    }
 
    ll get(int u) {
        ll res = 0;
        while (u) {
            res += t[u];
            u = u - (u & (-u));
        }
        return res;
    }

    private:
    vector<ll> t;
    int N;
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    BinaryIndexedTree bit(n);
    FOR(i,0,n-1) {
        int x;
        cin >> x;
        bit.update(i+1, x);
    }
    while (q--) {
        int ch, u, v;
        cin >> ch >> u >> v;
        if (ch == 0) {
            bit.update(u+1, v);
        } else {
            ll r = bit.get(v);
            ll l = bit.get(u);
            cout << r-l << "\n";
        }
    }
    return 0;
}
