/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - For each starting point i, we can go as far as possible to the right by using m operations, let it be j
        - We can easily see that when i increases, j monotonic increases
        - Let f[i] = the index of nearest higher element than element i to the right of i
        - Let need[i] is the number of operations needed to make segment (i, n) monotonic increasing
        - Now we can use 2 pointers, left (i) and right (the furthest element from i to the right)
        - When we increase r, we find max(a[l->r]) and sum should be increased by max(a[l->r]) - a[r]
        - When we increase l, let mm = max(a[l->r]) and k = max(f[l->r]) and calc(l, r) = number of operations needed for segment(l, r)
        => if a[r+1] >= mm, calc(l, r) = need[l] - need[r+1];
            otherwise calc(l, r) = need[l] - need[k] - (mm * (number of element from u+1 to k-1) - (sum a from u+1 to k-1));
        - To find mm and k, use sliding window technique to reduce memory and time instead of RMQ (as we use 2 pointers)
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
const int MAXN = 1000010;
const int MAXM = 10010;
const int MAXK = 110;
const int MAXQ = 200010;

int n, a[MAXN], Max[MAXN][20];
ll m, s[MAXN], need[MAXN];
deque<II> window, windowMax;
int f[MAXN];
stack<int> st;

ll getSum(int l, int r) {
    return s[r] - s[l-1];
}

ll getNum(int l, int r) {
    return r - l + 1;
}

ll calc(int l, int u, int k, int mm) {
    if (a[u+1] >= mm) return need[l] - need[u+1];
    return need[l] - need[k] - ((ll) mm * getNum(u+1, k-1) - getSum(u+1, k-1));
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m;
    FOR(i,1,n) cin >> a[i];
    FOR(i,1,n) s[i] = s[i-1] + a[i];
    a[n+1] = 2000000000;

    st.push(n+1);
    FORE(i,n,1) {
        while (a[i] >= a[st.top()]) st.pop();
        f[i] = st.top();
        st.push(i);
    }

    need[n+1] = 0;
    FORE(i,n,1) {
        int nxt = f[i];
        need[i] = getNum(i, nxt-1) * a[i] - getSum(i, nxt-1) + need[nxt];
    }

    int l = 1, r = 1;
    ll remain = m;
    // window saves max f
    window.push_back(II(f[1], 1));
    // windowMax saves max a
    windowMax.push_back(II(a[1], 1));

    while (r+1 <= n) {
        r++;
        // sliding window technique
        while (!window.empty() && window.back().FI <= f[r]) window.pop_back();
        window.push_back(II(f[r], r));
        while (!windowMax.empty() && windowMax.back().FI <= a[r]) windowMax.pop_back();
        windowMax.push_back(II(a[r], r));

        int g = windowMax.front().FI;
        if (g <= a[r]) continue;
        int need = g - a[r];
        if (remain < need) {
            r--;
            break;
        }
        remain -= need;
    }

    ll res = r - l + 1;
    while (l+1 <= n) {
        l++;
        while (window.front().SE < l) window.pop_front();
        while (windowMax.front().SE < l) windowMax.pop_front();
        remain = m - calc(l, r, window.front().FI, windowMax.front().FI);

        while (r+1 <= n) {
            r++;
            // sliding window technique
            while (!window.empty() && window.back().FI <= f[r]) window.pop_back();
            window.push_back(II(f[r], r));
            while (!windowMax.empty() && windowMax.back().FI <= a[r]) windowMax.pop_back();
            windowMax.push_back(II(a[r], r));

            int g = windowMax.front().FI;
            if (g <= a[r]) continue;
            int need = g - a[r];
            if (remain < need) {
                r--;
                break;
            }
            remain -= need;
        }

        res += r - l + 1;
    }

    cout << res;
    return 0;
}
