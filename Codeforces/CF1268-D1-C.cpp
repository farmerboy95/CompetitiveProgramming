/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - We consider each number from 1 to n, one by one
        - For example, we have number from 1 to k, each number in one position. We consider
        them from left to right (p1, p2, p3, ..., pk)
        - Easily see that we should focus them on the median of this sequence
        - Let the median is px, consider p[i] to the right of px, number of moves required
        to move p[x+1] to p[n] to be on the right of px is 
            + R = sum(p[x+1] to p[n]) - (x+1 + x+2 + ... + n) - (n - (x+1) + 1) * px
        - Similarly, consider p[i] to the left of px
            + L = (i-1) * px - (1 + 2 + ... + i-1) - sum(p[1] to p[x-1])
        - Now all the numbers needed are close together but they are not in order yet
        => Result = L + R + number of inversion of the sequence
        - Easily find out L, R and number of inversion using Fenwick Tree
*/
 
#include "bits/stdc++.h"
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
typedef pair<II, ll> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;
 
const ll MODBASE = 1000000007LL;
const int MAXN = 200010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, a[MAXN], pos[MAXN], t[MAXN];
ll s[MAXN];

void update(int u, int gt, int val) {
    while (u <= n) {
        t[u] += gt;
        s[u] += val;
        u = u + (u & (-u));
    }
}

int count(int u) {
    int res = 0;
    while (u) {
        res += t[u];
        u = u - (u & (-u));
    }
    return res;
}

ll getSum(int u) {
    ll res = 0;
    while (u) {
        res += s[u];
        u = u - (u & (-u));
    }
    return res;
}

ll calc(ll u) {
    return u * (u+1) / 2;
}
 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n) {
        cin >> a[i];
        pos[a[i]] = i;
    }
    ll cntInv = 0;
    int now = 0;
    ll sumPos = 0;
    FOR(i,1,n) {
        int addInv = now - count(pos[i]-1);
        update(pos[i], 1, pos[i]);
        sumPos += pos[i];
        cntInv += addInv;
        now++;

        int dau = 1, cuoi = n;
        while (dau <= cuoi) {
            int mid = (dau + cuoi) >> 1;
            if (count(mid-1) > now/2) cuoi = mid-1;
            else dau = mid+1;
        }
        int x = cuoi;

        ll sumLeft = getSum(x-1), sumRight = sumPos - getSum(x);
        ll res = sumRight - sumLeft;
        int v = now / 2, u = now - v - 1;
        res -= (ll) x * (u-v);
        res += cntInv - calc(u) - calc(v);
        cout << res << " ";
    }
    return 0;
}
