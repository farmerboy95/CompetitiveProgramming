#include <bits/stdc++.h>
#define base 1000000007LL
#define ll long long
#define X first
#define Y second
#define ld double
#define pb push_back
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
typedef pair<int, int> II;
typedef pair<ll, II> III;

void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
	cout << *it << " = " << a << endl;
	err(++it, args...);
}

ll a, b, c, l1, r1, l2, r2;

ll x, y, d;

void extendedEuclid(ll a, ll b) {
    if (b == 0) { 
        x = 1; 
        y = 0; 
        d = a; 
        return; 
    } 
    extendedEuclid(b, a % b);
    ll X1 = y;
    ll Y1 = x - (a / b) * y;
    x = X1;
    y = Y1;
}

ll gcd(ll a, ll b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    cin >> a >> b >> c;
    cin >> l1 >> r1;
    cin >> l2 >> r2;
    c = -c;
    if (c < 0) {
        a = -a;
        b = -b;
        c = -c;
    }
    if (a < 0) {
        a = -a;
        swap(l1, r1);
        l1 = -l1;
        r1 = -r1;
    }
    if (b < 0) {
        b = -b;
        swap(l2, r2);
        l2 = -l2;
        r2 = -r2;
    }
    if (l1 > r1 || l2 > r2) {
        cout << 0;
        return 0;
    }
    if (a == 0 && b == 0) {
        if (c == 0) cout << (r1-l1+1) * (r2-l2+1);
        else cout << 0;
    }
    else if (a == 0) {
        if (c % b) cout << 0;
        else if (-c / b <= r2 && -c / b >= l2) cout << r1-l1+1;
        else cout << 0; 
    }
    else if (b == 0) {
        if (c % a) cout << 0;
        else if (-c / a <= r1 && -c / a >= l1) cout << r2-l2+1;
        else cout << 0; 
    }
    else {
        ll g = gcd(a,b);
        if (c % g) {
            cout << 0;
            return 0;
        }
        a /= g;
        b /= g;
        c /= g;
        extendedEuclid(a, b);
        x *= c;
        y *= c;
        ll u1 = (ll) ceil(1.0*(l1-x)/b);
        ll v1 = (ll) floor(1.0*(r1-x)/b);
        ll u2 = (ll) ceil(1.0*(y-r2)/a);
        ll v2 = (ll) floor(1.0*(y-l2)/a);
        ll r = min(v1,v2), l = max(u1,u2);
        cout << max(0LL, r-l+1);
    }
    return 0;
}
