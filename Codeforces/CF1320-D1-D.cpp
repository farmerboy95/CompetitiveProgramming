/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - "110" <-> "011" can reduce the transformation to: we can move a zero 2 steps to the left
        or right iff we have two 1s towards its direction.
        - Now consider a string with 0 and 1, let's assume that it has 5 zeroes, between each pair,
        there is a number of 1s. We can easily see that if we order those zeroes from 1 to 5, no
        matter what you do, the string at the end will maintain that order, because one zero cannot
        go pass another zero.
        - The second thing is that the parity of the number of 1s between 2 zeroes will be the same
        after operations, and the parity of the number of 1s before the first zero will also be the
        same.
        - So we come up with the following solution, the answer is Yes iff:
            + The two strings must have the same number of 0s (or 1s)
            + The parity of the number of 1s before the first zero of 2 strings must be the same.
            + For each string, we can create a list of number, which is parity of number of 1s between
            2 consecutive zeroes. 2 lists must be the same.
        - To compare 2 lists, we simply use a hash with a condition: number of 0 (or 1) of 2 lists should
        be the same.
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

int n, q, cnt0[MAXN], b[MAXN];
ll pw[MAXN], h[MAXN], c[MAXN];
vector<int> a;
string s;

int getX(int u) {
    int dau = 0, cuoi = SZ(a)-1;
    while (dau <= cuoi) {
        int mid = (dau + cuoi) >> 1;
        if (a[mid] >= u) cuoi = mid - 1;
        else dau = mid+1;
    }
    return dau;
}

int getY(int u) {
    int dau = 0, cuoi = SZ(a)-1;
    while (dau <= cuoi) {
        int mid = (dau + cuoi) >> 1;
        if (a[mid] <= u) dau = mid+1;
        else cuoi = mid-1;
    }
    return cuoi;
}

ll query(ll l, ll r) {
    if (!l) return h[r];
    return (h[r] - h[l-1] * pw[r-l+1] + MODBASE*MODBASE) % MODBASE; 
}

bool check(int X1, int Y1, int X2, int Y2) {
    // number of 1s from X1 to Y1 should be identical with that from X2 to Y2
    if (c[Y1] - c[X1-1] != c[Y2] - c[X2-1]) return false;
    // compare hashes
    return query(X1, Y1) == query(X2, Y2);
}

bool solve(int L1, int L2, int len) {
    int R1 = L1 + len - 1, R2 = L2 + len - 1;
    // number of 0s in 2 strings should be the same
    if (cnt0[R1] - cnt0[L1-1] != cnt0[R2] - cnt0[L2-1]) return false;
    // no 0s? simply return Yes
    if (cnt0[R1] - cnt0[L1-1] == 0) return true;
    // positions of first and last zero of in array "a"
    int X1 = getX(L1), Y1 = getY(R1), X2 = getX(L2), Y2 = getY(R2);
    // parity of number of 1s before the first zero
    if ((a[X1] - L1) % 2 != (a[X2] - L2) % 2) return false;
    // no more 0? simply return Yes
    if (cnt0[R1] - cnt0[L1-1] == 1) return true;
    X1++; X2++;
    return check(X1, Y1, X2, Y2);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    pw[0] = 1;
    FOR(i,1,n) pw[i] = pw[i-1] * 2 % MODBASE;
    cin >> s;
    s = " " + s;
    FOR(i,1,n) {
        cnt0[i] = cnt0[i-1] + (s[i] == '0');
        if (s[i] == '0') a.push_back(i);
    }
    FOR(i,1,SZ(a)-1) {
        // get the number of 1s between 2 zeroes
        b[i] = (a[i] - a[i-1] - 1) % 2;
        // count the number of 1s from 0 to i
        c[i] = c[i-1] + b[i];
    }
    // pre calc hash value from 0 to i
    h[0] = b[0];
    FOR(i,1,SZ(a)-1) h[i] = (h[i-1] * 2 + b[i]) % MODBASE;
    cin >> q;
    while (q--) {
        int L1, L2, len;
        cin >> L1 >> L2 >> len;
        if (solve(L1, L2, len)) cout << "Yes\n";
        else cout << "No\n";
    }
    return 0;
}
