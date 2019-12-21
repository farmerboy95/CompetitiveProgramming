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

int x, y, d, n, a0, b0;
vector<II> res;

void extendedEuclid(int a, int b) {
    if (b == 0) { 
        x = 1; 
        y = 0; 
        d = a; 
        return; 
    } 
    extendedEuclid(b, a % b);
    int X1 = y;
    int Y1 = x - (a / b) * y;
    x = X1;
    y = Y1;
}

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a%b);
}

void linear(int A, int a, int b, int c) {
    extendedEuclid(a, c);
    if (b % d) return;
    x = x * (b/d);
    int mod = c / d;
    x = (x % mod + mod) % mod;
    while (x < n) {
        res.pb(II(A, x));
        x += mod;
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    cin >> n >> a0 >> b0;
    ll g = gcd(gcd(a0, b0), n);
    n /= g, a0 /= g, b0 /= g;
    FOR(i,0,n-1) linear(i, a0, i*b0%n, n);
    cout << sz(res) << "\n";
    FOR(i,0,sz(res)-1) cout << res[i].X*g << " " << res[i].Y*g << endl;
    return 0;
}
