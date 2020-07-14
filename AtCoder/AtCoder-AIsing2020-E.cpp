/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - For each camel i, we store its index to the last position that it can take l[i] happiness (k[i]),
        and to the first position that it can take r[i] happiness (k[i]+1).
        - We process the camels whose l > r and whose l < r separately. Say for the camels whose l > r, 
        we start assigning them from right to left. For some position i, you maintain the remaining camels 
        whose k >= i in increasing order of l — r (using a set). Now, if there's any camel remaining, we 
        assign the one with the maximum l — r value. Otherwise we don't assign any camel to position i. 
        Similarly we do from left to right for l < r. Finally, we take the minimum of l and r for those 
        whose positions are not assigned.
        - Why is this correct? Like what will happen when camels of type-1(L > R) overlaps with camels of 
        type-2(R > L). i.e., they are fighting for same position? Let's say we fill the camels whose l > r 
        at some positions. We can shift all of them to the left. Similarly for those whose r > l, we can 
        shift them to the right. The remaining positions can be filled with the remaining camels. So in 
        short even on overlapping, we can do some shifting to get the same value.
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
const int MAXN = 200010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int t, n, k[MAXN], l[MAXN], r[MAXN], choose[MAXN];
vector<int> L[MAXN], R[MAXN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> t;
    while (t--) {
        cin >> n;
        FOR(i,0,n+1) {
            L[i].clear();
            R[i].clear();
            choose[i] = 0;
        }
        FOR(i,1,n) {
            cin >> k[i] >> l[i] >> r[i];
            L[k[i]].push_back(i);
            R[k[i]+1].push_back(i);
        }
        ll res = 0;
        set<II> s;
        FORE(i,n,1) {
            for (int j : L[i]) s.insert(II(l[j] - r[j], j));
            if (SZ(s)) {
                II x = *s.rbegin();
                if (x.FI > 0) {
                    choose[x.SE] = 1;
                    s.erase(x);
                }
            }
        }
        s.clear();
        FOR(i,1,n) {
            for (int j : R[i]) s.insert(II(r[j] - l[j], j));
            if (SZ(s)) {
                II x = *s.rbegin();
                if (x.FI > 0) {
                    choose[x.SE] = 1;
                    s.erase(x);
                }
            }
        }

        FOR(i,1,n)
            if (choose[i]) res += max(l[i], r[i]);
            else res += min(l[i], r[i]);
        cout << res << "\n";
    }
    return 0;
}
