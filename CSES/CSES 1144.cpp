/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Salary Queries
        - Compress the salaries and query
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
const int MAXN = 200010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, m, a[MAXN], u[MAXN], v[MAXN];
char ch[MAXN];
vector<int> b;

struct BinaryIndexedTree {
    public:
    // 1-indexed
    BinaryIndexedTree(int n) {
        N = n;
        t.resize(N+1);
        FOR(i,0,N) t[i] = 0;
    }

    void update(int u, int val) {
        while (u <= N) {
            t[u] += val;
            u = u + (u & (-u));
        }
    }
 
    ll get(int u) {
        ll res = 0;
        while (u) {
            res += t[u];
            u = u - (u & (-u));
        }
        return res;
    }

    private:
    vector<ll> t;
    int N;
};

int query(BinaryIndexedTree &bit, int u) {
    int pos = upper_bound(ALL(b), u) - b.begin();
    return bit.get(pos);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m;
    FOR(i,1,n) {
        cin >> a[i];
        b.push_back(a[i]);
    }
    FOR(i,1,m) {
        cin >> ch[i] >> u[i] >> v[i];
        if (ch[i] == '!') b.push_back(v[i]);
    }
    sort(ALL(b));
    b.resize(unique(ALL(b)) - b.begin());

    BinaryIndexedTree bit(SZ(b));
    FOR(i,1,n) {
        int pos = lower_bound(ALL(b), a[i]) - b.begin() + 1;
        bit.update(pos, 1);
    }

    FOR(i,1,m)
        if (ch[i] == '!') {
            int pos = lower_bound(ALL(b), a[u[i]]) - b.begin() + 1;
            bit.update(pos, -1);
            a[u[i]] = v[i];
            pos = lower_bound(ALL(b), a[u[i]]) - b.begin() + 1;
            bit.update(pos, 1);
        } else {
            cout << query(bit, v[i]) - query(bit, u[i]-1) << "\n";
        }
    return 0;
}
