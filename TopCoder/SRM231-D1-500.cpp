/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let k = min(k, n-k)
        - Our formula is sum(i=1 -> k) (nCi / 2^(n-1))
        - Let's use logarithm on this problem (log10)
        - So we fix one i, and calculate nCi / 2^(n-1)
        - log10(nCi / 2^(n-1)) = log10(nCi) - log10(2^(n-1))
                               = log10(n! / (n-i)! / i!) - (n-1) * log10(2)
                               = log10(n!) - log10((n-i)!) - log10(i!) - (n-1) * log10(2)
        - But log10(n!) = log10((n-1)!) + log10(n) => Can be precompute in O(n)
        - After calculating x = log10(nCi / 2^(n-1)) => nCi / 2^(n-1) = 10^x
        - Remember to handle special case when k*2 == n => result = 100.0%
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
using ld = long double;
typedef pair<int, int> II;
typedef pair<II, int> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;

const ll MODBASE = 1000000007LL;
const int MAXN = 1000010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

ld logFact[MAXN];

class LargeSignTest {
    public:
    string pvalue(int n, int k) {
        if (k * 2 == n) return "100.0%";
        ld res = 0;
        ld log2 = log10l(2);
        k = min(k, n-k);
        FOR(i,1,n) logFact[i] = logFact[i-1] + log10l(i);

        FOR(i,0,k) {
            ld x = logFact[n] - logFact[n-i] - logFact[i] - (n-1) * log2;
            res += powl(10, x);
        }

        string kq = "";
        res *= 1000;
        int p = int(res + 0.5);

        kq += "%";
        kq += char(p % 10 + '0');
        kq += ".";
        p /= 10;
        FOR(i,1,3) {
            if (i > 1 && p == 0) break;
            kq += char(p % 10 + '0');
            p /= 10;
        }
        reverse(ALL(kq));
        return kq;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    LargeSignTest s;
    cout << s.pvalue(5, 4) << endl;
    cout << s.pvalue(10, 5) << endl;
    cout << s.pvalue(1000000, 400000) << endl;
    cout << s.pvalue(20, 5) << endl;
    return 0;
}
