/*
    Author: Nguyen Tan Bao
    Statement: https://www.facebook.com/codingcompetitions/hacker-cup/2020/round-2/problems/C
    Status: AC
    Idea:
        - Based on https://www.facebook.com/codingcompetitions/hacker-cup/2020/round-2/solutions
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

ll MOD = MODBASE;

int n, m, e, k;
ll A, B, C;
int x[MAXN], y[MAXN], w[MAXN], weight[MAXN], group[MAXN];
ll I[MAXN];
multiset<int> ms[MAXN][2], msD;

void input() {
    cin >> n >> m >> e >> k;

    FOR(i,0,k-1) cin >> x[i];
    cin >> A >> B >> C;
    FOR(i,k,n-1) x[i] = (A * x[i-2] + B * x[i-1] + C) % m;

    FOR(i,0,k-1) cin >> y[i];
    cin >> A >> B >> C;
    FOR(i,k,n-1) y[i] = (A * y[i-2] + B * y[i-1] + C) % m;

    FOR(i,0,k-1) cin >> I[i];
    cin >> A >> B >> C;
    FOR(i,k,e-1) I[i] = (A * I[i-2] + B * I[i-1] + C) % ((ll) n * m + n);
    
    FOR(i,0,k-1) cin >> w[i];
    cin >> A >> B >> C;
    FOR(i,k,e-1) w[i] = (A * w[i-2] + B * w[i-1] + C) % 1000000000;
}

void init() {
    FOR(i,0,n) {
        ms[i][0].clear();
        ms[i][1].clear();
    }
    msD.clear();
}

ll add(ll a, ll b) {
    return (a + b) % MOD;
}

ll sub(ll a, ll b) {
    return (a - b + MOD) % MOD;
}

ll mul(ll a, ll b) {
    return a * b % MOD;
}

// get maximum weight of any edge within a "half" of circle
int getMax(int circle, int groupIdx) {
    if (SZ(ms[circle][groupIdx]) == 0) return 0;
    return *ms[circle][groupIdx].rbegin();
}

// get maximum weight of any edge within a circle
int getMax(int circle) {
    return max(getMax(circle, 0), getMax(circle, 1));
}

// get the weight of minimum spanning tree
ll getSpanningTree(ll sum, ll sumMaxSmallCircle) {
    return sum - sumMaxSmallCircle - max(*ms[n][1].rbegin(), *msD.rbegin());
}

ll solve() {
    init();
    ll res = 1;
    // as n*m+n <= 10^6, we can store weight[i] as the weight of edge i
    FOR(i,0,n*m+n-1) weight[i] = 1;
    FOR(i,0,n-1) {
        if (x[i] > y[i]) swap(x[i], y[i]);
        // ms[i][0] and ms[i][1] are 2 multiset for 2 halves of a small circle i
        // if x[i] == y[i], we only use ms[i][1] (or 0 if you want)
        if (x[i] == y[i]) {
            FOR(j,0,m-1) {
                ms[i][1].insert(1);
                group[i*m+j] = 1;
            }
        } else {
            FOR(j,0,m-1)
                if (j >= x[i] && j < y[i]) {
                    ms[i][0].insert(1);
                    group[i*m+j] = 0;
                } else {
                    ms[i][1].insert(1);
                    group[i*m+j] = 1;
                }
        }
        // msD stores D[i] (= P[i] - R[i] in editorial) values
        msD.insert(getMax(i, 0) + getMax(i, 1) - getMax(i));
    }
    // the large circle weights
    FOR(j,0,n-1) ms[n][1].insert(1);

    // sumMaxSmallCircle stores sum of max weight of all small circles
    ll sum = (ll) m * n + n, sumMaxSmallCircle = n;
    FOR(i,0,e-1) {
        int circle = I[i] / m;
        int edge = I[i] % m;
        if (circle >= n) circle = n;

        // update ms, weight and msD
        // update sum and sumMaxSmallCircle
        if (circle == n) {
            ms[circle][1].erase(ms[circle][1].find(weight[I[i]]));
            sum -= weight[I[i]];

            weight[I[i]] = w[i];

            sum += weight[I[i]];
            ms[circle][1].insert(weight[I[i]]);
        } else {
            sum -= weight[I[i]];
            sumMaxSmallCircle -= getMax(circle);
            msD.erase(msD.find(getMax(circle, 0) + getMax(circle, 1) - getMax(circle)));
            ms[circle][group[I[i]]].erase(ms[circle][group[I[i]]].find(weight[I[i]]));

            weight[I[i]] = w[i];

            sum += weight[I[i]];
            ms[circle][group[I[i]]].insert(weight[I[i]]);
            sumMaxSmallCircle += getMax(circle);
            msD.insert(getMax(circle, 0) + getMax(circle, 1) - getMax(circle));
        }

        res = mul(res, getSpanningTree(sum, sumMaxSmallCircle) % MODBASE);
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
