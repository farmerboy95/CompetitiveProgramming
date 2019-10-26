/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Factorize every init number
        - For example a number g = a^x * b^y * c^z ..., this number can be formed as e ^ k
        if and only if k is divisor of x, y, z...
        - So that each number can be factorize as mask a^(x%k) * b^(y%k) * c^(z%k)...
        - This mask need another mask (reverse mask) a^(k - x%k) * b^(k - y%k) * c^(k - z%k)...
        - The mask of each number is always smaller than or equal to that number itself
        => For each init number, find its reverse mask and add dem[reverse mask] to the final result,
        increase dem[mask] by 1 for next number to find.
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
const int MAXM = 7369000;
const int MAXK = 110;
const int MAXQ = 200010;

int nt[100010], a[MAXN], n, k, Max[100010], dem[100010];

void sieveBase(int n) {
    FOR(i,2,n) {
        if (nt[i] == 0) {
            nt[i] = i;
            for (ll j = (ll) i * i; j <= n; j += i) nt[j] = i;
        }
    }
}

ll mu(ll a, ll b) {
    if (b == 0) return 1;
    if (b == 1) return a;
    ll g = mu(a, b/2);
    if (b % 2) return g * g * a;
    return g*g;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    sieveBase(100000);
    // get max exponentation of each prime number that p^e <= 100000
    FOR(i,1,100000) {
        if (nt[i] == i) {
            ll w = i;
            int cnt = 1;
            while (w <= 100000) {
                w *= i;
                cnt++;
            }
            w /= i;
            cnt--;
            Max[i] = cnt;
        }
    }
    cin >> n >> k;
    FOR(i,1,n) cin >> a[i];
    ll res = 0;
    FOR(i,1,n) {
        int g = a[i];
        bool co = true;
        // need = reverse mask
        ll need = 1;
        // transf = normal mask
        ll transf = 1;
        while (g > 1) {
            int p = nt[g];
            int cnt = 0;
            while (g % p == 0) {
                cnt++;
                g /= p;
            }
            cnt %= k;
            transf *= mu(p, cnt);
            if (cnt == 0) continue;
            cnt = k - cnt;
            if (Max[p] < cnt) {
                co = false;
                break;
            }
            need *= mu(p, cnt);
            if (need > 100000) {
                co = false;
                break;
            }
        }
        if (!co) continue;
        res += dem[need];
        dem[int(transf)]++;
    }
    cout << res;
    return 0;
}