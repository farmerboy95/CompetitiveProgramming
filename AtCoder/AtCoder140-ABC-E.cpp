/*
    Author: Nguyen Tan Bao

    Idea: 
        - For each a[i], we count the number of times we can add a[i] to the result, call it num => res += num * a[i]
        - Let fiLeft = position of the first element which is larger than a[i] from i to the left of it
        - Let seLeft = position of the second element which is larger than a[i] from i to the left of it
        - Let fiRight = position of the first element which is larger than a[i] from i to the right of it
        - Let seRight = position of the second element which is larger than a[i] from i to the right of it
        - All those variables can be achieved using binary search and RMQ
        - We can add a[i] to the result if the segment has a[i] and a[fiLeft] (doesn't have a[fiRight])
        or the segment has a[i] and a[fiRight] (doesn't have a[fiLeft])
        - Count the number of such segments and add to the result
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
#define WHATIS(x) cout << #x << " is " << x << endl;
#define ERROR(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
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

void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
    cout << *it << " = " << a << endl;
    err(++it, args...);
}

const ll MODBASE = 1000000007LL;
const int MAXN = 100010;
const int MAXM = 200010;
const int MAXK = 110;
const int MAXQ = 200010;

int a[MAXN], n, M[MAXN][20];

void RMQ() {
    FOR(i,0,n+3) M[i][0] = a[i];
    for (int k = 1; (1<<k) <= n+3; k++)
        for (int i = 0; i + (1<<k) - 1 <= n+3; i++) M[i][k] = max(M[i][k-1], M[i+(1<<(k-1))][k-1]);
}

int get(int u, int v) {
    int k = log2(v - u + 1);
    return max(M[u][k], M[v-(1<<k)+1][k]);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);  
    cin >> n;
    FOR(i,2,n+1) cin >> a[i];
    a[0] = 10000000;
    a[1] = 1000000;
    a[n+2] = 1000000;
    a[n+3] = 10000000;
    RMQ();
    ll res = 0;
    FOR(i,2,n+1) {
        int dau = 0, cuoi = i-1, mid;
        while (dau <= cuoi) {
            mid = (dau + cuoi) / 2;
            if (get(mid, i) > a[i]) dau = mid+1;
            else cuoi = mid-1;
        }
        int fiLeft = cuoi;
        dau = 0, cuoi = fiLeft - 1;
        while (dau <= cuoi) {
            // cout << dau << ' ' << cuoi << endl;
            mid = (dau + cuoi) / 2;
            if (get(mid, fiLeft-1) > a[i]) dau = mid+1;
            else cuoi = mid-1;
        }
        int seLeft = cuoi;

        dau = i+1, cuoi = n+3, mid;
        while (dau <= cuoi) {
            mid = (dau + cuoi) / 2;
            if (get(i, mid) > a[i]) cuoi = mid-1;
            else dau = mid+1;
        }
        int fiRight = dau;
        dau = fiRight+1, cuoi = n+3;
        while (dau <= cuoi) {
            mid = (dau + cuoi) / 2;
            if (get(fiRight+1, mid) > a[i]) cuoi = mid-1;
            else dau = mid+1;
        }
        int seRight = dau;

        // cout << seLeft << ' ' << fiLeft << ' ' << fiRight << ' ' << seRight << endl;
        if (fiRight < n+2) {
            res += (ll) (i - fiLeft) * (seRight - fiRight) * a[i];
        }
        if (fiLeft > 1) {
            res += (ll) (fiRight - i) * (fiLeft - seLeft) * a[i];
        }
    }
    cout << res;
    return 0;
}
