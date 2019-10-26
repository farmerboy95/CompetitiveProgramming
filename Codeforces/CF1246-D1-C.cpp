/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - At each cell, we can choose to go right or down 1 cell.
        - In this problem, we can choose to go by a sequence of right steps or sequence of down steps.
        - Let ve[i][j] is the number of way to go down to cell (i, j) from cell (k, j) (k < i)
        - Let ho[i][j] is the number of way to go right to cell (i, j) from cell (i, k) (k < j)

        - Let's consider how to calculate ve[i][j], we start at cell (k, j) (k < i) and go down to (i, j)
        - But how to know that we can go from (k, j) to (i, j), there are rocks
        - Let xuong[i][j] is the furthest point k (k >= i) that we can reach if we stand at cell (i, j)
        - Of course, as the number of rocks increase when go from bottom to top, xuong[k][j] will increase 
        from top to bottom (k from 1 to n)
        - So we binary search the first cell (k, j) (k < i) that xuong[k][j] >= i, add all ho[p][j] (p from k to i-1)
        to ve[i][j], we can do this in O(1) using prefix sum

        - Apply similar idea to ho[i][j]

        - Complexity O(n^2 * logn)
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
const int MAXN = 2010;
const int MAXM = 7369000;
const int MAXK = 110;
const int MAXQ = 200010;
 
int n, m, a[MAXN][MAXN], xuong[MAXN][MAXN], ngang[MAXN][MAXN];
ll ho[MAXN][MAXN], ve[MAXN][MAXN], sumH[MAXN][MAXN], sumV[MAXN][MAXN];
 
ll add(ll a, ll b) {
    return (a + b) % MODBASE;
}
 
ll sub(ll a, ll b) {
    return (a - b + MODBASE) % MODBASE;
}
 
ll getSumH(int v, int l, int r) {
    return sub(sumH[r][v], sumH[l-1][v]);
}
 
ll getSumV(int u, int l, int r) {
    return sub(sumV[u][r], sumV[u][l-1]);
}
 
void tinhV(int u, int v) {
    int dau = 1, cuoi = u-1, mid;
    while (dau <= cuoi) {
        mid = (dau + cuoi) >> 1;
        if (xuong[mid][v] >= u) cuoi = mid-1;
        else dau = mid+1;
    }
    if (dau >= 1 && dau <= u-1 && xuong[dau][v] >= u) {
        ve[u][v] = getSumH(v, dau, u-1);
    }
    sumV[u][v] = add(sumV[u][v-1], ve[u][v]);
}
 
void tinhH(int u, int v) {
    int dau = 1, cuoi = v-1, mid;
    while (dau <= cuoi) {
        mid = (dau + cuoi) >> 1;
        if (ngang[u][mid] >= v) cuoi = mid-1;
        else dau = mid+1;
    }
    if (dau >= 1 && dau <= v-1 && ngang[u][dau] >= v) {
        ho[u][v] = getSumV(u, dau, v-1);
    }
    sumH[u][v] = add(sumH[u-1][v], ho[u][v]);
}
 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m;
    FOR(i,1,n)
        FOR(j,1,m) {
            char ch;
            cin >> ch;
            if (ch == 'R') a[i][j] = 1;
        }
    FORE(i,n,1)
        FOR(j,1,m) xuong[i][j] = xuong[i+1][j] + a[i][j];
    FORE(j,m,1)
        FOR(i,1,n) ngang[i][j] = ngang[i][j+1] + a[i][j];
    FOR(i,1,n)
        FOR(j,1,m) {
            xuong[i][j] -= a[i][j];
            ngang[i][j] -= a[i][j];
        }
    FOR(i,1,n)
        FOR(j,1,m) {
            xuong[i][j] = n - xuong[i][j];
            ngang[i][j] = m - ngang[i][j];
        }

    ho[1][1] = ve[1][1] = sumH[1][1] = sumV[1][1] = 1;
    
    FOR(i,1,n)
        FOR(j,1,m) {
            if (i == 1 && j == 1) continue;
            tinhH(i, j);
            tinhV(i, j);
        }
 
    if (n == m && n == 1) cout << 1;
    else cout << add(ho[n][m], ve[n][m]);
    return 0;
}