/*
    Author: Nguyen Tan Bao
    Status: Pending
    Idea:
        - If there are i and j that a[i], a[j] >= 10 => YES
        - Because we can generate all number % 11 when we choose x digits i and 10-x digits j
            x * i + (10 - x) * j = y * i + (10 - y) * j (mod 11) (0 <= i <= 10)
        <=> x = y (mod 11)
        - So we can choose n/2-10 digits for positive part and we can choose 10 digits from i and j to make it mod 11 = k
        The negative part will be = k too (as we can find k = (sum(a[i]) % 11) / 2)

        - Otherwise, we can dp on digits that a[i] < 10 and add a[i] >= 10 to it.
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
const int MAXM = 100010;
const int MAXK = 110;
const int MAXQ = 200010;

int a[MAXN];
bool dp[10][365][15];

void printSpecialCase(int n, int num, int vt) {
    FOR(i,0,360) {
        FOR(j,0,10) {
            if (dp[9][i][j]) {
                int need = i - 180 - n % 2;
                if ((num + need) % 2) continue;
                int pos = (num + need) / 2;
                int neg = (num - need) / 2;
                if (pos < 0 || pos > num) continue;
                if (neg < 0 || neg > num) continue;
                int e = (ll) (pos - neg) * vt % 11;
                if (e < 0) e = e + 11;
                if ((j + e) % 11 == 0) {
                    cout << "YES\n";
                    return;
                } 
            }
        }
    }
    cout << "NO\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int t;
    cin >> t;
    FOR(o,1,t) {
        cout << "Case #" << o << ": ";
        FOR(i,1,9) cin >> a[i];
        int cnt = 0;
        FOR(i,1,9) cnt += a[i] >= 10;
        if (cnt >= 2) {
            cout << "YES\n";
            continue;
        }
        int n = 0;
        FOR(i,1,9) n += a[i];
        int vt = -1, num = 0;
        FOR(i,1,9)
            if (a[i] >= 10) {
                vt = i;
                num = a[i];
                a[i] = 0;
                break;
            }
        MS(dp, 0);
        dp[0][180][0] = true;
        FOR(i,1,9)
            FOR(j,0,360)
                FOR(k,0,10)
                    if (dp[i-1][j][k]) {
                        FOR(p,0,a[i]) {
                            int z = a[i] - p;
                            int diff = p - z;
                            int m = ((p % 11 - z % 11 + 11) % 11) * i % 11;
                            if (j + diff >= 0 && j + diff <= 360) dp[i][j+diff][(k + m) % 11] = true;
                        }
                    }
        if (vt != -1) {
            printSpecialCase(n, num, vt);
        }
        else {
            if (dp[9][180 + n % 2][0]) cout << "YES\n";
            else cout << "NO\n";
        }
    }
    return 0;
}
