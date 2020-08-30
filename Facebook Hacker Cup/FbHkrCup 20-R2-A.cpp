/*
    Author: Nguyen Tan Bao
    Statement: https://www.facebook.com/codingcompetitions/hacker-cup/2020/round-2/problems/B
    Status: AC
    Idea:
        - If one seat section has more person than the expected range, reduce the number of persons
        until it reach the range, add the number of person to "neg"
        - If one seat section has less person than the expected range, increase the number of persons
        until it reach the range, add the number of person to "pos"
        - Easily see that our result should be max(pos, neg) or -1
        - If pos == neg, there's no need to do anything here
        - If pos > neg, find any range that we can still reduce the number of persons and increase the neg
        until it reach pos, if not possible after all => -1
        - If pos < neg, find any range that we can still increase the number of persons and increase the pos
        until it reach neg, if not possible after all => -1
        - The proof for the above stuff is trivial.
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
typedef pair<II, int> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;

const ll MODBASE = 1000000007LL;
const int MAXN = 1000010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, k;
ll s[MAXN], x[MAXN], y[MAXN], A, B, C, D;
II now[MAXN];

void input() {
    cin >> n >> k;

    FOR(i,1,k) cin >> s[i];
    cin >> A >> B >> C >> D;
    FOR(i,k+1,n) s[i] = (A * s[i-2] + B * s[i-1] + C) % D;

    FOR(i,1,k) cin >> x[i];
    cin >> A >> B >> C >> D;
    FOR(i,k+1,n) x[i] = (A * x[i-2] + B * x[i-1] + C) % D;

    FOR(i,1,k) cin >> y[i];
    cin >> A >> B >> C >> D;
    FOR(i,k+1,n) y[i] = (A * y[i-2] + B * y[i-1] + C) % D;
    
    FOR(i,1,n) y[i] = x[i] + y[i];
}

void init() {

}

ll solve() {
    ll pos = 0, neg = 0;
    FOR(i,1,n) {
        if (s[i] < x[i]) {
            pos += x[i] - s[i];
            now[i] = II(0, y[i] - x[i]);
        } else if (s[i] > y[i]) {
            neg += s[i] - y[i];
            now[i] = II(x[i] - y[i], 0);
        } else {
            now[i] = II(x[i] - s[i], y[i] - s[i]);
        }
    }
    ll diff = pos - neg;
    ll res = max(pos, neg);
    if (diff > 0) {
        FOR(i,1,n)
            if (now[i].FI < 0) diff -= min(diff, abs(now[i].FI));
        if (diff) return -1;
    } else if (diff < 0) {
        diff = abs(diff);
        FOR(i,1,n)
            if (now[i].SE > 0) diff -= min(diff, abs(now[i].SE));
        if (diff) return -1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int te;
    cin >> te;
    FOR(o,1,te) {
        cout << "Case #" << o << ": ";
        input();
        cout << solve() << "\n";
    }
    return 0;
}
