/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: https://codeforces.com/blog/entry/84298
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
template<class T>
using min_pq = priority_queue<T, vector<T>, greater<T> >;
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

int MOD = 998244353;
int n, m;
vector<int> a[2][MAXN];

// Cost in the form of (B, A)
struct Cost {
    int cnt_trans;
    int cnt_edges;
    Cost(int t = 0, int e = 0): cnt_trans(t), cnt_edges(e)  {}
    
    static Cost inf() {
        return Cost(MAXN, MAXN);
    }
    
    bool is_small() const {
        return cnt_trans < 19;
    }
    
    ll true_cost() const {
        return (1ll << cnt_trans) + cnt_edges - 1;
    }
    
    ll true_cost_mod() const {
        ll ans = 1;
        FOR(i,1,cnt_trans) {
            ans += ans;
            if (ans >= MOD) ans -= MOD;
        }
        ans += cnt_edges - 1;
        while (ans >= MOD) ans -= MOD;
        while (ans < 0) ans += MOD;
        return ans;
    }
    
    friend bool operator<(const Cost& u, const Cost& v) {
        if (u.is_small() != v.is_small()) {
            return u.is_small();
        }
        if (u.is_small()) {
            if (u.true_cost() == v.true_cost()) return u.cnt_trans < v.cnt_trans;
            return u.true_cost() < v.true_cost();
        }
        if (u.cnt_trans == v.cnt_trans) return u.cnt_edges < v.cnt_edges;
        return u.cnt_trans < v.cnt_trans;
    }
    
    friend ostream& operator<<(ostream& out, const Cost& u ) {
        return out << "(" << u.cnt_trans << ", " << u.cnt_edges << ")";
    }
};

Cost d[2][MAXN][20], D[2][MAXN];

void dijkstra1() {
    // combine first and second step
    min_pq <tuple<Cost, int, int, int> > h;
    FOR(i,0,1) FOR(j,1,n) FOR(k,0,18) d[i][j][k] = Cost::inf();
    d[0][1][0] = Cost(0, 0);
    h.emplace(d[0][1][0], 0, 1, 0);

    while (SZ(h)) {
        int g, u, cur_trans;
        Cost c;
        tie(c, g, u, cur_trans) = h.top();
        h.pop();
        if (d[g][u][cur_trans] < c) continue;

        auto new_cost = Cost(c.cnt_trans, c.cnt_edges + 1);
        for (int v : a[g][u])
            if (new_cost < d[g][v][cur_trans]) {
                d[g][v][cur_trans] = new_cost;
                h.emplace(d[g][v][cur_trans], g, v, cur_trans);
            }

        // calculate the second step right here if new_trans > 18
        int new_trans = min(18, cur_trans + 1);
        new_cost = Cost(c.cnt_trans + 1, c.cnt_edges);
        if (new_cost < d[1-g][u][new_trans]) {
            d[1-g][u][new_trans] = new_cost;
            h.emplace(d[1-g][u][new_trans], 1-g, u, new_trans);
        }
    }

    Cost res = Cost::inf();
    FOR(i,0,1) FOR(k,0,18) res = min(res, d[i][n][k]);
    cout << res.true_cost_mod();
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m;
    FOR(i,1,m) {
        int u, v;
        cin >> u >> v;
        a[0][u].push_back(v);
        a[1][v].push_back(u);
    }
    dijkstra1();
    
    return 0;
}
