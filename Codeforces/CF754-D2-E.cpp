/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: 
        - Bitset: https://codeforces.com/blog/entry/49637 (below is the implementation)
        - FFT: https://codeforces.com/blog/entry/49613?#comment-335977 (from the problem of matching
        strings with wildcard, a basic problem of FFT but we use 2d this time)
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
const int MAXN = 410;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, m, r, c;
bitset<MAXN> G[26][MAXN];
bitset<MAXN> res[MAXN];

bitset<MAXN> shift(const bitset<MAXN> &b, int sh) {
    return (b << sh) | (b >> (m - sh));
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m;
    FOR(i,0,n-1) {
        string s;
        cin >> s;
        FOR(j,0,m-1) G[s[j] - 'a'][i][j] = 1;
    }

    FOR(i,0,n-1) FOR(j,0,m-1) res[i][j] = 1;

    cin >> r >> c;
    FOR(i,0,r-1) {
        string s;
        cin >> s;
        FOR(j,0,c-1) {
            if (s[j] == '?') continue;
            int ch = s[j] - 'a';
            int shiftUp = (-i % n + n) % n, shiftLeft = (-j % m + m) % m;
            FOR(x,0,n-1) {
                int nx = (x + shiftUp) % n;
                res[nx] &= shift(G[ch][x], shiftLeft);
            }
        }
    }
    FOR(i,0,n-1) {
        FOR(j,0,m-1)
            if (res[i][j]) cout << 1;
            else cout << 0;
        cout << "\n";
    }
    return 0;
}
