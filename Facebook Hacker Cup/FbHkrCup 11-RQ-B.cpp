/*
    Author: Nguyen Tan Bao
    Statement: https://www.facebook.com/hackercup/problem/157960964217186/
    Status: AC (tested with some AC code, not AC-ed in the contest page)
    Idea:
        - Simulate the problem, consider each place to drop the ball, use dp to find the final probability of
        each place at the bottom
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

char ch[MAXN][MAXN*2];
ld p[MAXN][MAXN*2];
int n, m, k, M;

void transform(int &u, int &v) {
    if (u % 2 == 0) {
        v *= 2;
    } else {
        v = v * 2 + 1;
    }
}

ld getRes(int pos, int kq) {
    MS(p, 0);
    p[0][pos] = 1;
    FOR(i,0,n-1) {
        FOR(j,0,M) {
            if (ch[i][j] == '.') {
                if (ch[i+1][j] != ' ') p[i+1][j] += p[i][j];
            } else if (ch[i][j] == 'x') {
                if (i % 2 == 0) {
                    if (j == 0) {
                        p[i+1][j+1] += p[i][j];
                    } else if (j == M) {
                        p[i+1][j-1] += p[i][j];
                    } else {
                        p[i+1][j+1] += p[i][j] / 2;
                        p[i+1][j-1] += p[i][j] / 2;
                    }
                } else {
                    if (j == 1) {
                        p[i+1][j+1] += p[i][j];
                    } else if (j == M - 1) {
                        p[i+1][j-1] += p[i][j];
                    } else {
                        p[i+1][j+1] += p[i][j] / 2;
                        p[i+1][j-1] += p[i][j] / 2;
                    }
                }
            }
        }
    }
    return p[n][kq];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int t;
    cin >> t;
    FOR(o,1,t) {
        cout << "Case #" << o << ": ";
        cin >> n >> m >> k;
        M = 2*(m-1);
        FOR(i,0,n) FOR(j,0,M) ch[i][j] = '.';
        FOR(i,0,n) {
            if (i % 2 == 0) {
                for (int j = 0; j <= M; j += 2) ch[i][j] = 'x';
            } else {
                for (int j = 1; j <= M; j += 2) ch[i][j] = 'x';
                ch[i][0] = ch[i][M] = ' ';
            }
        }
        FOR(j,1,M-1) ch[n][j] = '.';

        int q;
        cin >> q;
        FOR(i,1,q) {
            int u, v;
            cin >> u >> v;
            transform(u, v);
            ch[u][v] = '.';
        }
        int u = n, v = k;
        transform(u, v);

        ld res = 0;
        int pos = -1, cnt = 0;

        for (int j = 1; j <= M; j += 2) {
            ld now = getRes(j, v);
            if (now > res + EPS) {
                res = now;
                pos = cnt;
            } 
            cnt++;
        }

        cout << pos << ' ' << fixed << setprecision(6) << res << "\n";
    }
    return 0;
}
