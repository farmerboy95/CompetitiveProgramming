/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let's denote the stacks as a NxM 0-1 grid (HxS, A-B).
        - Let's fix the kind of paper to be graded, for example, 0. Let f[col][start] is the number
        of context switches independently required for just the col-th stack (imagining that it 
        has an additional unloseable subject-start paper at its top). We can observe that the total 
        number of context switches required to handle all M stacks is then simply 
        max{f[1][start], f[2][start], f[3][start], ..., f[M][start]}.
        - Let dp2[col][start][op] be the minimum number of context switches when we remove "op" papers 
        at stack col, with kind of paper "start" at the top.
        - It can be calculated from dp[col][start][last][row][op] = the minimum number of context 
        switches when we remove "op" paper at stack col, with kind of paper "start" at the top, the
        previously graded paper has kind "last" and with kind of paper "start" at the top. This
        dp is very straightforward.
        - So dp2[col][start][op] = min(dp[col][start][n][0][op], dp[col][start][n][1][op])
        - Now we have a list of column with number of context switches for each one. Which one should
        we reduce first? Yes, the one with the highest value of context switches. We use a priority queue
        to do this, we take the largest one, with the column index and the number of paper thrown already.
        We try to check if we can have less context switches when we increase the number of paper thrown
        or not. If we can find one closest to the previous "op", we put the new value to the priority
        queue and go on. By the way, we should update the result for the sum of paper thrown. We can prove
        that it's the smallest number of lost papers to have that amount of context switches (the more 
        we throw, the less we have to switch).
        - Complexity O(n^2 * m)
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
const int MAXN = 310;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, m, k, l[MAXN * MAXN], res[2][MAXN * MAXN], dp[MAXN][2][MAXN][2][MAXN], a[MAXN][MAXN], dp2[MAXN][2][MAXN];

void input() {
    cin >> n >> m >> k;
    FOR(i,1,n) {
        string s;
        cin >> s;
        FOR(j,0,m-1) a[i][j+1] = (s[j] == 'B');
    }
    FOR(i,1,k) cin >> l[i];
}

void init() {
    FOR(i,0,n*m) res[0][i] = res[1][i] = 1000;
}

void solve() {
    // dp[col][start]
    FOR(col,1,m) {
        FOR(start,0,1) {
            FOR(row,0,n) FOR(last,0,1) FOR(op,0,n) dp[col][start][row][last][op] = 1000;
            dp[col][start][0][start][0] = 1;
            FOR(row,0,n-1)
                FOR(last,0,1)
                    FOR(op,0,n)
                        if (dp[col][start][row][last][op] > 0) {
                            // removing a[row+1][col]
                            dp[col][start][row+1][last][op+1] = min(
                                dp[col][start][row+1][last][op+1], 
                                dp[col][start][row][last][op]
                            );
                            // not removing a[row+1][col]
                            if (a[row+1][col] == last) {
                                dp[col][start][row+1][last][op] = min(
                                    dp[col][start][row+1][last][op], 
                                    dp[col][start][row][last][op]
                                );
                            } else {
                                dp[col][start][row+1][1-last][op] = min(
                                    dp[col][start][row+1][1-last][op], 
                                    dp[col][start][row][last][op] + 1
                                );
                            }
                        }
            FOR(op,0,n) dp2[col][start][op] = min(dp[col][start][n][0][op], dp[col][start][n][1][op]);
        }
    }

    FOR(start,0,1) {
        priority_queue<III> h;
        FOR(j,1,m) {
            int last = start;
            int ctxSw = 1;
            FOR(i,1,n) {
                if (a[i][j] != last) {
                    ctxSw++;
                    last = 1-last;
                }
            }
            h.push({{ctxSw, j}, 0});
        }
        res[start][0] = h.top().FI.FI;
        int sumOp = 0;
        while (SZ(h)) {
            III r = h.top(); h.pop();
            int ctxSw = r.FI.FI, col = r.FI.SE, op = r.SE;
            int newOp = op;
            FOR(o,op+1,n)
                if (dp2[col][start][o] < ctxSw) {
                    newOp = o;
                    break;
                }
            if (newOp != op) {
                int newCtxSw = dp2[col][start][newOp];
                h.push({{newCtxSw, col}, newOp});
                sumOp += newOp - op;
            }

            if (SZ(h) == 0) {
                res[start][sumOp] = 1;
            } else {
                res[start][sumOp] = h.top().FI.FI;
            }
        }

        FOR(i,1,n*m-1)
            if (res[start][i] == 1000) res[start][i] = res[start][i-1]; 
    }

    FOR(i,1,k) cout << min(res[0][l[i]], res[1][l[i]]) << ' ';
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int te;
    cin >> te;
    FOR(o,1,te) {
        cout << "Case #" << o << ": ";
        input();
        init();
        solve();
    }
    return 0;
}
