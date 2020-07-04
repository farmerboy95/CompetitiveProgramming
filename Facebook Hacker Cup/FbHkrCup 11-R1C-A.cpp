/*
    Author: Nguyen Tan Bao
    Statement: https://www.facebook.com/hackercup/problem/172875359424547/
    Status: AC
    Idea:
        - Define res[i] = x if i is x-factorful number.
        - For each query, simply iterate through l to r, increase the count if res[i] = k
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

int nt[10000010], res[10000010];

void sieveBase(int n) {
    FOR(i,2,n) {
        if (nt[i] == 0) {
            nt[i] = i;
            for (ll j = (ll) i * i; j <= n; j += i) nt[j] = i;
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    sieveBase(10000000);
    FOR(i,1,10000000) {
        set<int> s;
        int p = i;
        while (p > 1) {
            s.insert(nt[p]);
            p /= nt[p];
        }
        res[i] = SZ(s);
    }
    int t;
    cin >> t;
    FOR(o,1,t) {
        cout << "Case #" << o << ": ";
        int l, r, k;
        cin >> l >> r >> k;
        int kq = 0;
        FOR(i,l,r) kq += res[i] == k;
        cout << kq << "\n";
    }
    return 0;
}
