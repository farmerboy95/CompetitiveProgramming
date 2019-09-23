/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - n <= 16 so that we can use bitmasks
        - Let dp[mask] is the minimum number of nodes on trie tree if we add strings whose indexes are set bits in mask
        - We can separate mask into 2 groups and dp on each group, get the summation and remove the redundant nodes
        - Use dp top-down, time complexity O(3^n) using mask subset iteration
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
const int MAXN = 20;
const int MAXM = 1000010;
const int MAXK = 110;
const int MAXQ = 200010;

int n, cnt[MAXN][26], tmpCnt[26], common[70000], dp[70000];
string s[MAXN];

int solve(int mask) {
    if (dp[mask] != -1) return dp[mask];
    int cm = common[mask];
    int res = 1000000000;
    // submask iteration
    for (int split = mask & (mask-1); split; split = (split-1) & mask) {
        int submask2 = mask ^ split;
        res = min(res, solve(split) + solve(submask2) - cm);
    }
    return dp[mask] = res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n) cin >> s[i];

    FOR(i,1,n)
        FOR(j,0,SZ(s[i])-1) cnt[i][s[i][j] - 'a']++;

    // get number of same characters in each group of string based on the mask
    FOR(mask,1,(1<<n)-1) {
        FOR(i,0,25) tmpCnt[i] = 1000000000;
        FOR(i,1,n)
            if (mask & (1<<(i-1)))
                FOR(j,0,25) tmpCnt[j] = min(tmpCnt[j], cnt[i][j]);
        FOR(i,0,25) common[mask] += tmpCnt[i];
    }

    // init dp
    FOR(i,1,(1<<n)-1) {
        if (__builtin_popcount(i) == 1) {
            FOR(j,1,n)
                if (i & (1<<(j-1))) dp[i] = SZ(s[j]);
        }
        else dp[i] = -1;
    }

    // add the root nodes to the answer
    cout << solve((1<<n)-1) + 1;
    return 0;
}