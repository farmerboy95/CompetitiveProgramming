/*
    Author: Nguyen Tan Bao
    Status: AC after reading editorial
    Idea: https://codeforces.com/contest/1209/submission/60541156
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
#define WHATIS(x) cout << #x << " is " << x << endl;
#define ERROR(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
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

void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
    cout << *it << " = " << a << endl;
    err(++it, args...);
}

const ll MODBASE = 1000000007LL;
const int MAXN = 13;
const int MAXM = 2010;
const int MAXK = 110;
const int MAXQ = 200010;

int t, n, m, a[MAXN][MAXM], dp[(1<<MAXN)], tmp[(1<<MAXN)];
bool used[MAXM];
vector<II> A;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> t;
    FOR(o,1,t) {
        cin >> n >> m;
        FOR(i,0,n-1) FOR(j,0,m-1) cin >> a[i][j];

        FOR(i,0,m-1) used[i] = false;
        A.clear();
        FOR(i,0,n-1)
            FOR(j,0,m-1) A.emplace_back(II(a[i][j], j));
        sort(ALL(A));
        reverse(ALL(A));

        // only consider n columns, yes, n columns only
        FOR(i,0,SZ(A)-1) {
            int j = A[i].SE;
            if (!used[j]) {
                used[j] = true;
                cnt++;
                if (cnt == n) break;
            }
        }
        
        // dp[mask] is maximum sum of rows whose indexes are set bits in mask, non-set bits are not considered
        FOR(i,0,(1<<n)-1) dp[i] = -1;
        dp[0] = 0;

        FOR(j,0,m-1) {
            // ignore other columns
            if (!used[j]) continue;

            // tmp[mask] = sum of elements if we take elements whose indexes are set bits in mask
            FOR(shift,0,n-1) {
                FOR(mask,0,(1<<n)-1) {
                    if (shift == 0) tmp[mask] = -1;
                    int sum = 0;
                    FOR(i,0,n-1)
                        if (mask & (1<<i)) sum += a[(i+shift) % n][j];
                    tmp[mask] = max(tmp[mask], sum);
                }
            }

            // for each old dp[mask], combine it with tmp[split] (mask & split == 0) (O(3^n) here)
            FORE(mask,(1<<n)-1,0) {
                int other = (1<<n)-1 - mask;
                if (dp[mask] != -1) {
                    dp[mask | other] = max(dp[mask | other], dp[mask] + tmp[other]);
                    for (int split = other & (other-1); split; split = (split-1) & other) {
                        dp[mask | split] = max(dp[mask | split], dp[mask] + tmp[split]);
                    }
                }
            }
        }

        cout << dp[(1<<n)-1] << "\n";
    }
    return 0;
}
