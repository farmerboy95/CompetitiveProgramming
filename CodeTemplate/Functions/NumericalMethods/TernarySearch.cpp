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
typedef pair<ll, II> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;

void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
    cout << *it << " = " << a << endl;
    err(++it, args...);
}

int calc(ll a) {
    // return something
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int LL = 0;
    int RR = 1e9;
    int ML = (LL + LL + RR) / 3;
    int MR = (LL + RR + RR) / 3;
    while ((LL != ML) && (ML != MR) && (MR != RR)) {
        if (calc(ML) > calc(MR)) LL = ML;
        else RR = MR;
        ML = (LL + LL + RR) / 3;
        MR = (LL + RR + RR) / 3;
    }
    FOR(i,ML,MR) calc(i);
    return 0;
}
