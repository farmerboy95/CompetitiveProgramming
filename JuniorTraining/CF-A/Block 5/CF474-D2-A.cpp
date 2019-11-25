/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: Do as problem requirement
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
const int MAXN = 100010;
const int MAXM = 30010;
const int MAXK = 16;
const int MAXQ = 200010;

string s[3], t;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    s[0] = "qwertyuiop";
    s[1] = "asdfghjkl;";
    s[2] = "zxcvbnm,./";
    char ch;
    cin >> ch;
    cin >> t;
    FOR(i,0,SZ(t)-1) {
        FOR(j,0,2)
            FOR(k,0,SZ(s[j])-1)
                if (s[j][k] == t[i]) {
                    if (ch == 'R') cout << s[j][k-1];
                    else cout << s[j][k+1];
                }
    }
    return 0;
}
