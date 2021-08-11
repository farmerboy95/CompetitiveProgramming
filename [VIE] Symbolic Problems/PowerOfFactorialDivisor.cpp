/*
    Keywords: factorial, divisor, integer factorization
    Đề bài:
        - Cho 2 số n và k. Tìm số mũ lớn nhất x của k sao cho n! chia hết cho k^x
    Lời giải:
        - n! = 1 * 2 * 3 * 4 * ... * n
        - Khi k là số nguyên tố, res = n / k + n / k^2 + n / k^3 + ...
        - Khi k là hợp số, phân tích k ra thành các thừa số nguyên tố, với mỗi thừa số nguyên tố p (với 
        số mũ là t) thì tìm số mũ lớn nhất x của p trong n! như khi tính với số nguyên tố. Kết quả là
        min(x[i] / t[i])
    Nguồn: 
        - https://cp-algorithms.com/algebra/factorial-divisors.html
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
const int MAXN = 1000010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int nt[MAXN], n, k;

void sieveBase(int N) {
    FOR(i,2,N) {
        if (nt[i] == 0) {
            nt[i] = i;
            for (ll j = (ll) i * i; j <= n; j += i) nt[j] = i;
        }
    }
}

int factPow(int N, int K) {
    int res = 0;
    while (N) {
        N /= K;
        res += N;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> k;
    sieveBase(1000000);
    int K = k;
    map<int, int> ma;
    while (K > 1) {
        ma[nt[K]]++;
        K /= nt[K];
    }
    int res = 1e9;
    FORALL(it, ma) {
        int t = it->SE;
        int x = factPow(n, it->FI);
        res = min(res, x / t);
    } 
    cout << res;
    return 0;
}
