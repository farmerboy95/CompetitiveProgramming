/*
    Author: Nguyen Tan Bao
    Statement: https://www.facebook.com/hackercup/problem/185328794823941/
    Status: AC
    Idea:
        - As the grid is small, we simply consider all cells, for each cell, we consider 4 direction,
        try to get the sum of kinetic energy on one direction and then leave it to slide until the energy
        is below 0, then compare the number of cell slided with the current result.
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
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, m;
char ch[MAXN][MAXN];
int dx[4] = {1,0,0,-1};
int dy[4] = {0,1,-1,0};

bool isValid(int x, int y) {
    return (x >= 1 && x <= n && y >= 1 && y <= m);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int t;
    cin >> t;
    FOR(o,1,t) {
        cout << "Case #" << o << ": ";
        cin >> n >> m;
        FOR(i,1,n) FOR(j,1,m) cin >> ch[i][j];
        int res = 0;
        FOR(i,1,n)
            FOR(j,1,m) {
                FOR(k,0,3) {
                    int x = i, y = j, sum = 0;
                    while (isValid(x, y)) {
                        sum += ch[x][y] - '0';
                        int u = x + dx[k], v = y + dy[k], slide = 0, sumNow = sum;
                        while (isValid(u, v)) {
                            sumNow -= ch[u][v] - '0';
                            if (sumNow >= 0) slide++;
                            else break;
                            u += dx[k];
                            v += dy[k];
                        }
                        res = max(res, slide);
                        x += dx[k];
                        y += dy[k];
                    }
                }
            }
        cout << res << "\n";
    }
    return 0;
}
