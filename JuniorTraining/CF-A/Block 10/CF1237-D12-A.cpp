/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
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
const int MAXM = 1010;
const int MAXK = 110;
const int MAXQ = 200010;

int n, a[MAXN], b[MAXN], c[MAXN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n) {
        cin >> a[i];
        b[i] = a[i] / 2;
        if (a[i] % 2) c[i] = 1;
    }
    int pos = 0, neg = 0;
    FOR(i,1,n)
        if (a[i] < 0) neg += -b[i];
        else pos += b[i];
    while (neg < pos) {
        FOR(i,1,n)
            if (a[i] < 0 && c[i]) {
                b[i]--;
                neg++;
                if (pos == neg) break;
            }
    }
    if (pos < neg) {
        FOR(i,1,n)
            if (a[i] >= 0 && c[i]) {
                b[i]++;
                pos++;
                if (pos == neg) break;
            }
    }
    FOR(i,1,n) cout << b[i] << "\n";
    return 0;
}