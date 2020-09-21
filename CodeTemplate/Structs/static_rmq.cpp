/*
    Author: Nguyen Tan Bao
    Statement: https://judge.yosupo.jp/problem/staticrmq
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

template <typename T, T (*op)(T, T)>
struct SparseTable {
  public:
    // creates a sparse table size n with default value
    SparseTable(int n, T def) {
        _n = n;
        elements.resize(n);
        fill(ALL(elements), def);

        _b = 0;
        while ((1 << _b) <= n) _b++;
        sparse_table.resize(n, vector<T>(_b));
    }

    // calculate sparse table
    void proceed() {
        FOR(i,0,_n-1) sparse_table[i][0] = elements[i];
        FOR(j,1,_b-1)
            for (int i = 0; i + (1 << j) <= _n; i++) 
                sparse_table[i][j] = op(sparse_table[i][j-1], sparse_table[i + (1 << (j-1))][j-1]);
    }

    // set a[u] = val, not changing sparse table
    void assign(int u, T val) {
        assert(0 <= u && u < _n);
        elements[u] = val;
    }

    // get op(a[i]) with i is in [l, r)
    T query(int l, int r) {
        assert(0 <= l && l < _n);
        assert(0 < r && r <= _n);
        assert(l < r);
        int k = log2(r-l);
        return op(sparse_table[l][k], sparse_table[r - (1 << k)][k]);
    }

  private:
    vector<vector<T>> sparse_table;
    vector<T> elements;
    int _n, _b;
};

int f(const int a, const int b) { return min(a, b); }

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    SparseTable<int, f> rmq(n, 0);
    FOR(i,0,n-1) {
        int x;
        cin >> x;
        rmq.assign(i, x);
    }
    rmq.proceed();
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << rmq.query(l, r) << "\n";
    }
    return 0;
}
