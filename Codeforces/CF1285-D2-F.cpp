/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: https://codeforces.com/blog/entry/72950
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
 
const ll MODBASE = 1000000007LL;
const int MAXN = 100010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, a[MAXN], u[MAXN], cnt[MAXN];
bool appear[MAXN];
vector<int> d[MAXN];

int coprime(int x) {
    int res = 0;
    FOR(i,0,SZ(d[x])-1) res += cnt[d[x][i]] * u[d[x][i]];
    return res;
}

void update(int x, int val) {
    FOR(i,0,SZ(d[x])-1) cnt[d[x][i]] += val;
}

int gcd(int a, int b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    // n * ln(n)
    FOR(i,1,100000) {
        for (int j = i; j <= 100000; j += i) d[j].emplace_back(i);
        if (i == 1) u[i] = 1;
        else if ((i / d[i][1]) % d[i][1] == 0) u[i] = 0;
        else u[i] = -u[i / d[i][1]];
    }

    cin >> n;
    ll res = 0;
    FOR(i,1,n) {
        cin >> a[i];
        appear[a[i]] = true;
        res = max(res, (ll) a[i]);
    }

    // each distinct number (i * g) will be triggered k times
    // k = number of divisor of (i * g) (max = 128)
    FOR(g,1,100000) {
        stack<int> s;
        FORE(i,100000/g,1) {
            if (!appear[i*g]) continue;
            // coprime(i) has the complexity of O(k)
            int c = coprime(i);
            while (c) {
                if (gcd(i, s.top()) == 1) {
                    res = max(res, (ll) g * i * s.top());
                    c--;
                }
                update(s.top(), -1);
                s.pop();
            }
            update(i, 1);
            s.push(i);
        }
        while (SZ(s)) {
            update(s.top(), -1);
            s.pop();
        }
    }

    cout << res;
    return 0;
}
