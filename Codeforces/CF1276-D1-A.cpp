/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - We group same adjacent letters together and its ocurrence
        - Iterate the new array, if we see "twone" then we would have to check if there is only one "o"
        => remove that "o", otherwise, remove "w" and "n"
        - If we see "two" => remove "w"
        - If we see "one" => remove "n"
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
vector<II> a;
vector<int> add, res;
 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        cin >> s;
        a.clear();
        add.clear();
        int cnt = 1;
        FOR(i,1,SZ(s)-1) {
            if (s[i] != s[i-1]) {
                a.emplace_back(II(s[i-1], cnt));
                add.emplace_back(0);
                cnt = 1;
            }
            else cnt++;
        }
        a.emplace_back(II(s[SZ(s)-1], cnt));
        add.emplace_back(0);
        FOR(i,0,SZ(a)-1) {
            if (a[i].FI == 't') {
                if (i+1 < SZ(a) && a[i+1].FI == 'w' && a[i+1].SE == 1)
                    if (i+2 < SZ(a) && a[i+2].FI == 'o') {
 
                        if (i+3 < SZ(a) && a[i+3].FI == 'n' && a[i+3].SE == 1) {
                            if (i+4 < SZ(a) && a[i+4].FI == 'e') {
                                if (a[i+2].SE > 2) add[i+1] = add[i+3] = 1;
                                else add[i+2] = 1;
                                i = i + 4;
                                continue;
                            }
                        }
 
                        add[i+1] = 1;
                        i = i + 2;
                    }
            }
 
            if (a[i].FI == 'o') {
                if (i+1 < SZ(a) && a[i+1].FI == 'n' && a[i+1].SE == 1) {
                    if (i+2 < SZ(a) && a[i+2].FI == 'e') {
                        add[i+1] = 1;
                        i = i + 2;
                    }
                }
            }
        }
 
        res.clear();
        int p = 0;
        FOR(i,0,SZ(a)-1) {
            int w = a[i].SE;
            if (add[i])
                FOR(j,1,w) res.emplace_back(p + j);
            p += w;
        }
 
        cout << SZ(res) << "\n";
        FOR(i,0,SZ(res)-1) cout << res[i] << ' ';
        cout << "\n";
    }
    return 0;
}