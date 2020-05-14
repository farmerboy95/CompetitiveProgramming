
/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Same idea as the editorial
        https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/MCO/official/2017/editorial.pdf
        - Maintain list S of reachable segments and create list T of candidate segments when 
        considering new row.
        - Initially, S contains only one segment (1, Min)
        - Get all the forbidden houses in one row and create the segments based on the houses, put
        all of them in to T.
        - With S and T, we can get new S which is the list of reachable segments from old S.
        - Notice that next row and current row may not be consecutive and we can proceed with the between
        rows to quickly get the number of reachable cells and move S to right before next row.
        - The same thing would happen between current row and the last row (but there is no forbidden house
        there).
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

int n, m, curRow;
ll res;
vector<II> a, s, t, tmp;

void add(II a) {
    if (a.FI <= a.SE) {
        res += a.SE - a.FI + 1;
        tmp.push_back(a);
    }
}

void solve(int nextRow, int l, int r) {
    int y = 1;
    if (!SZ(s)) return;
    // get T
    t.clear();
    FOR(i,l,r) {
        int g = y, h = a[i].SE-1;
        y = a[i].SE + 1;
        if (h - g + 1 <= 0) continue;
        t.push_back(II(g, h));
    }
    if (n - y + 1 > 0) t.push_back(II(y, n));
    // get S
    if (nextRow - curRow > 1) {
        // move S to right before next row
        int num = nextRow - curRow - 1;
        int fi = s[0].FI;
        res += (ll) num * (n - fi + 1);
        s.clear();
        s.push_back(II(fi, n));
    }

    tmp.clear();
    int i = 0, j = 0;
    // consider pair of segments very carefully here, easy to get WA!!!!!
    while (i < SZ(s) && j < SZ(t)) {
        if (t[j].SE < s[i].FI) j++;
        else if (t[j].FI > s[i].SE) i++;
        else if (s[i].FI >= t[j].FI && s[i].SE <= t[j].SE) {
            add(II(s[i].FI, t[j].SE));
            i++;
            j++;
        }
        else if (s[i].FI <= t[j].FI && s[i].SE >= t[j].SE) {
            add(t[j]);
            j++;
        }
        else if (s[i].FI >= t[j].FI && s[i].SE >= t[j].SE) {
            add(II(s[i].FI, t[j].SE));
            j++;
        }
        else if (s[i].FI <= t[j].FI && s[i].SE <= t[j].SE) {
            add(t[j]);
            i++;
            j++;
        }
    }
    // update S
    s = tmp;
    // move to the next row
    curRow = nextRow;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m;
    int Min = n+1;
    FOR(i,1,m) {
        int x, y;
        cin >> x >> y;
        if (x == 1) Min = min(Min, y);
        else a.push_back(II(x, y));
    }
    s.push_back(II(1, Min-1));
    res = Min - 1;

    sort(ALL(a));
    curRow = 1;
    int l = 0;
    FOR(i,1,SZ(a)-1)
        if (a[i].FI != a[i-1].FI) {
            solve(a[i-1].FI, l, i-1);
            l = i;
        }
    solve(a[SZ(a)-1].FI, l, SZ(a)-1);
    if (curRow < n && SZ(s)) {
        int num = n - curRow;
        int fi = s[0].FI;
        res += (ll) num * (n - fi + 1);
    }
    cout << res;
    return 0;
}
