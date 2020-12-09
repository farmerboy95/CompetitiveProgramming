/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - https://codeforces.com/blog/entry/67727
        - It looked hard at first but we can separate using a vertical cut or a horizontal cut.
        - The key idea of E2 is to cut smaller from larger part.
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

struct point {
    int x, y;
};

struct rect {
    point llef, urig;
};

struct lr {
    bool operator() (rect a, rect b) {
        if (a.llef.x != b.llef.x) return a.llef.x < b.llef.x;
        if (a.urig.x != b.urig.x) return a.urig.x < b.urig.x;
        return a.llef.y < b.llef.y;
    }
};

struct rl {
    bool operator() (rect a, rect b) {
        if (a.urig.x != b.urig.x) return a.urig.x > b.urig.x;
        if (a.llef.x != b.llef.x) return a.llef.x > b.llef.x;
        return a.llef.y > b.llef.y;
    }
};

struct du {
    bool operator() (rect a, rect b) {
        if (a.llef.y != b.llef.y) return a.llef.y < b.llef.y;
        if (a.urig.y != b.urig.y) return a.urig.y < b.urig.y;
        return a.llef.x < b.llef.x;
    }
};

struct ud {
    bool operator() (rect a, rect b) {
        if (a.urig.y != b.urig.y) return a.urig.y > b.urig.y;
        if (a.llef.y != b.llef.y) return a.llef.y > b.llef.y;
        return a.llef.x > b.llef.x;
    }
};

set<rect, lr> LR[MAXN];
set<rect, rl> RL[MAXN];
set<rect, du> DU[MAXN];
set<rect, ud> UD[MAXN];

int cnt;

void move(vector<rect> &b, int id, int newId) {
    for (rect r : b) {
        LR[id].erase(r);
        RL[id].erase(r);
        DU[id].erase(r);
        UD[id].erase(r);

        LR[newId].insert(r);
        RL[newId].insert(r);
        DU[newId].insert(r);
        UD[newId].insert(r);
    }
}

int split(int id, set<rect>::iterator itt, int dir) {
    cnt++;
    vector<rect> b;
    if (dir == 1) for (auto it = LR[id].begin(); it != itt; it++) b.push_back(*it);
    else if (dir == 2) for (auto it = RL[id].begin(); it != itt; it++) b.push_back(*it);
    else if (dir == 3) for (auto it = DU[id].begin(); it != itt; it++) b.push_back(*it);
    else for (auto it = UD[id].begin(); it != itt; it++) b.push_back(*it);
    move(b, id, cnt);
    return cnt;
}

bool solve(int id) {
    int n = SZ(LR[id]);
    if (n == 1) return true;

    auto x1 = LR[id].begin(), x2 = RL[id].begin(), y1 = DU[id].begin(), y2 = UD[id].begin();

    int mx1 = x1->urig.x, mx2 = x2->llef.x, my1 = y1->urig.y, my2 = y2->llef.y;

    int dir = 0;
    set<rect>::iterator it;

    FOR(i,2,n) {
        x1++; x2++; y1++; y2++;
        if (mx1 <= x1->llef.x) {
            dir = 1;
            it = x1;
            break;
        }
        if (mx2 >= x2->urig.x) {
            dir = 2;
            it = x2;
            break;
        }
        if (my1 <= y1->llef.y) {
            dir = 3;
            it = y1;
            break;
        }
        if (my2 >= y2->urig.y) {
            dir = 4;
            it = y2;
            break;
        }
        mx1 = max(mx1, x1->urig.x);
        mx2 = min(mx2, x2->llef.x);
        my1 = max(my1, y1->urig.y);
        my2 = min(my2, y2->llef.y);
    }
    if (!dir) return false;
    int newId = split(id, it, dir);
    return (solve(id) & solve(newId));
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int n;
    cin >> n;
    cnt = 1;
    FOR(i,1,n) {
        rect r;
        cin >> r.llef.x >> r.llef.y >> r.urig.x >> r.urig.y;
        LR[cnt].insert(r);
        RL[cnt].insert(r);
        DU[cnt].insert(r);
        UD[cnt].insert(r);
    }

    if (solve(cnt)) cout << "YES";
    else cout << "NO";
    return 0;
}
