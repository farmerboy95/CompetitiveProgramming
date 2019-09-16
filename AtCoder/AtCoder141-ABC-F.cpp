/*
    Author: Nguyen Tan Bao
    Status: AC after reading editorial
    Idea: https://codeforces.com/blog/entry/69809
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
const int MAXN = 100010;
const int MAXM = 200010;
const int MAXK = 110;
const int MAXQ = 200010;


const int LOG_A = 60;
int n;
ll a[MAXN], basis[LOG_A];

void insertVector(ll mask) {
    FORE(i,LOG_A-1,0) {
        if (!(mask & (1LL << i))) continue;
        if (!basis[i]) {
            basis[i] = mask;
            return;
        }
        mask ^= basis[i];
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n) cin >> a[i];
    
    ll xorSum = 0;
    FOR(i,1,n) xorSum ^= a[i];

    // remove all 1-bit in xorSum from a[]
    FORE(i,LOG_A-1,0)
        if (xorSum & (1LL << i)) {
            FOR(j,1,n)
                if (a[j] & (1LL << i)) a[j] -= (1LL << i);
        }

    // insert vector and calculate max xor subset using this technique
    // https://codeforces.com/blog/entry/68953
    FOR(i,1,n) insertVector(a[i]);

    ll maxXor = 0;
    FORE(i,LOG_A-1,0) {
        if (!basis[i]) continue;
        if (maxXor & (1LL << i)) continue;
        maxXor ^= basis[i];
    }
    cout << maxXor + (xorSum ^ maxXor);
    return 0;
}
