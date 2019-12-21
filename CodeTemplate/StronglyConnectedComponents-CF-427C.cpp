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
typedef pair<int, int> II;
typedef pair<ll, II> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;

void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
    cout << *it << " = " << a << endl;
    err(++it, args...);
}

const ll MODBASE = 1000000007LL;
const int MAXN = 100010;

int n, m, c[MAXN], low[MAXN], num[MAXN], dfsNum, sccCnt, w[MAXN];
vector<int> a[MAXN];
stack<int> s;
bool visited[MAXN];
II f[MAXN];

void scc(int u) {
    low[u] = num[u] = ++dfsNum;
    s.push(u);
    visited[u] = true;
    FOR(i,0,SZ(a[u])-1) {
        int v = a[u][i];
        if (num[v] == -1) scc(v);
        if (visited[v]) low[u] = min(low[u], low[v]);
    }
    if (low[u] == num[u]) {
        int k = -1;
        sccCnt++;
        do {
            k = s.top();
            s.pop();
            w[k] = sccCnt;
            visited[k] = false;
        } while (k != u);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n) cin >> c[i];
    cin >> m;
    FOR(i,1,m) {
        int u, v;
        cin >> u >> v;
        a[u].emplace_back(v);
    }
    FOR(i,1,n) num[i] = -1;
    FOR(i,1,n)
        if (num[i] == -1) scc(i);
    FOR(i,1,sccCnt) f[i] = II(2000000000, 0);
    FOR(i,1,n) {
        if (c[i] == f[w[i]].FI) f[w[i]].SE++;
        else if (c[i] < f[w[i]].FI) f[w[i]] = II(c[i], 1);
    }
    ll res = 1, sum = 0;
    FOR(i,1,sccCnt) {
        res = res * f[i].SE % MODBASE;
        sum += f[i].FI;
    }
    cout << sum << ' ' << res;
    return 0; 
}
