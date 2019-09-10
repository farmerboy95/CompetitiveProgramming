/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - N! = l + (l + 1) + (l + 2) + ... + r (l < r) => N! = r*(r+1)/2 - l*(l-1)/2 => 2 * N! = (r-l+1) * (r+l)
        Let x = r-l+1, y = r+l => 2 * N! = x * y
        => r = (y+x-1) / 2, l = (y-x+1) / 2   (l < r and 1 < x < y)
        => x and y must have different parity (x odd, y even or vice versa)
        => Find all odd and even primes in N! factorization
        => Divide odd primes to 2 parts and put all even primes to 1 parts to create odd and even parts
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
const int MAXN = 2010;
const int MAXM = 200010;
const int MAXK = 110;
const int MAXQ = 200010;

int nt[100000010], test, n;
ll m;
vector<int> primes;

void sieveBase(int n) {
    FOR(i,2,n) {
        if (nt[i] == 0) {
            nt[i] = i;
            primes.emplace_back(i);
            for (ll j = (ll) i * i; j <= n; j += i) nt[j] = i;
        }
    }
}

ll binPowMod(ll a, ll b, ll m) {
    a %= m;
    ll res = 1;
    while (b > 0) {
        if (b & 1LL) res = res * a % m;
        a = a * a % m;
        b >>= 1LL;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    // get all primes under 10^8
    sieveBase(100000000);
    cin >> test;
    while (test--) {
        cin >> n >> m;
        ll res = 1;
        FOR(i,0,SZ(primes)-1) {
            int p = primes[i];
            if (p > n) break;
            int cnt = 0;
            if (i == 0) {
                // don't care about 2
                continue;
            }
            else {
                // is prime is larger than sqrt(n), the power of prime p in N! factorization is N / p
                // and this value <= sqrt(n), so that we use binary search to get all primes that has power = N / p
                // so that the whole for loop would take O(sqrt(n) * log(numOfPrimes))
                if ((ll) p * p > n) {
                    int dau = i, cuoi = SZ(primes)-1;
                    while (dau <= cuoi) {
                        int mid = (dau + cuoi) / 2;
                        if (n / primes[mid] != n / p) cuoi = mid-1;
                        else dau = mid+1;
                    }
                    // cout << p << ' ' << cuoi - i + 1 << endl;
                    int numOfSameExp = cuoi - i + 1;
                    res = res * binPowMod(n / p + 1, numOfSameExp, m) % m;
                    i = cuoi;
                }
                else {
                    // if prime is smaller than sqrt(n), use lagrange's theorem to get the power of prime in N! factorization
                    int N = n;
                    while (N) {
                        cnt += N / p;
                        N /= p;
                    }
                    res = res * (cnt + 1) % m;
                }
            }
        }
        // by right we should multiple the result by 2 because we put all 2s into one of the parts
        // but then we have to divide result by 2 because x < y
        // then minus 1 because when x = 1 => l = r, should eliminate this case
        res = (res - 1 + m) % m;
        cout << res << "\n";
    }
    return 0;
}
