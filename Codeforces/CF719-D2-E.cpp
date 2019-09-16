/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let f[i] is the ith fibonacci number
        - Quickly find out that f[n+k] = f[k] * f[n+1] + f[k-1] * f[n] and f[n+k+1] = f[k+1] * f[n+1] + f[k] * f[n]
        - Build a segment tree that save sum(f[n]) and sum(f[n+1])
        - For each query, we can easily calculate new state of tree node based on the above formulas
        - The hard thing is how to get f[k] efficiently
            1. Use matrix exponentation
            2. Save matrix to lazy node to avoid getting f[k] multiple times, simply multiply 2 matrices to go down to child node
            2. Use half of a matrix to calculate
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
#define WHATIS(x) cout << #x << " is " << x << endl;
#define ERROR(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
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

void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
    cout << *it << " = " << a << endl;
    err(++it, args...);
}

const ll MODBASE = 1000000007LL;
const int MAXN = 100010;
const int MAXM = 200010;
const int MAXK = 110;
const int MAXQ = 200010;

int n, a[MAXN];

ll sub(ll x, ll y) {
    return (x - y + MODBASE) % MODBASE;
}

ll add(ll x, ll y) {
    return (x + y) % MODBASE;
}

ll mul(ll x, ll y) {
    return (x * y) % MODBASE;
}

// use half of a matrix
II mul(II &A, II B) {
    int tempFI = A.FI, tempSE = A.SE;
    A.FI = add(mul(tempFI, B.FI), mul(tempSE, B.SE));
    A.SE = add(mul(tempFI, B.SE), mul(tempSE, sub(B.FI, B.SE)));
}

int mu(ll n) {
    II B = II(1, 0), A = II(1, 1);
    while (n) {
        if (n & 1LL) mul(B, A);
        mul(A, A);
        n >>= 1LL;
    }
    return B.SE;
}

map<ll, int> ma;

int fibo(ll n) {
    if (n <= 0) return 0;
    if (n <= 2) return 1;
    if (ma.count(n)) return ma[n];
    int res = mu(n);
    return ma[n] = res;
}

II fiboII(ll n) {
    return II(fibo(n+1), fibo(n));
}

struct TreeNode {
    int sum, sumPlus1;
    TreeNode(int sum = 0, int sumPlus1 = 0) : sum(sum), sumPlus1(sumPlus1) {}
} t[MAXN * 8];

II lazy[MAXN * 8];

void build(int k, int l, int r) {
    if (l > r) return;
    if (l == r) {
        t[k].sum = fibo(a[l]);
        t[k].sumPlus1 = fibo(a[l]+1);
        return;
    }
    int m = (l + r) >> 1;
    build(k*2, l, m);
    build(k*2+1, m+1, r);
    t[k].sum = add(t[k*2].sum, t[k*2+1].sum);
    t[k].sumPlus1 = add(t[k*2].sumPlus1, t[k*2+1].sumPlus1);
}

void lazyUpdate(int k, int l, int r) {
    if (l > r) return;
    if (lazy[k] == II(1, 0)) return;
    int oldSum = t[k].sum;
    int oldSumPlus1 = t[k].sumPlus1;
    int fiboVal = lazy[k].SE;
    int fiboValPlus1 = lazy[k].FI;
    int fiboValMinus1 = sub(lazy[k].FI, lazy[k].SE);
    // calculate new values of node tree
    t[k].sum = add(mul(fiboVal, oldSumPlus1), mul(fiboValMinus1, oldSum));
    t[k].sumPlus1 = add(mul(fiboValPlus1, oldSumPlus1), mul(fiboVal, oldSum));
    if (l < r) {
        // going down by multiplying 2 matrices
        mul(lazy[k*2], lazy[k]);
        mul(lazy[k*2+1], lazy[k]);
    }
    lazy[k] = II(1, 0);
}

void update(int k, int l, int r, int u, int v, ll val) {
    lazyUpdate(k,l,r);
    if (l > r || r < u || v < l) return;
    if (u <= l && r <= v) {
        lazy[k] = fiboII(val);
        lazyUpdate(k,l,r);
        return;
    }
    int m = (l + r) >> 1;
    update(k*2, l, m, u, v, val);
    update(k*2+1, m+1, r, u, v, val);
    t[k].sum = add(t[k*2].sum, t[k*2+1].sum);
    t[k].sumPlus1 = add(t[k*2].sumPlus1, t[k*2+1].sumPlus1);
}

int get(int k, int l, int r, int u, int v) {
    lazyUpdate(k,l,r);
    if (l > r || r < u || v < l) return 0;
    if (u <= l && r <= v) return t[k].sum;
    int m = (l + r) >> 1;
    return add(get(k*2, l, m, u, v), get(k*2+1, m+1, r, u, v));
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    FOR(i,1,800000) lazy[i] = II(1,0);
    int m;
    cin >> n >> m;
    FOR(i,1,n) cin >> a[i];
    build(1,1,n);
    while (m--) {
        int ch, l, r, x;
        cin >> ch;
        if (ch == 1) {
            cin >> l >> r >> x;
            update(1,1,n,l,r,x);
        }
        else {
            cin >> l >> r;
            cout << get(1,1,n,l,r) << "\n";
        }
    }
    return 0;
}
