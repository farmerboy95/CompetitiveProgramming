/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Each contestant will have one of 2^3 = 8 possibilities of problem status.
        - Let f[m][j] is the number of way that we can achieve j points with mask m
        => f[m][j] = sum(f[p][k]) (choose a mask p which has number of set bits + 1 = number of set bits of m, 
        let z is that unset bit) (j-points[z] <= k <= j-1)
        - Let dp[i][j] is the number of scoreboard when we iterate to contestant i, and that contestant has j points
        => dp[i][j] = sum(dp[i-1][k]) * f[mask][j] (k > j)
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
typedef pair<ll, ll> II;
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
const int MAXN = 500010;
const int MAXM = 1000010;
const int MAXK = 110;
const int MAXQ = 200010;

ll f[8][200010], sum[200010], dp[25][200010];

class SRMIntermissionPhase {
    public:

    ll add(ll a, ll b) {
        return (a + b) % MODBASE;
    }

    ll sub(ll a, ll b) {
        return (a - b + MODBASE) % MODBASE;
    }

    ll mul(ll a, ll b) {
        return a * b % MODBASE;
    }

    int getBit(int u) {
        FOR(i,0,2)
            if (u & (1<<i)) return i;
        return -1;
    }

    ll getSum(int l, int r) {
        if (l == 0) return sum[r];
        return sub(sum[r], sum[l-1]);
    }

    int toNum(string &s) {
        int res = 0;
        FOR(i,0,2)
            if (s[i] == 'Y') res += (1<<i);
        return res;
    }

    void init(vector<int> &points) {
        f[0][0] = 1;
        FOR(i,1,200000) f[0][i] = 0;

        FOR(mask,1,7) {
            int bit = getBit(mask);
            int pre = mask ^ (1<<bit);
            sum[0] = f[pre][0];
            FOR(j,1,200000) sum[j] = add(sum[j-1], f[pre][j]);
            FOR(j,0,200000) {
                f[mask][j] = 0;
                int l = max(0, j - points[bit]), r = j - 1;
                if (l > r) continue;
                f[mask][j] = add(f[mask][j], getSum(l, r));
            }
        }
    }

    int countWays(vector<int> points, vector<string> description) {
        init(points);
        FOR(i,0,SZ(description)-1) {
            int mask = toNum(description[i]);
            if (i == 0) {
                FOR(j,0,200000) dp[i][j] = f[mask][j];
            }
            else {
                ll s = 0;
                FORE(j,200000,0) {
                    dp[i][j] = mul(s, f[mask][j]);
                    s = add(s, dp[i-1][j]);
                }
            }
        }
        ll res = 0;
        FOR(j,0,200000) res = add(res, dp[SZ(description)-1][j]);
        return res;
    }
};