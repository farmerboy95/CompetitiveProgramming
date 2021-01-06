/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - https://codeforces.com/blog/entry/86464
        - During the first n/2 iterations, the number of people with more than k cards, increases.
        Find at least one such person.
        - Wait for sqrt(n) iterations. After this there is always a continuous segment of length
        sqrt(n) with elements > k. So we can split the array into blocks of size sqrt(n), ask one
        element from each block and find the one > k. Then we can use binary search to find p.
        In total we need 2 * sqrt(n) + log(n) queries.
*/

#include <bits/stdc++.h>
#define FI first
#define SE second
#define ALL(a) a.begin(),a.end()
#define SZ(a) int((a).size())
#define MS(s, n) memset(s, n, sizeof(s))
#define FOR(i,a,b) for (int i = (a); i <= (b); i++)
#define FORE(i,a,b) for (int i = (a); i >= (b); i--)
#define FORALL(it, a) for (__typeof((a).begin()) it = (a).begin(); it != (a).end(); it++)

using namespace std;
using ll = long long;
using ld = double;
using II = pair<int, int>;
using III = pair<II, int>;
using cd = complex<ld>;
using vcd = vector<cd>;

const ld EPS = 1e-9;
const ll MODBASE = 1000000007LL;
const int MAXN = 110;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, k;

int ask(int u) {
    cout << "? " << u << endl;
    int x;
    cin >> x;
    return x;
}

void guess(int u) {
    cout << "! " << u << endl;
}

void findP(int pos) {
    int l = pos+1, r = pos+n;
    while (l <= r) {
        int mid = (l + r) >> 1;
        int g = mid;
        if (g > n) g -= n;
        if (ask(g) > k) r = mid-1;
        else l = mid+1;
    }
    int res = r;
    while (res > n) res -= n;
    guess(res);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> k;
    FOR(i,1,320) ask(1);
    // there is one case that (n-1)/2 < sqrt(n), it's n = 4, so we deduct 1 from sqrt(n) to make it more precise.
    int block = int(sqrt(n))-1;
    for (int i = 1; i <= n; i += block) {
        int x = ask(i);
        if (x > k) {
            findP(i);
            return 0;
        }
    }
    return 0;
}