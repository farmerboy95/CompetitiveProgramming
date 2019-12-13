/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: Don't consider digits which are larger than k
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

int f[20];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    int res = 0;
    FOR(i,1,n) {
        string s;
        cin >> s;
        bool co = true;
        FOR(j,0,9) f[j] = 0;
        FOR(j,0,SZ(s)-1) f[s[j]-'0']++;
        FOR(j,0,k)
            if (f[j] == 0) co = false;
        res += co;
    }
    cout << res;
    return 0;
}
