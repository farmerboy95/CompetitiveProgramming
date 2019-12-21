// https://en.wikipedia.org/wiki/Gambler%27s_ruin
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
typedef complex<ld> cd;
typedef vector<cd> vcd;

void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
    cout << *it << " = " << a << endl;
    err(++it, args...);
}

int ev1, ev2, at, d;

ld solve(int num1, int num2) {
    if (at == 3) return 1.0 * num1 / (num1 + num2);
    ld p = at / 6.0;
    p = p / (1-p);
    return 1 - (1-pow(p, num2)) / (1-pow(p, num1+num2));
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    cin >> ev1 >> ev2 >> at >> d;
    while (ev1 + ev2 + at + d) {
        int num1 = ev1 / d + (ev1 % d > 0);
        int num2 = ev2 / d + (ev2 % d > 0);

        cout << fixed << setprecision(1) << solve(num1, num2)*100 << endl;
        
        cin >> ev1 >> ev2 >> at >> d;
    }
    return 0; 
}
