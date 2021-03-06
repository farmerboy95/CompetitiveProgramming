/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: http://codeforces.com/blog/entry/57605
        - More or less like this solution: http://codeforces.com/contest/922/submission/35055961
        - Basically pure backtracking, prioritize adding current number into the list
        and then remove numbers from n.
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
const int MAXN = 300010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, k, in[MAXN];
vector<int> d[MAXN];

bool solve(int u, int num) {
    if (num == k) return true;
    if (u > n || num > k) return false;

    in[u] = 1;
    int add = 0;
    FOR(i,0,SZ(d[u])-1) add += in[d[u][i]];

    if (solve(u+1, num+add)) return true;

    in[u] = 0;
    if (solve(u+1, num)) return true;

    return false;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> k;
    int num = 0;
    FOR(i,1,n)
        for (int j = i * 2; j <= n; j += i) {
            d[j].emplace_back(i);
            num++;
        }
    if (num < k) {
        cout << "No";
        return 0;
    }

    solve(1, 0);
    int res = 0;
    FOR(i,1,n) res += in[i];
    cout << "Yes\n";
    cout << res << "\n";
    FOR(i,1,n)
        if (in[i]) cout << i << ' ';
    return 0;
}
