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

struct Num {
    ll part1, part2;
    Num(ll part1 = 0, ll part2 = 0) {
        ll p = part2 / 100000;
        this->part2 = part2 % 100000;
        part1 += p;
        this->part1 = part1 % 100000;
    }
    Num operator* (const Num &b) {
        ll res = (100000LL * (part1 * b.part2 + part2 * b.part1) + part2 * b.part2) % 10000000000LL;
        return Num(res / 100000, res % 100000);
    }
    Num operator+ (const Num &b) {
        ll res = (part1 * 100000 + part2 + b.part1 * 100000 + b.part2) % 10000000000LL;
        return Num(res / 100000, res % 100000);
    }
    ll toNum() {
        return part1 * 100000LL + part2;
    }
};

int n;

Num mu(int a, int b) {
    if (b == 0) return Num(0, 1);
    if (b == 1) return Num(0, a);
    Num g = mu(a, b/2);
    if (b%2) return g*g*Num(0, a);
    return g*g;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    cin >> n;
    Num res(0, 0);
    FOR(i,1,n) {
        res = res + mu(i, i);
        //cout << res.part1 << res.part2 << endl;
    }
    cout << res.toNum();
    return 0;
}
