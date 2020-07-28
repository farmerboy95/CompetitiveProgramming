/*
    Author: Nguyen Tan Bao
    Statement: https://www.facebook.com/codingcompetitions/hacker-cup/2020/qualification-round/problems/A
    Status: AC
    Idea:
        - For each countries, initially we set the possibilities to other countries as N, except itself.
        - We iterate forward and backward, then check if we can move to the next or previous country,
        if not, we stop immediately, otherwise, we continue to move as we just need to check the possibility
        to go to the next country from the current country.
        - Complexity O(N^2)
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

int t, n;
string I, O;
bool res[MAXN][MAXN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> t;
    FOR(o,1,t) {
        cout << "Case #" << o << ": ";
        cin >> n;
        cin >> I;
        cin >> O;
        I = " " + I;
        O = " " + O;
        MS(res, 0);

        FOR(i,1,n) {
            res[i][i] = 1;
            FOR(j,i+1,n) {
                if (O[j-1] == 'Y' && I[j] == 'Y') res[i][j] = 1;
                else break;
            }
            FORE(j,i-1,1) {
                if (O[j+1] == 'Y' && I[j] == 'Y') res[i][j] = 1;
                else break;
            }
        }

        cout << "\n";
        FOR(i,1,n) {
            FOR(j,1,n) cout << (res[i][j] ? "Y" : "N");
            cout << "\n";
        }
    }
    return 0;
}
