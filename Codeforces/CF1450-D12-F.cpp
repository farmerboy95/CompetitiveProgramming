/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - First we handle some special cases: n=1, n=2
        - We can easily see that if the max number of appearance of a value > ceil(n/2), there is
        no solution. Otherwise, there sure is one.
        - Now we have to reduce the number of equal adjacent pairs to 0. Let's consider a pair, xx
        for example.
        - If one of the ends of the array is y != x, for example, ...xx...y, we can reverse the right
        part to become ...xy...x, the number of equal pairs reduced by 1, the cost increased by 1.
        This is the best way that we can do.
        - If both ends are x, there is another case like ...xx...yy..., we reverse the middle part
        to become ...xy...xy..., the number of equal pairs reduced by 2, the cost increased by 2.
        But we don't need to consider this case in our problem.
        - If there is no such above cases, we have something like ...xx...yz..., we reverse the middle
        part again ...xy...xz..., the number of equal pairs reduced by 1, the cost increased by 2.
        This is the worst case.
        - As n is now larger than 2, we can just only consider case 1 and 3. We care about the ends
        only, and maintain a set (number of pairs, value) and try to reverse using case 1 from the value
        that has the largest num of pairs. If not possible, we have to use case 3 as I think case 2
        is reduced in this situation.
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
const int MAXN = 100010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int t, n, a[MAXN], cnt[MAXN], cnt2[MAXN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> t;
    while (t--) {
        cin >> n;
        FOR(i,1,n) cin >> a[i];
        if (n == 1) {
            cout << 0 << "\n";
            continue;
        }
        if (n == 2) {
            if (a[1] == a[2]) cout << -1 << "\n";
            else cout << 0 << "\n";
            continue; 
        }
        FOR(i,1,n) cnt[i] = 0;
        FOR(i,1,n) cnt[a[i]]++;

        int Max = 0;
        FOR(i,1,n) Max = max(Max, cnt[i]);

        if (Max > n / 2 + n % 2) {
            cout << -1 << "\n";
            continue;
        }

        FOR(i,1,n) cnt2[i] = 0;
        int l = a[1], r = a[n];

        FOR(i,1,n-1)
            if (a[i] == a[i+1]) cnt2[a[i]]++;
        
        set<II> s;
        FOR(i,1,n)
            if (cnt2[i]) s.insert(II(cnt2[i], i));
        
        int res = 0;
        while (SZ(s)) {
            auto it = s.end();
            it--;
            bool co = true;
            while (1) {
                int val = it->SE, numPair = it->FI;
                if (val != l) {
                    l = val;
                    numPair--;
                    s.erase(it);
                    if (numPair) s.insert(II(numPair, val));
                    res++;
                    break;
                } else if (val != r) {
                    r = val;
                    numPair--;
                    s.erase(it);
                    if (numPair) s.insert(II(numPair, val));
                    res++;
                    break;
                } else {
                    if (it == s.begin()) {
                        co = false;
                        break;
                    }
                    it--;
                }
            }
            if (!co) {
                res += 2;
                int val = it->SE, numPair = it->FI;
                s.erase(it);
                numPair--;
                if (numPair) s.insert(II(numPair, val));
            }
        }
        cout << res << "\n";
    }
    return 0;
}
