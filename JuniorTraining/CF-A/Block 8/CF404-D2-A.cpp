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
char ch[MAXN][MAXN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n) FOR(j,1,n) cin >> ch[i][j];
    char x = ch[1][1];
    FOR(i,1,n)
        if (ch[i][i] != x) {
            cout << "NO";
            return 0;
        }
        else if (ch[i][n-i+1] != x) {
            cout << "NO";
            return 0;
        }
    if (ch[1][2] == x) {
        cout << "NO";
        return 0;
    }
    x = ch[1][2];
    FOR(i,1,n)
        FOR(j,1,n)
            if (i == j) continue;
            else if (j == n - i + 1) continue;
            else if (ch[i][j] != x) {
                cout << "NO";
                return 0;
            }
    cout << "YES";
    return 0;
}
