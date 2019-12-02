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
const int MAXN = 110;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

char ch[MAXN][MAXN];
int n, m;

bool check(int u, int v, char c) {
    if (u >= 1 && u <= n && v >= 1 && v <= m) return ch[u][v] == c;
    return false;
}

vector<string> res;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        cin >> n >> m;
        FOR(i,1,n)
            FOR(j,1,m) cin >> ch[i][j];
        string s = "IEHOVA#";
        II st = II(0,0);
        FOR(i,1,n)
            FOR(j,1,m) if (ch[i][j] == '@') st = II(i,j);
        res.clear();
        FOR(i,0,SZ(s)-1) {
            if (check(st.FI-1, st.SE, s[i])) {
                res.emplace_back("forth");
                st.FI--;
            }
            else if (check(st.FI, st.SE-1, s[i])) {
                res.emplace_back("left");
                st.SE--;
            }
            else if (check(st.FI, st.SE+1, s[i])) {
                res.emplace_back("right");
                st.SE++;
            }
        }
        cout << res[0];
        FOR(i,1,SZ(res)-1) cout << " " << res[i];
        cout << "\n";
    }
    return 0;
}
