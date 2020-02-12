/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Based on the greedy solution in editorial
        https://www.topcoder.com/tc?module=Static&d1=match_editorials&d2=srm314
        - There is a solution related to integer programming (using pruning technique) but
        I did not find anything after reading some lectures and articles
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
const int MAXN = 110;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

class MonthlyPayment {
    public:
    ll parse(string s) {
        stringstream sin(s);
        ll n;
        sin >> n;
        return n;
    }

    ll minimalPayment(string totalSMS, string pack1, string pay1, string pack2, string pay2) {
        ll total = parse(totalSMS);
        ll n1 = parse(pack1), p1 = parse(pay1);
        ll n2 = parse(pack2), p2 = parse(pay2);

        ll res = total * 10;

        FOR(x,0,1) {
            FOR(i,0,1000000) {
                ll remain = total - i * n1;
                if (remain < 0) {
                    res = min(res, i * p1);
                    break;
                }
                res = min(res, i * p1 + remain * 10);
                res = min(res, i * p1 + remain / n2 * p2 + remain % n2 * 10);
                res = min(res, i * p1 + (remain / n2 + 1) * p2);
            }
            swap(n1, n2);
            swap(p1, p2);
        }
        return res;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    MonthlyPayment s;
    cout << s.minimalPayment("92", "10", "90", "20", "170") << endl;
    cout << s.minimalPayment("90", "10", "90", "20", "170") << endl;
    cout << s.minimalPayment("99","10","90","20","170") << endl;
    cout << s.minimalPayment("10","1","11","20","300") << endl;
    cout << s.minimalPayment("0","10","80","50","400") << endl;
    cout << s.minimalPayment("28","1","10","1","8") << endl;
    cout << s.minimalPayment("450702146848","63791","433956","115281","666125") << endl;
    cout << s.minimalPayment("45","6","12","7","14") << endl;
    return 0;
}
