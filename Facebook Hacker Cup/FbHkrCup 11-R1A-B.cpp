/*
    Author: Nguyen Tan Bao
    Statement: https://www.facebook.com/codingcompetitions/hacker-cup/2011/round-1a/problems/B
    Status: AC
    Idea:
        - Easily see that each button can be pressed at most once.
        - We consider all cases of pressing on the first row (2^m cases), after pressing the first row,
        there would be some lighted and unlighted button on it, if one button (i, j) is unlighted, the 
        only way to make it lighted is to press the button at the same column but on the next row (i+1, j).
        Keep considering till the (n-1)-th row. Now we see if the last row is all lighted. If not, there
        is no answer for that case, otherwise, check the number of pressed button with the best one so far.
        - Complexity: O(n * m * 2^m)
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

int n, m, a[MAXN][MAXN], b[MAXN][MAXN];
int dx[5] = {1,0,0,-1,0};
int dy[5] = {0,1,-1,0,0};

void press(int u, int v, int &cnt) {
    FOR(i,0,4) {
        int x = u + dx[i], y = v + dy[i];
        if (x >= 1 && x <= n && y >= 1 && y <= m) b[x][y] = 1-b[x][y];
    }
    cnt++;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int t;
    cin >> t;
    FOR(o,1,t) {
        cout << "Case #" << o << ": ";
        cin >> n >> m;
        FOR(i,1,n) FOR(j,1,m) {
            char ch;
            cin >> ch;
            a[i][j] = (ch == '.' ? 0 : 1);
        }

        int res = 1000000000;
        FOR(mask,0,(1<<m)-1) {
            FOR(i,1,n) FOR(j,1,m) b[i][j] = a[i][j];
            int cnt = 0;
            FOR(i,1,m)
                if (mask & (1<<(i-1))) press(1, i, cnt);
            FOR(i,1,n-1)
                FOR(j,1,m)
                    if (!b[i][j]) press(i+1, j, cnt);
            bool co = true;
            FOR(j,1,m)
                if (!b[n][j]) co = false;
            if (co) res = min(cnt, res);
        }
        if (res == 1000000000) res = -1;
        cout << res << "\n";
    }
    return 0;
}
