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
typedef pair<II, ll> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;

void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
    cout << *it << " = " << a << endl;
    err(++it, args...);
}

const ll MODBASE = 1000000007LL;
const int MAXN = 110;
const int MAXM = 35;
const int MAXK = 510;
const int MAXQ = 200010;

int n, d[100010];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,0,n-1) d[i] = 1000000000;
    d[1] = 1;
    deque<int> q;
    q.push_front(1);
    while (!q.empty()) {
        int u = q.front();
        q.pop_front();
        if (d[(10 * u) % n] > d[u]) {
            d[(10 * u) % n] = d[u];
            q.push_front((10*u) % n);
        }
        if (d[(u + 1) % n] > d[u] + 1) {
            d[(u + 1) % n] = d[u] + 1;
            q.push_back((u+1) % n);
        }
    }
    cout << d[0];
    return 0;
}