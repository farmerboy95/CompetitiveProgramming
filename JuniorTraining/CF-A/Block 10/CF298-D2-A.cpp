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
typedef pair<int, int> II;
typedef pair<int, II> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;
 
const ll MODBASE = 1000000007LL;
const int MAXN = 210;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

string s;
int n;
vector<int> a, b;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    cin >> s;
    s = " " + s;
    FOR(i,1,n)
        if (s[i] == 'R') a.emplace_back(i);
        else if (s[i] == 'L') b.emplace_back(i);
    if (SZ(a) == 0) cout << b[SZ(b)-1] << ' ' << b[0]-1;
    else if (SZ(b) == 0) cout << a[0] << ' ' << a[SZ(a)-1]+1;
    else cout << a[0] << ' ' << a[SZ(a)-1];
    return 0;
}
