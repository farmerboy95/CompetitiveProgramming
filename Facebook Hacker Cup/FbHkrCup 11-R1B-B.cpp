/*
    Author: Nguyen Tan Bao
    Statement: https://www.facebook.com/codingcompetitions/hacker-cup/2011/round-1b/problems/B
    Status: AC
    Idea:
        - The same as this: https://cp-algorithms.com/others/josephus_problem.html
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

// only if k is a lot smaller than n
// 0-indexed, there are n persons from 0 to n-1, delete the k-th one
ll josephus(ll n, ll k) {
    // corner cases
    if (n == 1) return 0;
    if (k == 1) return n-1;
    // if k > n, use O(n) solution
    if (n < k) return (josephus(n-1, k) + k) % n;
    
    // Let's look at how the iterations go with n=10, k=3:
    // 0 1 2 3 4 5 6 7 8 9    n=10,k=3
    // 1 2   3 4   5 6   0    n=7,k=3
    // We aim to remove elim = n / k elements, we get the result of (n-elim, k) first.
    // After removing n/k elements, we start at number (floor(n/k) * k), the distance between 
    // it and 0 in the first array is (n % k) this is why we have to move back (n % k) steps 
    // in our result. If we move back and it is moved to the end of the array, we simply add n to
    // it. Otherwise, we have several areas in the second array, length of them are all (k-1).
    // It's time to move the result forward based on the number of spaces behind our real result
    // It's (current result / (k-1))

    ll elim = n / k;
    ll res = josephus(n - elim, k);
    res -= n % k;
    if (res < 0) res += n;
    else res += res / (k - 1);
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int t;
    ll n, k;
    cin >> t;
    FOR(o,1,t) {
        cout << "Case #" << o << ": ";
        cin >> n >> k;
        k++;
        cout << josephus(n, k) + 1 << "\n";
    }
    return 0;
}
