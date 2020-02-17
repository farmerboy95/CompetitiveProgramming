/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - We binary search the result (call it x) and count the number of products that are
        smaller than or equal to x.
        - First we put all negative numbers into array neg (remove sign), positive numbers 
        into array pos and count number of products that are equals to 0.
        - If current number u is smaller than 0, we count number of products that are bigger
        than or equal to u, this product should be formed from a number from neg and a number
        from pos. We iterate through 1 array and binary search another array.
        - If current number u >= 0, we count number of products that are smaller than or equal
        to u, this product should be formed from 2 numbers of 1 array. So we consider each array,
        iterate through it and binary search the iterated elements. Remember to add number of 
        products that are equals to 0 (we counted it above) to the result.
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

int n, cnt0;
ll prod0, k;
vector<ll> pos, neg;

ll cntNeg(ll u) {
    ll res = 0;
    FOR(i,0,SZ(pos)-1) {
        ll e = u / pos[i] + (u % pos[i] > 0);
        int dau = 0, cuoi = SZ(neg)-1;
        while (dau <= cuoi) {
            int mid = (dau + cuoi) >> 1;
            if (neg[mid] >= e) cuoi = mid-1;
            else dau = mid+1;
        }
        res += SZ(neg) - dau;
    }
    return res;
}

ll cnt(vector<ll> &a, ll u) {
    ll res = 0;
    FOR(i,0,SZ(a)-1) {
        ll e = u / a[i];
        int dau = 0, cuoi = i-1;
        while (dau <= cuoi) {
            int mid = (dau + cuoi) >> 1;
            if (a[mid] <= e) dau = mid+1;
            else cuoi = mid-1;
        }
        res += cuoi + 1;
    }
    return res;
}

ll cntPos(ll u) {
    return cnt(pos, u) + cnt(neg, u);
}

ll solve(ll u) {
    ll res = 0;
    if (u >= 0) {
        res = prod0 + cntNeg(1);
        if (u) res += cntPos(u);
        return res;
    }
    else {
        res += cntNeg(-u);
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> k;
    FOR(i,1,n) {
        ll x;
        cin >> x;
        if (x == 0) cnt0++;
        else if (x > 0) pos.emplace_back(x);
        else neg.emplace_back(-x);
    }
    sort(ALL(neg));
    sort(ALL(pos));

    FORE(i,n-1,n-cnt0) prod0 += i;

    ll dau = -1000000000000000000LL, cuoi = 1000000000000000000LL;
    while (dau <= cuoi) {
        ll mid = (dau + cuoi) / 2;
        if (solve(mid) < k) dau = mid+1;
        else cuoi = mid-1;
    }
    cout << dau;
    return 0;
}
