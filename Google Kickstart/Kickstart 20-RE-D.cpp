/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let f[i][j] is the cost to get stone j at node i. 
        - We can consider a new graph, where each {node, stone type} combination is a vertex, and 
        for each street {u,v} in the given input, there will be S new edges {(u,c), (v,c)}, one 
        for each stone type c. Then we can run Dijkstra to fill the two dimensional cost.
        - Firstly, for all the stone types that are directly available at some nodes (as given in 
        the input), the f[node][stone] would be 0. All other combinations of node and stone type 
        will have initial cost set to infinity (-1 in specific).
        - At each step of trying to reduce cost for a vertex {u, c} from the queue, we can do the 
        following:
            + For each edge {u, v}, try to reduce the f[v][c] by carrying one type c stone from u to v.
            + Try to reduce the f[u][c] by applying recipes where c is an ingredient.
        - In this approach, there are N x S vertices. For each edge in the input graph there will 
        be corresponding S edges, so in total M x S edges.
        - The relaxation of the first type follows classic Dijkstra's algorithm's style, so the 
        complexity is O((N x S + M x S) x log(N x S)).
        - For the relaxation of the second type for each vertex {u, c}, we need to try only the 
        recipes where c is an ingredient. So in total, for each junction, a recipe will be applied 
        once for each of its ingredients. Each recipe has at most 3 ingredients. Which gives us 
        additional O(R x N x log(N x S)) complexity. So the total time complexity of this approach 
        is O((N x S + M x S + R x N) x log(N x S)) which is sufficient for test set 2.
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
const int MAXN = 310;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

struct Node {
    ll minCost;
    int node, stone;
    Node(ll minCost = 0, int node = 0, int stone = 0) : minCost(minCost), node(node), stone(stone) {}
    bool friend operator< (Node a, Node b) {
        return a.minCost > b.minCost;
    }
};

priority_queue<Node> h;
int n, m, s, r;
ll f[MAXN][MAXN];
vector<int> a[MAXN], stones[MAXN], recipe[MAXN];
vector<vector<int> > recipes;

void init() {
    FOR(i,1,n) {
        a[i].clear();
        stones[i].clear();
    }
    FOR(i,1,s) recipe[i].clear();
    recipes.clear();
}

void solve() {
    FOR(i,1,n)
        FOR(j,1,s) f[i][j] = -1;
    FOR(i,1,n)
        for (int stone : stones[i]) {
            f[i][stone] = 0;
            h.push(Node(f[i][stone], i, stone));
        }
    while (SZ(h)) {
        while (!h.empty()) {
            Node x = h.top();
            if (x.minCost == f[x.node][x.stone]) break;
            h.pop();
        }
        if (h.empty()) break;
        Node x = h.top(); h.pop();
        int u = x.node, st = x.stone;

        for (int v : a[u])
            if (f[u][st] + 1 < 1e12 && (f[v][st] == -1 || f[v][st] > f[u][st] + 1)) {
                f[v][st] = f[u][st] + 1;
                h.push(Node(f[v][st], v, st));
            }

        if (!SZ(recipe[st])) continue;
        for (int j : recipe[st]) {
            ll sum = 0;
            FOR(k,0,SZ(recipes[j])-2) {
                int stone = recipes[j][k];
                if (f[u][stone] == -1) {
                    sum = -1;
                    break;
                }
                sum += f[u][stone];
            }
            if (sum >= 1e12) sum = -1;
            if (sum != -1) {
                int newStone = recipes[j].back();
                if (f[u][newStone] == -1 || f[u][newStone] > sum) {
                    f[u][newStone] = sum;
                    h.push(Node(f[u][newStone], u, newStone));
                }
            }
        }
    }
    ll res = 1e18;
    FOR(i,1,n)
        if (f[i][1] != -1) res = min(res, f[i][1]);
    if (res == 1e18) res = -1;
    cout << res << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int te;
    cin >> te;
    FOR(o,1,te) {
        cout << "Case #" << o << ": ";
        cin >> n >> m >> s >> r;
        init();
        FOR(i,1,m) {
            int u, v;
            cin >> u >> v;
            a[u].push_back(v);
            a[v].push_back(u);
        }
        FOR(i,1,n) {
            int k, x;
            cin >> k;
            while (k--) {
                cin >> x;
                stones[i].push_back(x);
            }
        }
        FOR(i,1,r) {
            int k, x;
            cin >> k;
            vector<int> b;
            set<int> ss;
            while (k--) {
                cin >> x;
                b.push_back(x);
                ss.insert(x);
            }
            cin >> x;
            b.push_back(x);
            recipes.push_back(b);
            FORALL(it, ss) recipe[*it].push_back(i-1);
        }

        solve();
    }
    return 0;
}
