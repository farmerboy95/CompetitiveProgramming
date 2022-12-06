/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - https://codeforces.com/blog/entry/68953, problem 1
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

const int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67};
int n, mask[75];
int cnt[75][2], dp[75][600000];

ll add(ll a, ll b) {
    return (a + b) % MODBASE;
}

ll sub(ll a, ll b) {
    return (a - b + MODBASE) % MODBASE;
}

ll mul(ll a, ll b) {
    return a * b % MODBASE;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,70) cnt[i][0] = 1;
    FOR(i,1,n) {
        int u;
        cin >> u;

        int tmp = cnt[u][0];
        cnt[u][0] = add(cnt[u][0], cnt[u][1]);
        cnt[u][1] = add(cnt[u][1], tmp);
    }
    FOR(i,1,70) {
        int k = i;
        FOR(j,0,18) {
            int cnt = 0;
            while (k % primes[j] == 0) {
                k /= primes[j];
                cnt++;
            }
            cnt %= 2;
            if (cnt) mask[i] ^= (1<<j);
        }
    }

    dp[0][0] = 1;
    FOR(i,1,70) {
        FOR(m,0,(1<<19)-1) {
            dp[i][m] = add(mul(dp[i-1][m], cnt[i][0]), mul(dp[i-1][m ^ mask[i]], cnt[i][1]));
        }
    }
    cout << sub(dp[70][0], 1);
    return 0;
}
