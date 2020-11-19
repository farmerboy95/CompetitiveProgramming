/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: https://atcoder.jp/contests/agc049/editorial/331
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

int n, visited[MAXN], S[MAXN];
vector<int> a[MAXN];

void dfs(int u) {
    visited[u] = 1;
    for (int v : a[u])
        if (!visited[v]) dfs(v);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n) {
        string s;
        cin >> s;
        s = " " + s;
        FOR(j,1,SZ(s)-1)
            if (s[j] == '1') a[j].push_back(i);
    }

    FOR(i,1,n) {
        FOR(j,1,n) visited[j] = 0;
        dfs(i);
        FOR(j,1,n)
            if (visited[j]) S[i]++;
    }

    ld res = 0;
    FOR(i,1,n) res += 1.0 / S[i];
    cout << fixed << setprecision(9) << res;
    return 0;
}
