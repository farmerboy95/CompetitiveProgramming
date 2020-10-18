/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - From https://codeforces.com/blog/entry/83771
        - Define f(l, p) as the sum of time needed when we have a single carrot of length l and it's
        splitted into p pieces.
        - Crucial observation: f(l, p-1) - f(l, p) >= f(l, p) - f(l, p+1)
        => The more cuts we make to a carrot, there is a diminishing returns in the decrease in cost 
        per cut. For any carrot, we don't need to think about making the (p+1)-th cut before making 
        the p-th cut.
        - So we can choose the carrot with the largest decrease in cost and add one extra cut for that.
        It can be maintained by a priority queue.
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
typedef pair<ll, int> II;
typedef pair<II, int> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;

const ll MODBASE = 1000000007LL;
const int MAXN = 100010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, k, a[MAXN], numPieces[MAXN];
priority_queue<II> h;

ll getSumTime(int len, int pieces) {
    int each = len / pieces;
    int r = len % pieces;
    return (ll) (pieces - r) * each * each + (ll) r * (each + 1) * (each + 1);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> k;
    FOR(i,1,n) cin >> a[i];
    FOR(i,1,n) numPieces[i] = 1;
    ll sum = 0;
    FOR(i,1,n) sum += (ll) a[i] * a[i];
    int need = k - n;
    FOR(i,1,n)
        if (numPieces[i] < a[i]) h.push(II(getSumTime(a[i], numPieces[i]) - getSumTime(a[i], numPieces[i]+1), i));
    while (need--) {
        II r = h.top(); h.pop();
        ll diff = r.FI; int pos = r.SE;
        sum -= diff;
        numPieces[pos]++;
        if (numPieces[pos] < a[pos]) h.push(II(getSumTime(a[pos], numPieces[pos]) - getSumTime(a[pos], numPieces[pos]+1), pos));
    }
    cout << sum;
    return 0;
}
