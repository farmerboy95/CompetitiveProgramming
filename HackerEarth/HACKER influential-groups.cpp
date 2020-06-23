/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Sort input array, let's consider value w, and position of w in input array is k (1-indexed).
        - Good groups with value w is the number of groups that contain l value on the left of k
        and r value on the right of k that l >= r.
        - So the naive solution here is to pick l (out of k-1 values), then consider r (from 0 to l)
        (out of n-k values). Result is number of ways to pick l and r. (1)
        - But it would take you O(n^3). If you try to find result of all values in sample input and
        search for that result array in OEIS, that list would be equal to 
                Result = sum(C(n-1, i)) (i from 0 to k-1)
        - Why? Firstly, let x = k-1, y = n-k => x+y = n-1
        (1) = C(x,x) * (C(y,x) + C(y,x-1) + ... + C(y,0)) 
            + C(x,x-1) * (C(y,x-1)+ ... + C(y,0)) 
            + ... 
            + C(x,0) * C(y,0)
        this can be reduced to 
        (1) = C(x,x) * C(y,x) + C(x,x-1) * C(y,x-1) + ... + C(x,0) * C(y,0)
            + C(x,x) * C(y,x-1) + C(x,x-1) * C(y,x-2) + ... + C(x,1) * C(y,0)
            + ...
            + C(x,x) * C(y,0)
            = (summation i=0 to x) (summation j = 0 to x) { C(x,x-j) * C(y,i-j) } 
            = sumi sumj { C(x,j) * C(n-1-x,i-j) } ( as C(x, x-j) = C(x, j))
            = sumi C(n-1,i) (Vandermonde's Identity for each j)
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
const int MAXN = 100010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

ll binPowMod(ll a, ll b) {
    a %= MODBASE;
    ll res = 1;
    while (b > 0) {
        if (b & 1LL) res = res * a % MODBASE;
        a = a * a % MODBASE;
        b >>= 1LL;
    }
    return res;
}

ll add(ll a, ll b) {
    return (a+b) % MODBASE;
}

ll mul(ll a, ll b) {
    return (a*b) % MODBASE;
}

ll sub(ll a, ll b) {
    return (a-b+MODBASE) % MODBASE;
}

ll f[MAXN], inv[MAXN], c[MAXN];

ll C(int N, int K) {
    if (K > N || K < 0) return 0;
    return mul(f[N], mul(inv[N-K], inv[K]));
}

void init() {
    f[0] = 1;
    inv[0] = binPowMod(f[0], MODBASE-2);
    FOR(i,1,100000) {
        f[i] = mul(f[i-1], i);
        inv[i] = binPowMod(f[i], MODBASE-2);
    }
}

int n, m, a[MAXN];
map<int, int> ma;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m;
    FOR(i,1,n) cin >> a[i];
    sort(a+1, a+n+1);
    init();
    ll sum = 0;
    FOR(i,1,n) {
        sum = add(sum, C(n-1, i-1));
        ma[a[i]] = int(sum);
    }
    FOR(i,1,m) {
        int x;
        cin >> x;
        cout << ma[x] << "\n";
    }
    return 0;
}
