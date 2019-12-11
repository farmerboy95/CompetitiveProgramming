/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
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
typedef pair<ll, ll> II;
typedef pair<int, II> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;
 
const ll MODBASE = 1000000007LL;
const int MAXN = 310;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    int res = 0;
    FOR(i,1,n) {
        string s;
        cin >> s;
        if (s[0] == 'T') res += 4;
        if (s[0] == 'C') res += 6;
        if (s[0] == 'O') res += 8;
        if (s[0] == 'D') res += 12;
        if (s[0] == 'I') res += 20;
    }
    cout << res;
    return 0;
}
