/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - https://codeforces.com/blog/entry/70654
        - Use a list of set to save obstacles
        - Save points that have been used to turn right in the turnedRight set
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
const int MAXM = 1010;
const int MAXK = 110;
const int MAXQ = 200010;

int n, m, k;
set<int> row[MAXN], col[MAXN];
set<II> turnedRight;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m >> k;
    ll remain = (ll) n * m - k;
    FOR(i,1,k) {
        int x, y;
        cin >> x >> y;
        row[x].insert(y);
        col[y].insert(x);
    }
    II blockCol = II(0, m+1);
    II blockRow = II(0, n+1);
    II now = II(1, 1);
    remain--;
    int dir = 0;

    while (1) {
        // cout << now.FI << ' ' << now.SE << ' ' << dir << endl;
        if (dir == 0) {
            set<int>:: iterator it = row[now.FI].upper_bound(now.SE);
            int rigBlock = blockCol.SE;
            if (it != row[now.FI].end()) rigBlock = min(rigBlock, *it);

            int eat = max(0, rigBlock - now.SE - 1);
            remain -= eat;

            blockRow.FI = now.FI;
            now = II(now.FI, rigBlock-1);
        }
        else if (dir == 1) {
            set<int>:: iterator it = col[now.SE].upper_bound(now.FI);
            int downBlock = blockRow.SE;
            if (it != col[now.SE].end()) downBlock = min(downBlock, *it);

            int eat = max(0, downBlock - now.FI - 1);
            remain -= eat;

            blockCol.SE = now.SE;
            now = II(downBlock-1, now.SE);
        }
        else if (dir == 2) {
            set<int>:: iterator it = row[now.FI].upper_bound(now.SE);
            int lefBlock = blockCol.FI;
            if (it == row[now.FI].end()) {
                if (SZ(row[now.FI])) {
                    it--;
                    lefBlock = max(lefBlock, *it);
                }
            }
            else if (it != row[now.FI].begin()) {
                it--;
                lefBlock = max(lefBlock, *it);
            }

            int eat = max(0, now.SE - lefBlock - 1);
            remain -= eat;

            blockRow.SE = now.FI;
            now = II(now.FI, lefBlock+1);
        }
        else {
            set<int>:: iterator it = col[now.SE].upper_bound(now.FI);
            int upBlock = blockRow.FI;
            if (it == col[now.SE].end()) {
                if (SZ(col[now.SE])) {
                    it--;
                    upBlock = max(upBlock, *it);
                }
            }
            else if (it != col[now.SE].begin()) {
                it--;
                upBlock = max(upBlock, *it);
            }

            int eat = max(0, now.FI - upBlock - 1);
            remain -= eat;

            blockCol.FI = now.SE;
            now = II(upBlock+1, now.SE);
        }
        if (turnedRight.count(now)) break;
        turnedRight.insert(now);
        dir = (dir+1) % 4;
    }
    if (remain > 0) cout << "No";
    else cout << "Yes";
    return 0;
}
