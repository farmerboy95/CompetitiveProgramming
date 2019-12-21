#include <bits/stdc++.h>
#define base 1000000007LL
#define ll long long
#define X first
#define Y second
#define ld double
#define pb push_back
#define EPS 1e-9
#define all(a) a.begin(),a.end()
#define sz(a) int((a).size())
#define ms(s, n) memset(s, n, sizeof(s))
#define FOR(i,a,b) for (int i = (a); i <= (b); i++)
#define FORE(i,a,b) for (int i = (a); i >= (b); i--)
#define FORALL(it, a) for (__typeof((a).begin()) it = (a).begin(); it != (a).end(); it++)
#define what_is(x) cout << #x << " is " << x << endl;
#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
//__builtin_ffs(x) return 1 + index of least significant 1-bit of x
//__builtin_clz(x) return number of leading zeros of x
//__builtin_ctz(x) return number of trailing zeros of x

using namespace std;
typedef pair<int, int> II;
typedef pair<ll, II> III;

void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
	cout << *it << " = " << a << endl;
	err(++it, args...);
}

int st, en, n, m;

struct Light {
    char col;
    ll remainingTime, blueTime, purpleTime;
    Light(char col = 'a', ll remainingTime = 0, ll blueTime = 0, ll purpleTime = 0) : col(col), remainingTime(remainingTime), blueTime(blueTime), purpleTime(purpleTime) {}
};

struct Node {
    ll minTime;
    int node;
    Node(ll minTime = 0, int node = 0) : minTime(minTime), node(node) {}
    bool friend operator< (Node a, Node b)
	{
		return a.minTime > b.minTime;
	}
};

struct Edge {
    int des;
    ll travelingTime;
    Edge(int des = 0, ll travelingTime = 0) : des(des), travelingTime(travelingTime) {}
};

Light l[310];
vector<Edge> a[310];
ll d[310];
int trace[310];
priority_queue<Node> h;
vector<int> res;
bool lck[310];

Light getLightStatus(Light U, ll ti) {
    if (ti < U.remainingTime) {
        U.remainingTime -= ti;
        return U;
    }
    ti -= U.remainingTime;
    if (U.col == 'B') U.col = 'P';
    else U.col = 'B';
    ti %= (U.purpleTime+U.blueTime);
    if (U.col == 'B') {
        if (ti >= U.blueTime) {
            U.col = 'P';
            U.remainingTime = U.purpleTime + U.blueTime - ti;
        }
        else {
            U.remainingTime = U.blueTime - ti;
        }
    }
    else {
        if (ti >= U.purpleTime) {
            U.col = 'B';
            U.remainingTime = U.purpleTime + U.blueTime - ti;
        }
        else {
            U.remainingTime = U.purpleTime - ti;
        }
    }
    return U;
}

ll getTime(int u, int v, ll ti) {
    Light U = getLightStatus(l[u], ti);
    Light V = getLightStatus(l[v], ti);
    if (U.col == V.col) return 0;
    if (U.remainingTime != V.remainingTime) return min(U.remainingTime, V.remainingTime);

    ll res = U.remainingTime;
    U.col = (U.col == 'B' ? 'P' : 'B');
    U.remainingTime = (U.col == 'B' ? U.blueTime : U.purpleTime);
    V.col = (V.col == 'B' ? 'P' : 'B');
    V.remainingTime = (V.col == 'B' ? V.blueTime : V.purpleTime);
    if (U.remainingTime != V.remainingTime) return res + min(U.remainingTime, V.remainingTime);

    res += U.remainingTime;
    U.col = (U.col == 'B' ? 'P' : 'B');
    U.remainingTime = (U.col == 'B' ? U.blueTime : U.purpleTime);
    V.col = (V.col == 'B' ? 'P' : 'B');
    V.remainingTime = (V.col == 'B' ? V.blueTime : V.purpleTime);
    if (U.remainingTime != V.remainingTime) return res + min(U.remainingTime, V.remainingTime);

    return -1;
}

void dijkstra() {
    FOR(i,1,n) {
        d[i] = 1000000000000000000LL;
        lck[i] = false;
    }
    d[st] = 0;
    h.push(Node(0, st));
    while (1) {
        while (!h.empty() && h.top().minTime != d[h.top().node]) h.pop();
        if (h.empty()) break;
        Node r = h.top();
        h.pop();
        if (r.node == en) {
            cout << r.minTime << "\n";
            int g = en;
            while (g != st) {
                res.pb(g);
                g = trace[g];
            }
            res.pb(g);
            reverse(all(res));
            FOR(i,0,sz(res)-1) cout << res[i] << " ";
            return;
        }
        int u = r.node;
        lck[u] = true;
        FOR(i,0,sz(a[u])-1) {
            int v = a[u][i].des;
            ll c = a[u][i].travelingTime;
            if (!lck[v]) {
                ll w = getTime(u, v, d[u]);
                if (w == -1) continue;
                ll ti = d[u] + w + c;
                if (d[v] > ti) {
                    d[v] = ti;
                    h.push(Node(d[v], v));
                    trace[v] = u;
                }
            }
        }
    }
    cout << 0;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    cin >> st >> en;
    cin >> n >> m;
    FOR(i,1,n) {
        Light x;
        cin >> x.col >> x.remainingTime >> x.blueTime >> x.purpleTime;
        l[i] = x;
    }
    FOR(i,1,m) {
        int u, v;
        ll c;
        cin >> u >> v >> c;
        a[u].pb(Edge(v, c));
        a[v].pb(Edge(u, c));
    }
    dijkstra();
    return 0;
}
