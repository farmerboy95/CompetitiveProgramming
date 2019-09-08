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
const int MAXN = 2010;
const int MAXM = 200010;
const int MAXK = 110;
const int MAXQ = 200010;
 
int n, K, f[MAXN][MAXN], preF[MAXN][MAXN], cnt[26], numOfFirstChar[26];
vector<string> s;
ll group[MAXN][MAXN], g[26][MAXN], dp[30][MAXN];
 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> K;
    FOR(i,0,n-1) {
        string t;
        cin >> t;
        s.emplace_back(t);
    }
    sort(ALL(s));
    FOR(i,0,n-1) {
        int l = i, r = n-1;
        FOR(j,0,SZ(s[i])-1) {
            char ch = s[i][j];
            int dau = l, cuoi = r, mid;
            while (dau <= cuoi) {
                mid = (dau + cuoi) >> 1;
                if (j >= SZ(s[mid])) {
                    cuoi = mid-1;
                    continue;
                }
                if (s[mid][j] > s[i][j]) cuoi = mid-1;
                else dau = mid+1;
            }
            // cout << i << ' ' << j << ' ' << cuoi << endl;
            // from i + 1 to cuoi
            if (i < cuoi && cuoi < n) {
                f[i][i+1]++;
                f[i][cuoi+1]--;
            }
            else break;
        }
        FOR(j,i+1,n-1) f[i][j] += f[i][j-1]; 
    }
 
    // FOR(i,0,n-1) cout << s[i] << endl;
 
    // FOR(i,0,n-1) {
    //     FOR(j,0,n-1) cout << f[i][j] << ' ';
    //     cout << endl;
    // }
 
    FOR(j,0,n-1) {
        FOR(i,0,n-1) {
            if (i == 0) preF[i][j] = f[i][j];
            else preF[i][j] = preF[i-1][j] + f[i][j];
        }
    }
 
    FOR(i,0,n-1)
        FOR(j,i+1,n-1)
            if (j == i + 1) group[i][j] = f[i][j];
            else {
                // group[i][j] = group[i][j-1] + f[k][j]; k from i to j - 1
                group[i][j] = group[i][j-1] + preF[j-1][j];
                if (i > 0) group[i][j] = group[i][j] - preF[i-1][j];
            }
    
    // FOR(i,0,n-1) {
    //     FOR(j,0,n-1) cout << group[i][j] << ' ';
    //     cout << endl;
    // }
 
    FOR(i,0,n-1) cnt[s[i][0]-'a']++;
 
    int now = 0;
    FOR(i,0,25) {
        int nex = now + cnt[i];
        int num = nex - now;
        numOfFirstChar[i] = num;
        FOR(j,1,num) {
            g[i][j] = 0;
            FOR(k,now,nex-1) {
                if (k + j - 1 >= nex) break;
                int l = k, r = k + j - 1;
                g[i][j] = max(g[i][j], group[l][r]);
            }
        }
        now = nex;
    }
 
    // FOR(i,0,25) cout << numOfFirstChar[i] << ' ';
    // cout << endl;
 
    FOR(i,0,26)
        FOR(j,0,K) dp[i][j] = -1e18;
    dp[0][0] = 0;
    FOR(i,0,25)
        FOR(j,0,K) {
            FOR(k,0,numOfFirstChar[i]) {
                if (j + k <= K) dp[i+1][j+k] = max(dp[i+1][j+k], dp[i][j] + g[i][k]);
            }
        }
    ll res = 0;
    FOR(j,0,K) res = max(res, dp[26][j]);
    cout << res;
    return 0;
}