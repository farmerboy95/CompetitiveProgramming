/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - First we need to prove that ax = b (mod m) <=> b = 0 (mod gcd(a, m))
            + Let d = gcd(a, m)
            + Suppose ax = b (mod m) for some integer x. Then there is an integer k such that
            ax - b = km => b = ax - km. But (ax - km) % d == 0 => b = 0 (mod d)
            + Conversely, suppose b = 0 (mod d). Then b = rd for some integer r. Express d = pm + qa
            as an integer combination of m and a, which is possible by virtue of the euclidean algo.
            It follows that b = rd = rpm + rqa = (rq)a (mod m). Letting x = rq we rewrite this as
            ax = b (mod m)
        - So we now want to build a sequence of number a[1], a[2], ..., a[k] such that gcd(a[i], m)
        divides gcd(a[i+1], m). So we simply sort all the allowed numbers according to their gcd
        with m and do dp. Let dp[i] is the length of the longest sequence ending at i. Then we trace
        to get that longest sequence.
        - Now the problem becomes how to find x that ax = b (mod m). If a and m are coprime, we
        can simply solve x = b * a^-1 (mod m) = b * a^(phi(m)-1) (mod m). But if not, we can change
        ax = b (mod m) to ax + mk = b. Then we can simply divide a, m, b by gcd(a, m) (because
        b = 0 (mod gcd(a, m))) and do as the previous case.
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
const int MAXN = 200010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, m, dp[MAXN], trace[MAXN], Max[MAXN];
bool valid[MAXN];
vector<II> a;
vector<int> divisor, res, res2;

int gcd(int a, int b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

ll binPowMod(ll a, ll b) {
    a %= m;
    ll res = 1;
    while (b > 0) {
        if (b & 1LL) res = res * a % m;
        a = a * a % m;
        b >>= 1LL;
    }
    return res;
}

ll add(ll a, ll b) {
    return (a + b) % m;
}

ll sub(ll a, ll b) {
    return (a - b + m) % m;
}

ll mul(ll a, ll b) {
    return a * b % m;
}

int phi(int u) {
    int x = u;
    for (int j : divisor) {
        if (j == 1) continue;
        if (x % j == 0) {
            while (x % j == 0) x /= j;
            u -= u / j;
        }
    }
    return u;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m;
    FOR(i,1,m)
        if (m % i == 0) divisor.push_back(i);
    FOR(i,0,m-1) valid[i] = true;
    FOR(i,1,n) {
        int x;
        cin >> x;
        valid[x] = false;
    }
    a.push_back(II(-1, -1));
    FOR(i,0,m-1) {
        if (!valid[i]) continue;
        int g = gcd(i, m);
        a.push_back(II(g, i));
    }
    sort(ALL(a));
    int n = SZ(a)-1;

    FOR(i,1,n) {
        dp[i] = 1;
        if (a[i].FI == a[i-1].FI) {
            dp[i] = dp[i-1] + 1;
            trace[i] = i-1;
        } else {
            int p = 0, pos = 0;
            for (int j : divisor)
                if (j >= a[i].FI) break;
                else if (a[i].FI % j) continue;
                else {
                    if (dp[Max[j]] > p) {
                        p = dp[Max[j]];
                        pos = Max[j];
                    }
                }
            if (p) {
                dp[i] = p + 1;
                trace[i] = pos;
            }
        }
        if (Max[a[i].FI] == 0 || dp[Max[a[i].FI]] < dp[i]) Max[a[i].FI] = i; 
    }

    int len = 0, pos = 0;
    for (int j : divisor) {
        if (Max[j] > 0 && dp[Max[j]] > len) {
            len = dp[Max[j]];
            pos = Max[j];
        }
    }
    while (pos) {
        res.push_back(a[pos].SE);
        pos = trace[pos];
    }
    reverse(ALL(res));

    res2.push_back(res[0]);

    FOR(i,1,SZ(res)-1) {
        int u = res[i-1];
        int v = res[i];
        if (v == 0) res2.push_back(0);
        else {
            int g = gcd(u, gcd(v, m));
            u /= g;
            v /= g;
            res2.push_back(mul(v, binPowMod(u, phi(m/g)-1)));
        }
    }

    cout << len << endl;
    FOR(i,0,SZ(res2)-1) cout << res2[i] << ' ';
    return 0;
}
