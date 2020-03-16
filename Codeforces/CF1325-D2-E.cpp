/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: Mainly from https://codeforces.com/blog/entry/74235
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
const int MAXM = 1000010;
const int MAXK = 16;
const int MAXQ = 200010;

int n;
int nt[MAXM], dist[MAXM];
vector<int> d[MAXM], edgesFromNode[MAXM], primes;
vector<vector<int> > edges;

void sieveBase(int N) {
    // add 1 as a prime
    primes.push_back(1);

    // d[i] contains list of prime factors of i, remove factors that have 2 occurences
    FOR(i,2,N) {
        if (nt[i] == 0) {
            primes.push_back(i);
            nt[i] = i;
            for (ll j = (ll) i * i; j <= N; j += i) nt[j] = i;
        }
        d[i] = d[i / nt[i]];
        vector<int>::iterator it = find(d[i].begin(), d[i].end(), nt[i]);
        if (it != d[i].end()) d[i].erase(it);
        else d[i].push_back(nt[i]);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    sieveBase(1000000);

    cin >> n;
    FOR(i,0,n-1) {
        int x;
        cin >> x;
        if (SZ(d[x]) == 0) {
            cout << 1;
            return 0;
        }
        // add 1 if there is only one factor in d[x]
        if (SZ(d[x]) == 1) d[x].push_back(1);

        // edges stores list of edges in the graph
        edges.push_back({d[x][0], d[x][1]});

        // edgesFromNode[i] stores position in "edges" of edges that has i as an endpoint
        edgesFromNode[d[x][0]].push_back(i);
        edgesFromNode[d[x][1]].push_back(i);
    }

    int res = 1000000000;
    FOR(i,0,SZ(primes)-1) {
        // consider all primes that are smaller than 1000
        int pr = primes[i];
        if (pr * pr > 1000000) break;
        FOR(j,0,SZ(primes)-1) dist[primes[j]] = 0;
        queue<II> q;

        // mark dist from other endpoints of edges going from "pr"
        FOR(j,0,SZ(edgesFromNode[pr])-1) {
            int e = edgesFromNode[pr][j];
            if (edges[e][0] != pr) {
                q.push(II(e, 0));
                dist[edges[e][0]] = 1;
            }
            else {
                q.push(II(e, 1));
                dist[edges[e][1]] = 1;
            }
        }

        while (SZ(q)) {
            II r = q.front(); q.pop();
            int node = edges[r.FI][r.SE];
            FOR(j,0,SZ(edgesFromNode[node])-1) {
                int e = edgesFromNode[node][j];
                // not going back
                if (e != r.FI) {
                    II np;
                    if (edges[e][0] != node) np = II(e, 0);
                    else np = II(e, 1);
                    int newNode = edges[np.FI][np.SE];
                    if (dist[newNode] == 0 && newNode != pr) {
                        q.push(np);
                        dist[newNode] = dist[node] + 1;
                    }
                    else {
                        // meet a visited node, simply check res
                        // note that this result may not correct because it may go back
                        // to a node (newNode) in the path from "pr" to "node" but
                        // it does not matter, we would check all primes anyway
                        res = min(res, dist[node] + dist[newNode] + 1);
                    }
                }
            }
        }
    }
    if (res == 1000000000) res = -1;
    cout << res;
    return 0;
}
