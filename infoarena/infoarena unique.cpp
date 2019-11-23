/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let l[i] is index of the nearest greater number than a[i] to the left of i
        - Let r[i] is index of the nearest greater number than a[i] to the right of i
        - We can use stack to calculate these 2 arrays

        - For each i, if (length from l[i]+1 to r[i]-1) >= a[i] then we can store this segment (at most n segments)
        - For each i from n to 1, we mark the appearance of a[i] and clear the appearance of previous a[i] using Fenwick tree,
        then our tree will contain only positions of different value of a[i]
        - Now we can query from right bound and compare result with max value of the segment we store
        - If they are equal, update the final result.
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
typedef pair<int, II> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;
 
const ll MODBASE = 1000000007LL;
const int MAXN = 100010;
const int MAXM = 30010;
const int MAXK = 16;
const int MAXQ = 200010;

int n, a[MAXN], tr[MAXN], pre[MAXN], l[MAXN], r[MAXN];
stack<int> s;
vector<II> b[MAXN];

int getLength(int l, int r) {
    return max(0, r-l+1);
}

void update(int u, int val) {
    while (u <= n+1) {
        tr[u] += val;
        u = u + (u & (-u));
    }
}

int get(int u) {
    int res = 0;
    while (u) {
        res += tr[u];
        u = u - (u & (-u));
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    freopen("unique.in", "r", stdin);
    freopen("unique.out", "w", stdout);
    int t;
    cin >> t;
    while (t--) {
        cin >> n;
        FOR(i,1,n) cin >> a[i];
        a[0] = a[n+1] = n+1;
        FOR(i,1,n) {
            pre[i] = n+1;
            b[i].clear();
        }
        MS(tr, 0);

        while (!s.empty()) s.pop();
        s.push(0);
        FOR(i,1,n) {
            while (!s.empty() && a[i] >= a[s.top()]) s.pop();
            l[i] = s.top();
            s.push(i);
        }

        while (!s.empty()) s.pop();
        s.push(n+1);
        FORE(i,n,1) {
            while (!s.empty() && a[i] >= a[s.top()]) s.pop();
            r[i] = s.top();
            s.push(i);
        }

        FOR(i,1,n) {
            if (getLength(l[i]+1, r[i]-1) < a[i]) continue;
            b[l[i]+1].emplace_back(II(r[i]-1, a[i])); // O(n) segments
        }

        int res = 0;
        FORE(i,n,1) {
            update(i, 1);
            update(pre[a[i]], -1);
            pre[a[i]] = i;

            // O(n) for each test
            FOR(j,0,SZ(b[i])-1)
                if (get(b[i][j].FI) == b[i][j].SE) res = max(res, getLength(i, b[i][j].FI));
        }
        cout << res << "\n";
    }
    return 0;
}
