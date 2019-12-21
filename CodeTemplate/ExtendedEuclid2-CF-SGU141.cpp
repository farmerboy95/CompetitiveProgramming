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

ll X1, X2, P, K, x, y, d;

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
    cin >> X1 >> X2 >> P >> K;
    ll g = gcd(X1, X2);
    if (P % g) {
        cout << "NO";
        return 0;
    }
    X1 /= g;
    X2 /= g;
    P /= g;
    extendedEuclid(X1, X2);
    x *= P;
    y *= P;
    while (abs(x+X2)+abs(y-X1) < abs(x)+abs(y)) x+=X2,y-=X1;
    while (abs(x-X2)+abs(y+X1) < abs(x)+abs(y)) x-=X2,y+=X1;
    if (abs(x) + abs(y) > K) {
        cout << "NO";
        return 0;
    }
    ll n1 = 0, n2 = 0;
    ll last = K - abs(x) - abs(y);
    if (last % 2 == 0) {
        if (x < 0) n1 =- x, x = 0;
        if (y < 0) n2 =- y, y = 0;
        x += last/2; 
        n1 += last/2;
    }
    else {
        if ((X1 + X2) % 2 == 0) {
            cout << "NO";
            return 0;
        }
        if (abs(x+X2)+abs(y-X1) < abs(x-X2)+abs(y+X1)) x+=X2,y-=X1;
        else x-=X2,y+=X1;
        if (abs(x) + abs(y) > K) {
            cout << "NO";
            return 0;
        }
        last = K - abs(x) - abs(y);
        if (x < 0) n1 =- x, x = 0;
        if (y < 0) n2 =- y, y = 0;
        x += last/2; 
        n1 += last/2;
    }
    cout << "YES\n";
    cout << x << " " << n1 << " " << y << " " << n2;
    return 0;
}
