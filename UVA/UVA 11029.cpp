/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Trailing digits: get (a^b) % 1000 then print 3 digits
        - Leading digits: a^b = x * 10^y 
        <=> log10(a^b) = log10(x * 10^y) 
        <=> b * log10(a) = log10(x) + log10(10^y) = log10(x) + y;
        <=> log10(x) = b * log10(a) - y (y is integer part of log10(a^b))
        <=> x = 10 ^ (b * log10(a) - y)
        - Get 3 first digits of x, they are leading digits
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
const int MAXN = 410;
const int MAXM = 1010;
const int MAXK = 110;
const int MAXQ = 200010;

ll binPowMod(ll a, ll b, ll m) {
    a %= m;
    ll res = 1;
    while (b > 0) {
        if (b & 1LL) res = res * a % m;
        a = a * a % m;
        b >>= 1LL;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int a, b;
        cin >> a >> b;
        // trailing
        ll tr = binPowMod(a, b, 1000);
        // leading
        ld g = b * log10(a);
        g -= floor(g);
        ld x = pow(10, g);
        // print leading
        FOR(i,1,3) {
            int e = int(floor(x));
            cout << e;
            x -= e;
            x *= 10;
        }
        cout << "...";
        // print trailing
        vector<int> c;
        FOR(i,1,3) {
            c.emplace_back(tr % 10);
            tr /= 10;
        }
        FORE(i,2,0) cout << c[i];
        cout << endl;
    }
    return 0;
}
