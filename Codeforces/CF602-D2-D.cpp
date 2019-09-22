/*
    Author: Nguyen Tan Bao
    Status: AC after reading editorial
    Idea: https://codeforces.com/blog/entry/21755
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
const int MAXN = 100010;
const int MAXM = 1000010;
const int MAXK = 110;
const int MAXQ = 200010;

int n, q, a[MAXN], d[MAXN], N, l[MAXN], r[MAXN];
stack<II> s;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> q;
    FOR(i,1,n) cin >> a[i];
    // get difference array
    FOR(i,1,n-1) d[i] = abs(a[i+1] - a[i]);
    N = n-1;

    // get l[i] which is the first element to the left of i that has d[l[i]] >= d[i]
    while (!s.empty()) s.pop();
    FOR(i,1,N) {
        l[i] = 0;
        while (!s.empty()) {
            II g = s.top();
            if (g.FI < d[i]) s.pop();
            else {
                l[i] = g.SE;
                break;
            }
        }
        s.push(II(d[i], i));
    }

    // get r[i] which is the first element to the right of i that has d[r[i]] >=d[i]
    while (!s.empty()) s.pop();
    FORE(i,N,1) {
        r[i] = n;
        while (!s.empty()) {
            II g = s.top();
            if (g.FI <= d[i]) s.pop();
            else {
                r[i] = g.SE;
                break;
            }
        }
        s.push(II(d[i], i));
    }

    while (q--) {
        int u, v;
        cin >> u >> v;
        v--;
        ll res = 0;
        FOR(i,u,v) {
            // get result within (u, v) based of l[i] and r[i]
            int g = max(l[i], u-1);
            int h = min(r[i], v+1);
            res += (ll) (i - g) * (h - i) * d[i];
        }
        cout << res << "\n";
    }
    return 0;
}