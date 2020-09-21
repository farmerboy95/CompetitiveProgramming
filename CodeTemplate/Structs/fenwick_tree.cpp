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

template <class T>
struct FenwickTree {
  public:
    FenwickTree() : _n(0) {}
    FenwickTree(int n) : _n(n), data(n, 0) {}

    void add(int p, T x) {
        assert(0 <= p && p < _n);
        // use 1-based indexing when iterating, but storing in 0-based indexing array
        p++;
        while (p <= _n) {
            data[p - 1] += x;
            p += p & -p;
        }
    }

    T sum(int l, int r) {
        assert(0 <= l && l <= r && r <= _n);
        return sum(r) - sum(l);
    }

  private:
    int _n;
    vector<T> data;

    // sum from 0 -> r-1
    T sum(int r) {
        T s = 0;
        while (r > 0) {
            s += data[r - 1];
            r -= r & -r;
        }
        return s;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    FenwickTree<ll> ft(n);
    FOR(i,0,n-1) {
        int x;
        cin >> x;
        ft.add(i, x);
    }
    while (q--) {
        int ch, u, v;
        cin >> ch >> u >> v;
        if (ch == 0) {
            ft.add(u, v);
        } else {
            cout << ft.sum(u, v) << "\n";
        }
    }
    return 0;
}
