/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let's consider number x, which would be number y that x & y = 0? (it has an edge connecting
        x and y in the graph)
        - y should be submask of k = (2^n - 1) ^ x
        - Let's dfs from x, we consider all submask of k and dfs from k.
        - But it's not enough, if k is in the input array, we should do as we did with x (consider all
        submask of k' = (2^n - 1) ^ k) and so on.
        - At one node, we go n times, as we try to flip bit 1 only and continue to dfs. There are 2^n
        nodes => Complexity O(n*2^n)
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
const int MAXN = 5000010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, m, a[MAXN], mask;
bool exist[MAXN], visit[MAXN];

void dfs(int u) {
    if (visit[u]) return;
    visit[u] = true;
    FOR(i,0,n-1)
        if (u & (1<<i)) dfs(u ^ (1<<i));
    if (exist[u]) dfs(mask ^ u);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m;
    FOR(i,1,m) {
        cin >> a[i];
        exist[a[i]] = true;
    }
    mask = (1 << n) - 1;

    int res = 0;
    FOR(i,1,m)
        if (!visit[a[i]]) {
            dfs(mask ^ a[i]);
            res++;
        }
    cout << res;
    return 0;
}
