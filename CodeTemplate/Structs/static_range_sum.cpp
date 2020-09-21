/*
    Author: Nguyen Tan Bao
    Statement: https://judge.yosupo.jp/problem/static_range_sum
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

struct StaticRangeSum {
  public:
    // inits an original array and prefix sum array with size n
    StaticRangeSum() : _n(0) {}
    StaticRangeSum(int n) : _n(n), elements(n, 0), prefix_sums(n, 0) {}

    // a[u] = val
    void assign(int u, ll val) {
        assert(0 <= u && u < _n);
        elements[u] = val;
    }

    // calculates prefix sum array
    void calculate() {
        if (_n == 0) return;
        prefix_sums[0] = elements[0];
        FOR(i,1,_n-1) prefix_sums[i] = prefix_sums[i-1] + elements[i];
    }

    // gets sum a[i] with i is in [l, r)
    ll getSum(int l, int r) {
        assert(0 <= l && l < _n);
        assert(0 < r && r <= _n);
        assert(l < r);
        if (l == 0) return prefix_sums[r-1];
        return prefix_sums[r-1] - prefix_sums[l-1];
    }

  private:
    int _n;
    vector<ll> elements, prefix_sums;
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    StaticRangeSum srs(n);
    FOR(i,0,n-1) {
        int x;
        cin >> x;
        srs.assign(i, x);
    }
    srs.calculate();
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << srs.getSum(l, r) << "\n";
    }
    return 0;
}
