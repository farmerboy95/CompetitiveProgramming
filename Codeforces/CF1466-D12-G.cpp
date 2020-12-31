/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - https://codeforces.com/blog/entry/86126
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
const int MAXN = 100010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

string s0, t, st;
int n, q, x, b[3000010], pref[1000010], suf[1000010];
ll mu[MAXN], prefixSum[26][MAXN];

ll MOD = MODBASE;

void kmpPreprocess(string &t) {
    b[0] = 0;
    FOR(i,1,SZ(t)-1) {
        int k = b[i-1];
        while (k > 0 && t[k] != t[i]) k = b[k-1];
        if (t[k] == t[i]) b[i] = k+1;
        else k = b[i] = 0;
    }
}

ll solve() {
    // find the first k that len(s[k]) >= len(w)
    int kNow = 0;
    string q = s0;
    if (SZ(q) < SZ(st)) {
        FOR(i,0,SZ(t)-1) {
            q = q + t[i] + q;
            kNow++;
            if (SZ(q) >= SZ(st)) break;
        }
    }

    // if the longest s[k] is still < len(w) => 0
    if (SZ(q) < SZ(st)) return 0;

    // if kNow > songId => 0
    if (kNow > x) return 0;

    ll res = 0;

    // check if some prefix of w can be some suffix of s[k]
    string sPref = st + "#" + q;
    kmpPreprocess(sPref);

    // get the earlier part in the formula
    int f = 0;
    FOR(i,0,SZ(sPref)-1) f += (b[i] == SZ(st));
    res = f * mu[x - kNow] % MOD;

    // extract prefix of w
    FOR(i,0,SZ(st)-1) pref[i] = false;
    int ptr = SZ(sPref)-1;
    while (ptr >= 0) {
        int g = b[ptr];
        if (g > 0) pref[g-1] = true;
        ptr = g - 1;
    }

    // check if some suffix of w can be some prefix of s[k]
    string sSuf = q + "#" + st;
    kmpPreprocess(sSuf);
    // extract suffix of w
    FOR(i,0,SZ(st)-1) suf[i] = false;
    ptr = SZ(sSuf)-1;
    while (ptr >= 0) {
        int g = b[ptr];
        if (g > 0) suf[g-1] = true;
        ptr = g - 1;
    }

    // only proceed to find the later part in the formula if kNow < x
    if (kNow < x) {
        int newKNow = kNow + 1;
        FOR(i,0,SZ(st)-1) {
            bool pr = true, su = true;
            if (i-1 >= 0) pr = pref[i-1];
            if (SZ(st) - (i+1) - 1 >= 0) su = suf[SZ(st) - (i+1) - 1];
            // only proceed if we can form prefix of w as suffix of s[k] and suffix of w as prefix of s[k]
            // only one character left (ch)
            if (!pr || !su) continue;

            int ch = st[i] - 'a';
            // use prefix sum to get the result
            ll z = (prefixSum[ch][x] - prefixSum[ch][newKNow-1] * mu[x-kNow] % MOD + MOD) % MOD;
            res = (res + z) % MOD;
        }
    }

    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    // 2^x
    mu[0] = 1;
    FOR(i,1,100000) mu[i] = mu[i-1] * 2 % MOD;

    cin >> n >> q;
    cin >> s0 >> t;

    MS(prefixSum, 0);
    FOR(i,0,SZ(t)-1)
        FOR(ch,0,25)
            if (ch == t[i] - 'a') prefixSum[ch][i+1] = (prefixSum[ch][i] * 2 + 1) % MOD;
            else prefixSum[ch][i+1] = (prefixSum[ch][i] * 2) % MOD;

    while (q--) {
        cin >> x >> st;
        cout << solve() << "\n";
    }
    return 0;
}
