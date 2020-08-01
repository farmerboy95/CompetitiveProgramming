/*
    Author: Nguyen Tan Bao
    Statement: https://www.facebook.com/codingcompetitions/hacker-cup/2011/round-1b/problems/A
    Status: AC
    Idea:
        - Strong implementation problem. Need to find way to make it as short as possible.
        - Just do what the statement said, but in a smart way, like king would move like rook and bishop
        but no multiple steps like them, then all checks will be in one of the 3 ways (rook, bishop and
        knight; kraken is a special case, just handle it separately)
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

int n;
char ch[MAXN][MAXN];
bool threaten[MAXN][MAXN];

int dx[16] = {1,0,0,-1, 1,1,-1,-1, 1,2,-1,-2,-1,2,-2,1};
int dy[16] = {0,1,-1,0, 1,-1,1,-1, 2,1,-2,-1,2,-1,1,-2};

bool isValid(int u, int v) {
    return u >= 1 && u <= 16 && v >= 1 && v <= 16;
}

void goAll(int u, int v) {
    FOR(i,1,16)
        FOR(j,1,16)
            if (ch[i][j] != ' ' && II(i, j) != II(u, v)) threaten[i][j] = true;
}

void go(int i, int u, int v, int mulStep) {
    int x = u, y = v;
    int cnt = 0;
    while (1) {
        cnt++;
        // check mulStep
        if (!mulStep && cnt > 1) break;
        x = x + dx[i];
        y = y + dy[i];
        // moving out of the grid => break
        if (!isValid(x, y)) break;
        // meet an occupied cell => break after threatening it
        if (ch[x][y] != ' ') {
            threaten[x][y] = true;
            break;
        }
    }
}

void goRook(int u, int v, int mulStep = 1) {
    FOR(i,0,3) go(i, u, v, mulStep);
}

void goBishop(int u, int v, int mulStep = 1) {
    FOR(i,4,7) go(i, u, v, mulStep);
}

void goKnight(int u, int v, int mulStep = 1) {
    FOR(i,8,15) go(i, u, v, mulStep);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int t;
    cin >> t;
    FOR(o,1,t) {
        cout << "Case #" << o << ": ";
        cin >> n;
        FOR(i,1,16) FOR(j,1,16) ch[i][j] = ' ';
        FOR(i,1,n) {
            char c;
            int u, v;
            cin >> c >> u >> v;
            ch[u][v] = c;
        }
        MS(threaten, 0);
        FOR(i,1,16)
            FOR(j,1,16)
                if (ch[i][j] != ' ') {
                    if (ch[i][j] == 'K') {
                        goRook(i, j, 0);
                        goBishop(i, j, 0);
                    }
                    if (ch[i][j] == 'Q') {
                        goRook(i, j);
                        goBishop(i, j);
                    }
                    if (ch[i][j] == 'R') {
                        goRook(i, j);
                    }
                    if (ch[i][j] == 'B') {
                        goBishop(i, j);
                    }
                    if (ch[i][j] == 'N') {
                        goKnight(i, j, 0);
                    }
                    if (ch[i][j] == 'S') {
                        goKnight(i, j);
                    }
                    if (ch[i][j] == 'A') {
                        goKnight(i, j, 0);
                        goBishop(i, j);
                    }
                    if (ch[i][j] == 'E') {
                        goAll(i, j);
                    }
                }
        int res = 0;
        FOR(i,1,16) FOR(j,1,16) res += threaten[i][j];
        cout << res << "\n";
    }
    return 0;
}
