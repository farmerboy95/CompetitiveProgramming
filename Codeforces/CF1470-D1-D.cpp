/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - https://codeforces.com/blog/entry/86464
        - BFS with black-white elements
*/

#include <bits/stdc++.h>
#define FI first
#define SE second
#define ALL(a) a.begin(),a.end()
#define SZ(a) int((a).size())
#define MS(s, n) memset(s, n, sizeof(s))
#define FOR(i,a,b) for (int i = (a); i <= (b); i++)
#define FORE(i,a,b) for (int i = (a); i >= (b); i--)
#define FORALL(it, a) for (__typeof((a).begin()) it = (a).begin(); it != (a).end(); it++)

using namespace std;
using ll = long long;
using ld = double;
using II = pair<int, int>;
using III = pair<II, int>;
using cd = complex<ld>;
using vcd = vector<cd>;

const ld EPS = 1e-9;
const ll MODBASE = 1000000007LL;
const int MAXN = 300010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, m, res[MAXN];
vector<int> a[MAXN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int te;
    cin >> te;
    while (te--) {
        cin >> n >> m;
        FOR(i,1,n) a[i].clear();
        FOR(i,1,m) {
            int u, v;
            cin >> u >> v;
            a[u].push_back(v);
            a[v].push_back(u);
        }
        FOR(i,1,n) res[i] = -1;
        queue<int> q;
        res[1] = 1;
        for (int v : a[1]) {
            res[v] = 0;
            q.push(v);
        }
        while (SZ(q)) {
            int u = q.front(); q.pop();
            for (int v : a[u]) {
                if (res[v] == -1) {
                    res[v] = 1;
                    for (int k : a[v]) {
                        if (res[k] == -1) {
                            res[k] = 0;
                            q.push(k);
                        }
                    }
                }
            }
        } 
        bool co = true;
        FOR(i,1,n)
            if (res[i] == -1) co = false;
        if (!co) {
            cout << "NO\n";
            continue;
        }
        int cnt = 0;
        FOR(i,1,n) cnt += res[i];
        cout << "YES\n";
        cout << cnt << "\n";
        FOR(i,1,n)
            if (res[i]) cout << i << ' ';
        cout << "\n";
    }
    return 0;
}