/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let's assume that distance between 1 and n is x, there are some cases here
        - Firstly, 1 is connected to n, and some node connect to 1, some node connect to n
                c ----- 1 ----------- n ----- a
                        |      x      |
                        |             |
                        |             |
                        d             b
        - So abs(dist(node, 1) - dist(node, n)) == x, we can just check if all abs(d[i] - l[i])
        are the same x, then generate the tree (solve2() function in the code)
        - Secondly, there are some nodes between 1 and n
                            k      x-k
                c ----- 1 ----- e ----- n ----- a
                        |       |       |
                        |       |       |
                        |       |       |
                        d       f       b
        - So there must be at least one d[i] + l[i] == x (to get the "e" node in above tree,
        we call it subroot), we can get y = d[i] - l[i] and we can attach all node j which
        have d[j] - l[j] == y to "e", if there is a node j that does not have subroot
        which has y = d[j] - l[j], there is no answer in this case. So we connect 1 and n
        to all subroot like a line, and attach children of them to corresponding subroot.
        - The problem is that there are a lot of such x, but it turns out there is only
        one x usable, which is min(d[i] + l[i]). Why? Because if x < min(d[i] + l[i]), there
        is no "e" node and we have to check the 1st case. If x > min(d[i] + l[i]), there 
        would be at least one d[j] + l[j] < x and there is no way to put it into the tree.
        => So there are only 2 cases to check.

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
const int MAXN = 500010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

struct Edge {
    int u, v, c;
    Edge(int u = 0, int v = 0, int c = 0) : u(u), v(v), c(c) {}
};

int n, d[MAXN], l[MAXN];
vector<Edge> res;
vector<III> a;
map<int, int> ma;

void addEdge(int u, int v, int c) {
    res.push_back(Edge(u, v, c));
}

bool solve(int x) {

    // create line from 1 -> subroots -> n
    FOR(i,2,n-1)
        if (d[i] + l[i] == x) a.push_back(III(II(d[i], i), d[i] - l[i]));
    sort(ALL(a));
    int pre = 1, dist = 0;
    FOR(i,0,SZ(a)-1) {
        if (ma.count(a[i].SE)) return false;
        addEdge(pre, a[i].FI.SE, a[i].FI.FI - dist);
        dist = a[i].FI.FI;
        ma[a[i].SE] = a[i].FI.SE;
        pre = a[i].FI.SE;
    }
    addEdge(pre, n, x - dist);

    FOR(i,2,n-1)
        // attach outer nodes to 1 or n
        if (d[i] - l[i] == -x) addEdge(1,i,d[i]);
        else if (d[i] - l[i] == x) addEdge(n,i,l[i]);
        else {
            // attach children to subroots
            if (d[i] + l[i] == x) continue;
            int h = d[i] - l[i];
            if (abs(h) % 2 != x % 2) return false;
            if (!ma.count(h)) return false;
            int u = (h + x) / 2;
            addEdge(ma[h], i, d[i] - u);
        }

    return true;
}

bool solve2() {
    res.clear();
    set<int> s;
    FOR(i,2,n-1) s.insert(abs(d[i] - l[i]));
    if (SZ(s) > 1) return false;
    int x = *s.begin();
    addEdge(1,n,x);
    FOR(i,2,n-1)
        if (d[i] - l[i] == -x) addEdge(1,i,d[i]);
        else if (d[i] - l[i] == x) addEdge(n,i,l[i]);
    return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    // corner case, just for sure
    if (n == 2) {
        cout << "TAK\n";
        cout << "1 2 1\n";
        return 0;
    }
    FOR(i,2,n-1) cin >> d[i];
    FOR(i,2,n-1) cin >> l[i];

    int L = 0;
    FOR(i,2,n-1) L = max(L, abs(d[i] - l[i]));
    int R = 1000000000;
    FOR(i,2,n-1) R = min(R, d[i] + l[i]);
    if (L > R) {
        cout << "NIE\n";
        return 0;
    }
    if (solve(R)) {
        cout << "TAK\n";
        FOR(i,0,SZ(res)-1) cout << res[i].u << ' ' << res[i].v << ' ' << res[i].c << "\n";
    }
    else if (solve2()) {
        cout << "TAK\n";
        FOR(i,0,SZ(res)-1) cout << res[i].u << ' ' << res[i].v << ' ' << res[i].c << "\n";
    }
    else cout << "NIE\n";
    return 0;
}
