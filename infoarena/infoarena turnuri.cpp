/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let a[0] = INF
        - Let l[i] = j is the index of the nearest tower that has a[j] > a[i] (j < i)
        - Let L[i] = J is the index of the second nearest tower that has a[J] > a[i] (J < j < i)

        - Consider tower i with height a[i], if removed tower j is not in the segment [l[i], i], 
        we add k = (i - l[i] - (j==0)) to the result, easily count the number of towers j
        - If removed tower j is in the segment [l[i]+1, i-1], we add k-1 to the result, easily prove
        - If removed tower is l[i] > 0, we add i - L[i] - 1 - (L[i] == 0) to the result, easily prove

        - So how to get l[i] and L[i]?
        - We can calculate l[i] using a stack that stores descending a[j] from 1 to i-1 => O(n)
        - We can calculate L[i] like this:
            + For each i, we have l[i], and the list of i that have the same l[i] must not be descending
            + So we call ite[l[i]] is the index p of the tower that has a[p] larger than a[i]
            + As the list is not descending, we can just move ite[l[i]] to the left
            + If there is an a[y] breaking that rule, l[y] will change and left bound of ite[l[y]] would be l[i]
            => O(n)
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
const int MAXM = 30010;
const int MAXK = 16;
const int MAXQ = 200010;

int n, a[MAXN], l[MAXN], L[MAXN], ite[MAXN];
stack<int> s;

int getLength(int l, int r) {
    return max(0, r - l + 1);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    freopen("turnuri.in", "r", stdin);
    freopen("turnuri.out", "w", stdout);
    cin >> n;
    FOR(i,1,n) cin >> a[i];
    a[0] = 2000000001;

    s.push(0);
    FOR(i,1,n) {
        while (a[i] >= a[s.top()]) s.pop();
        l[i] = s.top();
        s.push(i);
    }

    FOR(i,1,n) ite[i] = i-1;

    FOR(i,1,n) {
        if (l[i] == 0) continue;
        int j = l[i];
        while (a[ite[j]] <= a[i]) ite[j]--;
        L[i] = ite[j];
    }

    ll res = 0;
    FOR(i,1,n) {
        int k = i - l[i] - (l[i] == 0);
        ll cnt = getLength(1, l[i]-1) + getLength(i+1, n);
        res += cnt * k;

        res += (ll) getLength(l[i]+1, i-1) * (k-1);
        if (l[i] == 0) continue;
        res += i - L[i] - 1 - (L[i] == 0);
    }
    cout << res;
    return 0;
}
