/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Consider a moment x, if we need to leave the exam, we need to solve all the problems from x backwards
        and we can add points to the result when the amount of time needed to solve those problems is less than
        minimum time t of the remaining problems.
        - We can add some of the remaining problems to maximize the points, as long as the time needed is less
        than minimum time t of the remaining problems (no need to care about problems that we take because such
        case would be cover when we consider all x)
        - We only need to consider O(n) cases of moment x
*/
 
#include "bits/stdc++.h"
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
typedef pair<II, ll> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;
 
const ll MODBASE = 1000000007LL;
const int MAXN = 200010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;
 
struct Problem {
    int lvl, t;
    Problem(int lvl = 0, int t = 0) : lvl(lvl), t(t) {}
};
 
bool operator< (Problem a, Problem b) {
    if (a.t == b.t) return a.lvl < b.lvl;
    return a.t < b.t;
}
 
int t, n, T, a, b;
Problem A[MAXN];
 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> t;
    while (t--) {
        cin >> n >> T >> a >> b;
        ll cntH = 0;
        FOR(i,1,n) {
            cin >> A[i].lvl;
            cntH += A[i].lvl;
        }
        FOR(i,1,n) cin >> A[i].t;
        sort(A+1, A+n+1);
        A[n+1].t = T+1;
        ll sumT = 0;
        ll res = 0;
        FOR(i,1,n+1) {
            if (A[i].t != A[i-1].t) {
                if (sumT < A[i].t) {
                    ll cnt = i-1;
                    ll cntE = n-i+1-cntH;
                    ll remain = (ll) (A[i].t-1) - sumT;
 
                    ll used = min(remain / a, cntE);
                    cnt += used;
                    remain -= used * a;
 
                    used = min(remain / b, cntH);
                    cnt += used;
 
                    res = max(res, cnt);
                }
            }
            if (i == n+1) continue;
            if (A[i].lvl) sumT += b;
            else sumT += a;
            if (A[i].lvl) cntH--;
        }
        cout << res << "\n";
    }
    return 0;
}