// TLE submission
#include <bits/stdc++.h>
#define base 1000000007LL
#define ll long long
#define X first
#define Y second
#define ld double
#define EPS 1e-9
#define all(a) a.begin(),a.end()
#define sz(a) int((a).size())
#define ms(s, n) memset(s, n, sizeof(s))
#define FOR(i,a,b) for (int i = (a); i <= (b); i++)
#define FORE(i,a,b) for (int i = (a); i >= (b); i--)
#define FORALL(it, a) for (__typeof((a).begin()) it = (a).begin(); it != (a).end(); it++)
#define what_is(x) cout << #x << " is " << x << endl;
#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
//__builtin_ffs(x) return 1 + index of least significant 1-bit of x
//__builtin_clz(x) return number of leading zeros of x
//__builtin_ctz(x) return number of trailing zeros of x

using namespace std;
typedef pair<ll, ll> II;
typedef pair<ll, II> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;

void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
    cout << *it << " = " << a << endl;
    err(++it, args...);
}

string s, t;

struct HashModule {
    ll mod;
    vector<ll> pw, h;
    ll n;
    void init(string s, ll bas, ll p) {
        mod = p;
        n = sz(s);
        pw.resize(s.length()+1);
        h.resize(s.length());
        pw[0] = 1;
        FOR(i,1,sz(s)) pw[i] = (pw[i-1] * bas) % mod;
        h[0] = s[0]-'0';
        FOR(i,1,sz(s)-1) h[i] = (h[i-1]*bas + s[i]-'0') % mod;
    }
    ll query(ll l, ll r) {
        if (!l) return h[r];
        return (h[r] - h[l-1] * pw[r-l+1] + mod*mod) % mod; 
    }
};

struct DoubleHash {
    HashModule hm1, hm2;
    void init(string s, ll base1, ll mod1, ll base2, ll mod2) {
        hm1.init(s, base1, mod1);
        hm2.init(s, base2, mod2);
    }
    II query(ll l, ll r) {
        return II(hm1.query(l,r), hm2.query(l,r));
    } 
};

DoubleHash dhashsS, dhashsT;

bool isEquivalent(int l, int r, int u, int v) {
    if (dhashsS.query(l, r) == dhashsT.query(u, v)) return true;
    if ((r-l+1)%2) return false;
    int m = (l + r) >> 1;
    int k = (u + v) >> 1;
    if (isEquivalent(l, m, u, k) && isEquivalent(m+1, r, k+1, v)) return true;
    if (isEquivalent(l, m, k+1, v) && isEquivalent(m+1, r, u, k)) return true;
    return false;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    cin >> s >> t;
    dhashsS.init(s, 26, 1000000007, 26, 999999991);
    dhashsT.init(t, 26, 1000000007, 26, 999999991);
    if (isEquivalent(0,sz(s)-1,0,sz(t)-1)) cout << "YES";
    else cout << "NO";
    return 0; 
}