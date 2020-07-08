/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Same as the editorial: https://codeforces.com/blog/entry/56666
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
const int MAXN = 100010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int res1[MAXN], res2[MAXN];

void process(int n) {
    if (n <= 0) return;
    int u = 0;
    while ((1<<u) <= n) u++;
    u--;
    int i = 1;
    // (2^u + i - 1) & (2^u - i) == 0
    // find the largest u that 2^u <= n, try to fill in the result till n and continue with the rest
    while ((1<<u) + i - 1 <= n) {
        res1[(1<<u) + i - 1] = (1<<u) - i;
        res1[(1<<u) - i] = (1<<u) + i - 1;
        i++;
    }
    process((1<<u) - i);
}

void solve1(int n) {
    if (n % 2) {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    process(n);
    FOR(i,1,n) cout << res1[i] << ' ';
    cout << "\n";
} 

void solve2(int n) {
    if (n <= 5) {
        cout << "NO\n";
        return;
    }
    int u = 0;
    while ((1<<u) <= n) u++;
    u--;
    if ((1<<u) == n) {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    if (n == 6) {
        cout << "3 6 2 5 1 4\n";
        return;
    }
    if (n == 7) {
        cout << "7 3 6 5 1 2 4\n";
        return;
    }
    cout << "7 3 6 5 1 2 4 ";
    // simply create cyclic permutation
    FOR(i,3,u) {
        int last = min(n, (1<<(i+1))-1);
        int x = (1<<i);
        FOR(j,x,last) {
            int p = j+1;
            if (p > last) p = x;
            cout << p << ' ';
        }
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int n;
    cin >> n;
    solve1(n);
    solve2(n);
    return 0;
}
