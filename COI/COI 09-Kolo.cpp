/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Simulate the game but not all nodes, only 3 nodes needed
        - Get the position of A at the end of the game using goForward(pos) function
        - Get the right and left position of A after the game and find the positions of those nodes
        at the beginning of the game using goBackward(pos)
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
const int MAXN = 5010;
const int MAXM = 7369000;
const int MAXK = 110;
const int MAXQ = 200010;

bool nt[MAXM + 10];
vector<int> primes;
int n, k, A;

void sieveBase(int n) {
    FOR(i,2,n) {
        if (nt[i] == false) {
            primes.emplace_back(i);
            nt[i] = true;
            for (ll j = (ll) i * i; j <= n; j += i) nt[j] = true;
        }
    }
}

int goForward(int pos) {
    FOR(o,0,k-1) {
        if (pos == 0) {
            pos = (pos + primes[o]) % n;
        }
        else {
            int p = int((ll) primes[o] % ((ll) n * (n-1)));
            int e = p / (n - 1);
            if (p % (n - 1) >= pos) e++;
            pos = (pos - e + n) % n;
        }
    }
    return pos;
}

int goBackward(int pos) {
    FORE(o,k-1,0) {
        if (primes[o] % n == pos) {
            pos = 0;
        }
        else {
            int p = int((ll) primes[o] % ((ll) n * (n-1)));
            int e = p / (n - 1);
            pos = (pos + e) % n;
            if (p % (n - 1) > pos) pos = (pos + 1) % n;
        }
    }
    return pos;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    sieveBase(MAXM);
    cin >> n >> k >> A;
    int pos = goForward(A-1);
    int g = goBackward((pos + 1) % n);
    int h = goBackward((pos - 1 + n) % n);
    cout << g+1 << ' ' << h+1;
    return 0;
}
