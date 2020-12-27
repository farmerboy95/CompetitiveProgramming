/*
    Author: Nguyen Tan Bao
    Status: AC
    Statement: https://lqdoj.edu.vn/problem/forest6
    Idea: 
        - Combining forest4 and forest5
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
const int MAXQ = 100010;

int n, m, q;
int ch[MAXQ], x[MAXQ], y[MAXQ], u[MAXQ], v[MAXQ], c[MAXQ];
vector<ll> dataXY[MAXN], dataX[MAXN], dataY[MAXN], data1[MAXN];
vector<int> order[MAXN];

bool cmp(II a, II b) {
    if (a.SE != b.SE) return a.SE < b.SE;
    return a.FI < b.FI;
}

void build(vector<II> &P) {
    // A[i] is a Fenwick tree which is responsible for the y-coordinate
    // As we need to store the data after updating somewhere, we need to add it into A[i]
    // So here we fully focus on adding data for updating the trees
    for (II point : P) {
        // when updating xx, we need to update data in O(logN) trees
        // we need the order of y-coordinates to be sorted to find their indices later
        for (int xx = point.FI; xx <= n; xx = xx + (xx & (-xx))) {
            order[xx].push_back(point.SE);
            // add value 0 to the tree to init
            dataXY[xx].push_back(0);
            dataX[xx].push_back(0);
            dataY[xx].push_back(0);
            data1[xx].push_back(0);
        }
    }
    // add one more 0 to all trees with at least one elements as the trees are 1-based
    FOR(i,1,n)
        if (SZ(dataXY[i])) {
            dataXY[i].push_back(0);
            dataX[i].push_back(0);
            dataY[i].push_back(0);
            data1[i].push_back(0);
        }
}

void getVer(int g, int h, ll &dXY, ll &dX, ll &dY, ll &d1) {
    // when counting, h may not be in order[g] (as we are going backward)
    // we need to get the upper_bound, no need to deduct by 1 as it's 1-based
    int realH = upper_bound(ALL(order[g]), h) - order[g].begin();
    for (int i = realH; i > 0; i = i - (i & (-i))) {
        dXY += dataXY[g][i];
        dX += dataX[g][i];
        dY += dataY[g][i];
        d1 += data1[g][i];
    }
}

ll get(int g, int h) {
    ll dXY = 0, dX = 0, dY = 0, d1 = 0;
    for (int i = g; i > 0; i = i - (i & (-i))) getVer(i, h, dXY, dX, dY, d1);
    return dXY * g * h + dX * g + dY * h + d1;
}

ll getRange(int x, int y, int u, int v) {
    return get(u, v) - get(x-1, v) - get(u, y-1) + get(x-1, y-1);
}

void updateVer(int g, int h, ll dXY, ll dX, ll dY, ll d1) {
    // as the value of h will always be in order[g], we just need to get realH as lower_bound
    // +1 as it's 1-based
    int realH = lower_bound(ALL(order[g]), h) - order[g].begin() + 1;
    for (int i = realH; i < SZ(dataXY[g]); i = i + (i & (-i))) {
        dataXY[g][i] += dXY;
        dataX[g][i] += dX;
        dataY[g][i] += dY;
        data1[g][i] += d1;
    }
}

void update(int g, int h, ll dXY, ll dX, ll dY, ll d1) {
    for (int i = g; i <= n; i = i + (i & (-i))) updateVer(i, h, dXY, dX, dY, d1);
}

void update2(int x, int y, ll val) {
    update(x, y, val, -val * (y-1), -val * (x-1), val * (x-1) * (y-1));
}

void addRange(int x, int y, int u, int v, ll val) {
    update2(x, y, val);
    update2(x, v+1, -val);
    update2(u+1, y, -val);
    update2(u+1, v+1, val);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m >> q;
    FOR(i,1,q) {
        cin >> ch[i] >> x[i] >> y[i] >> u[i] >> v[i];
        if (ch[i] == 1) cin >> c[i];
    }

    // put the values into a list of points to build
    vector<II> P;
     // as we need to addRange(1,1,n,m) here, we have to put update points of this range to P
    P.push_back(II(1,1));
    P.push_back(II(1,m+1));
    P.push_back(II(n+1,1));
    P.push_back(II(n+1,m+1));
    FOR(i,1,q) {
        if (ch[i] == 1) {
            P.push_back(II(x[i], y[i]));
            P.push_back(II(x[i], v[i]+1));
            P.push_back(II(u[i]+1, y[i]));
            P.push_back(II(u[i]+1, v[i]+1));
        }
    }
    sort(ALL(P), cmp);
    build(P);

   
    addRange(1,1,n,m,1);
    // query
    FOR(i,1,q) {
        if (ch[i] == 1) {
            addRange(x[i], y[i], u[i], v[i], c[i]);
        } else {
            cout << getRange(x[i], y[i], u[i], v[i]) << "\n";
        }
    }
    return 0;
}
