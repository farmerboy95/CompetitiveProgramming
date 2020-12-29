/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - There are some observations here:
            + We always connect white nodes of the tree with the middle node of the chain, clearly,
            to make the tree shorter.
            + We always connect the highest white node (the one with the lowest depth) with the new
            chain.
            + Using the longer chain first is always better.
        - So we sort the chain in the decreasing order of the length and binary search the result. 
        We can maintain a prefix sum of the number of white nodes at depths, then just connect
        nodes of that depth to new chain and add values to the prefix sum. It would have 1 of 2
        patterns: 2 2 2 2 2 or 2 2 2 2 1, prefix sum will make this easier as we only change 2 (or 3)
        values.
        - When the number of current white nodes >= k, we can tell that it's possibly our answer.
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

int n, k, a[MAXN], prefixSum[MAXN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> k;
    FOR(i,1,n) cin >> a[i];
    sort(a+1, a+n+1);
    reverse(a+1, a+n+1);

    int dau = 0, cuoi = 1000000;
    while (dau <= cuoi) {
        int mid = (dau + cuoi) >> 1;
        MS(prefixSum, 0);
        bool co = false;

        prefixSum[0] = 1; prefixSum[1] = -1;
        ll white = 1;
        ll whiteAtDepth = 0;
        int ptr = 1;

        if (white >= k) co = true;
        FOR(i,0,mid) {
            whiteAtDepth += prefixSum[i];
            ll x = whiteAtDepth;

            while (x) {
                if (ptr > n) break;

                white--;
                x--;

                int l = i+2, r = i+2 + (a[ptr] - 1) / 2 - 1;
                if (l <= mid) white += (min(r, mid) - l + 1) * 2;

                prefixSum[l] += 2;
                prefixSum[r+1] -= 2;

                if (a[ptr] % 2 == 0) {
                    int g = r+1;
                    if (g <= mid) white++;
                    prefixSum[g]++;
                    prefixSum[g+1]--;
                }

                ptr++;

                if (white >= k) co = true;
            }
        }

        if (co) cuoi = mid-1;
        else dau = mid+1;
    }
    if (dau > 1000000) cout << -1;
    else cout << dau;
    return 0;
}
