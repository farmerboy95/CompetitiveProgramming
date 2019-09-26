/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - All a[i] are distinct, this helps a lot in making us not to think about hard cases like a[i] 
        connects with a[j] (a[j] != a[i]) and a[j] connects with a[k] (a[k] == a[i])
        - a^2 + b^2 = c^2  <=>  a^2 = c^2 - b^2  <=>  a^2 = (c-b) * (c+b) = g * h  =>  c = (g+h) / 2 and b = h-c,
        g, h, a should have the same parity
        - For each a[i], try to integer factorize it.
        - But notice that a, b, c should be pairwise coprime => There are several cases:
            1. a[i] = 1 => ignore, clearly (actually 1 coprimes with 0 and 1^2 + 0^2 = 1^2, 
            but we don't have 0 in the list and we have at most one 1)
            2. a[i] = 2^1 * 3^x * 5^y .... => ignore, because g, h would be odd
            3. a[i] = 2^u * 3^x * 5^y .... => there would be 2^e triples (e = number of distinct primes of integer factorization of a[i] - 1)
            4. a[i] = 3^x * 5^y * 7^z .... => there would be 2^e triples (e = number of distinct primes of integer factorization of a[i] - 1)
        - How to create triples?
            3. a[i]^2 = 2^2u * 3^2x * 5^2y ...., g,h,a should have the same parity, then g and h should have at least one 2
            then we have 2^(2u-2) * 3^2x * 5^2y ...., for each distinct prime p, we should put the whole p^2x into g or h
            because a,b,c would not be pairwise coprime if we don't do that.
            4. a[i]^2 = 3^2x * 5^2y * 7^2z ...., for each distinct prime p, put the whole p^2x into g or h
        - Then use dsu to group triples, then simply count number of connected components.
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
const int MAXN = 1000010;
const int MAXM = 10000010;
const int MAXK = 110;
const int MAXQ = 200010;

int n, nt[MAXM], a[MAXN], res, lab[MAXN];
map<int, int> ma;
vector<ll> b;

void sieveBase(int n) {
    FOR(i,2,n) {
        if (nt[i] == 0) {
            nt[i] = i;
            for (ll j = (ll) i * i; j <= n; j += i) nt[j] = i;
        }
    }
}

int getRoot(int u) {
    while (lab[u] > 0) u = lab[u];
    return u;
}

void unionFind(int u, int v) {
    int x = lab[u] + lab[v];
    if (lab[u] < lab[v]) {
        lab[v] = u;
        lab[u] = x;
    }
    else {
        lab[u] = v;
        lab[v] = x;
    }
}

void integerFactorization(int p) {
    b.clear();
    while (p > 1) {
        int h = nt[p];
        int w = 1;
        while (p % h == 0) {
            p /= h;
            w *= h;
        }
        // remember to get p^2x, not p^x only
        b.emplace_back((ll) w * w);
    }
}

void solve(int pos, ll lef, ll rig, int a) {
    if (pos >= SZ(b)) {
        ll g = lef + rig;
        ll c = g / 2;
        ll b = max(lef, rig) - c;
        // create connections using dsu
        if (b <= 10000000 && ma.count(int(b))) {
            int u = getRoot(ma[a]);
            int v = getRoot(ma[int(b)]);
            if (u != v) unionFind(u, v);
        }
        if (c <= 10000000 && ma.count(int(c))) {
            int u = getRoot(ma[a]);
            int v = getRoot(ma[int(c)]);
            if (u != v) unionFind(u, v);
        }
        return;
    }
    // put the whole p^2x into one group
    lef *= b[pos];
    solve(pos+1, lef, rig, a);
    lef /= b[pos];
    rig *= b[pos];
    solve(pos+1, lef, rig, a);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    sieveBase(10000000);
    cin >> n;
    FOR(i,1,n) {
        cin >> a[i];
        ma[a[i]] = i;
    }
    FOR(i,1,n) lab[i] = -1;

    FOR(i,1,n)
        // case 1
        if (a[i] == 1) continue;
        // case 4
        else if (a[i] % 2) {
            integerFactorization(a[i]);
            // 2 groups
            ll lef = b[0];
            ll rig = 1;
            solve(1, lef, rig, a[i]);
        }
        else {
            // case 3
            if (a[i] % 4 == 0) {
                integerFactorization(a[i]);
                FOR(j,0,SZ(b)-1)
                    if (b[j] % 2 == 0) {
                        if (j != 0) swap(b[j], b[0]);
                        break;
                    }
                // 2 groups
                ll lef = b[0] / 2;
                ll rig = 2;
                solve(1, lef, rig, a[i]);
            }
            // case 2
            else {
                continue;
            }
        }

    FOR(i,1,n) res += (lab[i] < 0);
    cout << res;
    return 0;
}