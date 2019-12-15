/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Consider a number x (odd), how many times x will be included in the list?
        - x will be included in these numbers [x, x*2, x*2+1, x*2*2, x*2*2+1, (x*2+1)*2, (x*2+1)*2+1...]
        => x will be in numbers which have prefix (in binary representation) is x and are smaller or equal to n
        - What about a even number y?
        - Along with the similar list as x, even number y may come from y+1, so that we will have one more list
        (list of y+1), we can calculate them separately.

        - As odd and even numbers have different attributes, we should consider a list of odd numbers and a list
        of even numbers from 1 to n
        - We can prove that the result of numbers in each list decrease when we come close to n
        => Binary search on each list
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
typedef pair<int, II> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;
 
const ll MODBASE = 1000000007LL;
const int MAXN = 200010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

ll n, k;

int getLength(ll u) {
    int cnt = 0;
    while (u) {
        u /= 2;
        cnt++;
    }
    return cnt;
}

ll calcOdd(ll u) {
    if (u > n) return 0;
    int a = getLength(n);
    int b = getLength(u);
    int x = a - b - 1;
    ll N = n;
    while (b != a) {
        a--;
        N /= 2;
    }
    // number of digits (in binary) of the main value must be smaller than number of digits of n
    if (u > N) return (1LL << (x+1)) - 1;
    // number of digits (in binary) of the main value must be smaller than or equal to number of digits of n
    else if (u < N) return (1LL << (x+2)) - 1;
    else {
        // extract the suffix of n (excluding the prefix) and add to the result
        a = getLength(n);
        while (b != a) {
            b++;
            u *= 2;
        }
        return (1LL << (x+1)) - 1 + n - u + 1;
    }
}

ll calcEven(ll u) {
    return calcOdd(u+1) + calcOdd(u);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> k;
    ll dau = 1, cuoi = n / 2 + n % 2, mid;
    ll res = 0;
    while (dau <= cuoi) {
        mid = (dau + cuoi) >> 1;
        if (calcOdd(mid * 2 - 1) >= k) dau = mid+1;
        else cuoi = mid-1;
    }
    if (cuoi >= 1 && cuoi <= n / 2 + n % 2 && calcOdd(cuoi * 2 - 1) >= k) res = max(res, cuoi * 2 - 1);
    dau = 1, cuoi = n / 2;
    while (dau <= cuoi) {
        mid = (dau + cuoi) >> 1;
        if (calcEven(mid * 2) >= k) dau = mid+1;
        else cuoi = mid-1;
    }
    if (cuoi >= 1 && cuoi <= n / 2 && calcEven(cuoi * 2) >= k) res = max(res, cuoi * 2);
    cout << res;
    return 0;
}
