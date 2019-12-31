/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Use binary search to find the result
        - Consider a length x, we have to consider n-x+1 segments, in each segment, we should check
        if we can put the Great Plank into it and the remaining sum is lower than or equal to P.
        - Easily see that the Great Plank should be the largest sum of length d among x-d+1 segments 
        in a single segment with length x.
        - How can we find the largest sum of length d in a segment with length x?
            + First we pre-calculate sum of all segments with length d in the initial array.
            + For each segment with length x > d, we use sliding window technique to find largest sum
            of length d in it (and the next segments).
            + Do not use RMQ because the memory limit is 128MB.
        - Complexity O(nlogn)
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
typedef pair<ll, int> II;
typedef pair<II, ll> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;
 
const ll MODBASE = 1000000007LL;
const int MAXN = 2000010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, d;
ll p, a[MAXN], s[MAXN], q[MAXN];
deque<II> window;

ll getSum(int l, int r) {
    return s[r] - s[l-1];
}

bool check(int x) {
    while (SZ(window)) window.pop_back();
    int k = x - d + 1;
    FOR(i,d,n) {
        while (!window.empty() && window.back().FI <= q[i]) window.pop_back();
        window.push_back(II(q[i], i));
        while (window.front().SE <= i - k) window.pop_front();
        if (i >= x) {
            ll sum = getSum(i - x + 1, i);
            ll Max = window.front().FI;
            if (sum - Max <= p) return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> p >> d;
    FOR(i,1,n) {
        cin >> a[i];
        s[i] = s[i-1] + a[i];
    }
    ll w = 0;
    FOR(i,1,n) {
        w += a[i];
        if (i >= d) {
            w -= a[i-d];
            q[i] = w;
        }
    }
    int dau = d+1, cuoi = n, mid;
    while (dau <= cuoi) {
        mid = (dau + cuoi) >> 1;
        if (check(mid)) dau = mid+1;
        else cuoi = mid-1;
    }
    cout << cuoi;
    return 0;
}
