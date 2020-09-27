/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: https://codingcompetitions.withgoogle.com/kickstart/round/000000000019ff48/00000000003f47fb#analysis
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
const int MAXN = 110;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int s, ra, pa, rb, pb, c, id[20][20], ptr;
ll ban;
vector<int> a[40];
map<ll, int> ma[36][36][2];

void init() {
    cin >> s >> ra >> pa >> rb >> pb >> c;
    ptr = 0;
    ra--; pa--; rb--; pb--;
    // init arrays
    FOR(i,0,39) a[i].clear();
    FOR(i,0,35) FOR(j,0,35) FOR(k,0,1) ma[i][j][k].clear();

    // indexing nodes
    FOR(i,0,s-1)
        FOR(j,0,2*i) id[i][j] = ptr++;

    // create edges
    FOR(i,0,s-1)
        FOR(j,1,2*i) {
            int u = id[i][j], v = id[i][j-1];
            a[u].push_back(v);
            a[v].push_back(u);
        }
    FOR(i,0,s-2)
        for (int j = 0; j <= 2 * i; j += 2) {
            int u = id[i][j], v = id[i+1][j+1];
            a[u].push_back(v);
            a[v].push_back(u);
        }
    
    // ban = mask which contains unreachable nodes
    ban = 0;
    while (c--) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        int x = id[u][v];
        ban |= (1LL << x);
    }
}

int handle(ll mask, int fi, int se, int turn) {
    if (ma[fi][se][turn].count(mask)) return ma[fi][se][turn][mask];
    // carefully check if both cannot move => return 0
    bool fiCanMove = false, seCanMove = false;
    FOR(i,0,SZ(a[fi])-1) {
        int v = a[fi][i];
        if (mask & (1LL << v)) continue;
        fiCanMove = true;
        break;
    }
    FOR(i,0,SZ(a[se])-1) {
        int v = a[se][i];
        if (mask & (1LL << v)) continue;
        seCanMove = true;
        break;
    }
    int res = 0;
    // the first one will maximize the score, the second one will minimize the score
    if (turn == 0) {
        if (!fiCanMove) {
            if (!seCanMove) return ma[fi][se][turn][mask] = 0;
            return ma[fi][se][turn][mask] = handle(mask, fi, se, 1-turn);
        }
        bool co = false;
        FOR(i,0,SZ(a[fi])-1) {
            int v = a[fi][i];
            if (mask & (1LL << v)) continue;
            if (!co) {
                res = handle(mask | (1LL << v), v, se, 1-turn) + 1;
                co = true;
            }
            else res = max(res, handle(mask | (1LL << v), v, se, 1-turn) + 1);
        }
    } else {
        if (!seCanMove) {
            if (!fiCanMove) return ma[fi][se][turn][mask] = 0;
            return ma[fi][se][turn][mask] = handle(mask, fi, se, 1-turn);
        }
        bool co = false;
        FOR(i,0,SZ(a[se])-1) {
            int v = a[se][i];
            if (mask & (1LL << v)) continue;
            if (!co) {
                res = handle(mask | (1LL << v), fi, v, 1-turn) - 1;
                co = true;
            }
            else res = min(res, handle(mask | (1LL << v), fi, v, 1-turn) - 1);
        }
    }
    return ma[fi][se][turn][mask] = res;
}

void solve() {
    // init nodes are not reachable
    int fi = id[ra][pa], se = id[rb][pb];
    ban |= (1LL << fi);
    ban |= (1LL << se);
    cout << handle(ban, fi, se, 0) << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int te;
    cin >> te;
    FOR(o,1,te) {
        cout << "Case #" << o << ": ";
        init();
        solve();
    }
    return 0;
}
