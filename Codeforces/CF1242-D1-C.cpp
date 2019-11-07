/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: 
        - Firstly, if sum of all numbers % n != 0, we print NO
        - Let req = sum of all numbers / n
        - When we take 1 number out of 1 box, that box will need another number to make sum of all numbers
        in the box equal to "req", of course that needed number should be from another box
        - As all numbers a[i][j] are distinct, the number that we need to find is unique, or there is no such number
        - So that we can construct a graph, each vertex has a directed edge to the number that it needs
        - Then we have to find cycles and assign each of them a bitmask (as n <= 15 and each vertex has one edge coming
        out from it)
        - Then we use dp bit subset (3^n) to find whether we can fill cycles in to k boxes
        - Trace and print the result
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
typedef pair<int, II> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;
 
const ll MODBASE = 1000000007LL;
const int MAXN = 16;
const int MAXM = 5001;
const int MAXK = 110;
const int MAXQ = 200010;

int n, b[MAXN][MAXM], len[MAXN], B[MAXN][MAXM];
int group[MAXN * MAXM];
ll s[MAXN];
vector<int> c;
int a[MAXN * MAXM];
bool visited[MAXN * MAXM];
vector<int> f[1<<15];
bool dp[1<<15];
int trace[1<<15];
II res[MAXN];

// find the vertex that a number should be mapped with
int get(ll u) {
    int dau = 0, cuoi = SZ(c)-1, mid;
    while (dau <= cuoi) {
        mid = (dau + cuoi) >> 1;
        if (c[mid] <= u) dau = mid+1;
        else cuoi = mid-1;
    }
    if (cuoi < 0) return -1;
    if (c[cuoi] != u) return -1;
    return cuoi;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n) {
        cin >> len[i];
        FOR(j,1,len[i]) {
            cin >> b[i][j];
            s[i] += b[i][j];
        }
    }
    FOR(i,1,n)
        FOR(j,1,len[i]) c.emplace_back(b[i][j]);
    sort(ALL(c));

    FOR(i,1,n)
        FOR(j,1,len[i]) {
            // transform number b to vertex B
            B[i][j] = get(b[i][j]);
            // save box index of vertex
            group[B[i][j]] = i;
        }

    // check the first condition
    ll sum = 0;
    FOR(i,1,n) sum += s[i];
    if (sum % n) {
        cout << "No";
        return 0;
    }
    ll req = sum / n;

    FOR(i,0,SZ(c)-1) a[i] = -1;

    // create edges
    FOR(i,1,n) {
        FOR(j,1,len[i]) {
            int u = B[i][j];
            int v = get(req - (s[i] - b[i][j]));
            if (v == -1) continue;
            if (group[v] == i) {
                if (v != u) continue;
                a[u] = v;
            }
            else a[u] = v;
        }
    }

    // for each vertex, find its cycle and store the cycle in a mask
    FOR(i,0,SZ(c)-1) {
        int u = i;
        vector<int> cycle;
        FOR(j,1,n) visited[j] = false;
        cycle.emplace_back(u);
        visited[group[u]] = true;
        if (a[u] >= 0) {
            while (a[u] >= 0) {
                u = a[u];
                if (visited[group[u]]) break;
                cycle.emplace_back(u);
                visited[group[u]] = true;
            }
            
            if (group[u] != group[i]) continue;
            if (u != i) continue;

            int mask = 0;
            FOR(j,0,SZ(cycle)-1) {
                int u = cycle[j];
                int bit = group[u];
                mask |= (1 << (bit-1));
            }
            f[mask] = cycle;
        }
    }

    // dp step O(3^n)
    dp[0] = true;
    FOR(mask,1,(1<<n)-1) {
        for (int split = mask; split; split = (split-1) & mask) {
            if (SZ(f[split])) {
                if (dp[mask ^ split]) {
                    dp[mask] = true;
                    trace[mask] = mask ^ split;
                }
            }
        }
    }

    // trace and print result
    if (!dp[(1<<n)-1]) {
        cout << "No";
        return 0;
    }
    cout << "Yes\n";
    int now = (1<<n)-1;
    while (now) {
        int mask = now ^ trace[now];
        vector<int> cycle = f[mask];
        FOR(i,0,SZ(cycle)-1) {
            int u = cycle[i];
            int v = cycle[(i + 1) % SZ(cycle)];
            res[group[v]] = II(c[v], group[u]);
        }
        now = trace[now];
    }

    FOR(i,1,n) cout << res[i].FI << ' ' << res[i].SE << "\n";

    return 0;
}
