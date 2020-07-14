/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - For each door, calculate the first door to its left having higher difficulty, and the first 
        door to its right having higher difficulty. For simplicity, a door with infinite difficulty is 
        added at either end. This part is done by monotonic stack in O(N). Then construct a sparse table 
        for range maximum query in O(NlogN).
        - In each query, on the Kth day, there will be K−1 opened doors. Some are to the left of the Sth 
        room, while some are to the right. If there are x opened doors to the left of the Sth on a specific 
        day, there needs to be at least f(x) opened doors to the right, so that the difficulty of the (f(x)+1)-th 
        door to the right is higher than the highest difficulty among the x doors to the left. An observation 
        is that f(x) non-decreases when x increases. So the suitable x can be found via binary search that number
        of rooms is larger than or equal to k.
        - More comments in the code.
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

int t, n, d[MAXN], q, M[MAXN][20], l[MAXN], r[MAXN];
stack<int> s;

void RMQ() {
    FOR(i,0,n) M[i][0] = i;
    for (int k = 1; (1<<k) <= n; k++)
        for (int i = 0; i + (1<<k) - 1 <= n; i++) {
            if (i+(1<<(k-1)) > n) M[i][k] = M[i][k-1];
            else if (d[M[i][k-1]] > d[M[i+(1<<(k-1))][k-1]]) M[i][k] = M[i][k-1];
            else M[i][k] = M[i+(1<<(k-1))][k-1];
        }
}

int getMax(int u, int v) {
    int k = int(log2(v - u + 1));
    return (d[M[u][k]] > d[M[v-(1<<k)+1][k]] ? M[u][k] : M[v-(1<<k)+1][k]);
}

int check(int s, int u) {
    int pos = s-u;
    if (u == 0) {
        int posRight = r[s-1];
        // first room is s, last room is posRight
        return posRight - (s-1);
    }
    int L = getMax(pos, s-1);
    int R = r[L];
    // first room is pos, last room is R
    return R - (pos - 1);
}

int solve(int s, int k) {
    int dau = 0, cuoi = s-1;
    while (dau <= cuoi) {
        int mid = (dau + cuoi) >> 1;
        if (check(s, mid) >= k) cuoi = mid-1;
        else dau = mid+1;
    }
    // p is the x that we want to consider
    int p = dau;
    // some corner cases
    // p == 0, we simply go to the right
    if (p == 0) return s + k - 1;
    // p == s
    // this is a case when check(s, s-1) < k, so we call "remain" as the number of unvisited room, including
    // the result. Then if the hardest lock is to the left of s, it means the unvisited rooms are to the left
    // of s, simply trace from the last unvisited room (would be 1), otherwise, the last unvisited room 
    // would be n
    if (p == s) {
        int L = getMax(1, s-1);
        int R = getMax(s, n-1);
        int remain = n - k + 1;
        if (d[L] > d[R]) return remain;
        return n - remain + 1;
    }
    // generally, get "remain" and consider the position of the hardest lock in the range from s-p to R-1
    int remain = check(s, p) - k + 1;
    int pos = s-p;
    int L = getMax(pos, s-1);
    int R = r[L];

    int posMax = getMax(pos, R-1);
    if (posMax >= s) {
        // if the hardest lock is to the right of s, the leftmost room would be visited first, then it would
        // visit "diff" rooms from R-diff+1 to R
        int diff = check(s, p) - check(s, p-1);
        if (remain == diff) return pos;
        return R - remain + 1;
    } else {
        // if the hardest lock is to the left of s, it means the last room would be pos, otherwise,
        // it should be the rightmost room counting to the left
        if (remain == 1) return pos;
        remain--;
        return R - remain + 1;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> t;
    FOR(o,1,t) {
        cout << "Case #" << o << ": ";

        cin >> n >> q;
        FOR(i,1,n-1) cin >> d[i];
        d[n] = d[0] = 1000000;

        RMQ();
        while (SZ(s)) s.pop();
        FOR(i,0,n) {
            l[i] = -1;
            while (SZ(s) && d[s.top()] < d[i]) s.pop();
            if (SZ(s)) l[i] = s.top();
            s.push(i);
        }
        while (SZ(s)) s.pop();
        FORE(i,n,0) {
            r[i] = n+1;
            while (SZ(s) && d[s.top()] < d[i]) s.pop();
            if (SZ(s)) r[i] = s.top();
            s.push(i);
        }

        while (q--) {
            int u, v;
            cin >> u >> v;
            cout << solve(u, v) << " ";
        }
        cout << "\n";
    }
    return 0;
}
