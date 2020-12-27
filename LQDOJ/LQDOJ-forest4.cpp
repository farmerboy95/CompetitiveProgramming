/*
    Author: Nguyen Tan Bao
    Statement: https://lqdoj.edu.vn/problem/forest4
    Status: AC
    Idea: 
        - 2D Binary Indexed Tree in NlogN
        - https://codeforces.com/blog/entry/13813?#comment-187779
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
const int MAXQ = 100010;

int n, m, q;

int ch[MAXQ], x[MAXQ], y[MAXQ], u[MAXQ], v[MAXQ], c[MAXQ];
vector<int> X, Y;
vector<ll> A[2*MAXQ];
vector<int> order[2*MAXQ];

int getX(int U) {
    return lower_bound(ALL(X), U) - X.begin() + 1;
}

int getY(int V) {
    return lower_bound(ALL(Y), V) - Y.begin() + 1;
}

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
        for (int xx = point.FI; xx <= SZ(X); xx = xx + (xx & (-xx))) {
            order[xx].push_back(point.SE);
            // add value 0 to the tree to init
            A[xx].push_back(0);
        }
    }
    // add one more 0 to all trees with at least one elements as the trees are 1-based
    FOR(i,1,SZ(X))
        if (SZ(A[i])) A[i].push_back(0);
}

ll getVer(int g, int h) {
    ll res = 0;
    // when counting, h may not be in order[g] (as we are going backward)
    // we need to get the upper_bound, no need to deduct by 1 as it's 1-based
    int realH = upper_bound(ALL(order[g]), h) - order[g].begin();
    for (int i = realH; i > 0; i = i - (i & (-i))) res += A[g][i];
    return res;
}

ll get(int g, int h) {
    ll res = 0;
    for (int i = g; i > 0; i = i - (i & (-i))) res += getVer(i, h);
    return res;
}

void updateVer(int g, int h, int val) {
    // as the value of h will always be in order[g], we just need to get realH as lower_bound
    // +1 as it's 1-based
    int realH = lower_bound(ALL(order[g]), h) - order[g].begin() + 1;
    for (int i = realH; i < SZ(A[g]); i = i + (i & (-i))) A[g][i] += val;
}

void update(int g, int h, int val) {
    for (int i = g; i <= SZ(X); i = i + (i & (-i))) updateVer(i, h, val);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m >> q;
    FOR(i,1,q) {
        cin >> ch[i] >> x[i] >> y[i];
        if (ch[i] == 1) cin >> u[i] >> v[i] >> c[i];
    }

    // compress values
    FOR(i,1,q) {
        X.push_back(x[i]);
        if (ch[i] == 1) X.push_back(u[i]+1);

        Y.push_back(y[i]);
        if (ch[i] == 1) Y.push_back(v[i]+1);
    }

    sort(ALL(X));
    sort(ALL(Y));
    X.resize(unique(ALL(X)) - X.begin());
    Y.resize(unique(ALL(Y)) - Y.begin());

    // put the compressed value into a list of points to build
    vector<II> P;
    FOR(i,1,q) {
        if (ch[i] == 1) {
            P.push_back(II(getX(x[i]), getY(y[i])));
            P.push_back(II(getX(x[i]), getY(v[i]+1)));
            P.push_back(II(getX(u[i]+1), getY(y[i])));
            P.push_back(II(getX(u[i]+1), getY(v[i]+1)));
        }
    }
    sort(ALL(P), cmp);
    build(P);

    // query
    FOR(i,1,q) {
        if (ch[i] == 1) {
            update(getX(x[i]), getY(y[i]), c[i]);
            update(getX(x[i]), getY(v[i]+1), -c[i]);
            update(getX(u[i]+1), getY(y[i]), -c[i]);
            update(getX(u[i]+1), getY(v[i]+1), c[i]);
        } else {
            cout << get(getX(x[i]), getY(y[i])) + 1 << "\n";
        }
    }
    return 0;
}
