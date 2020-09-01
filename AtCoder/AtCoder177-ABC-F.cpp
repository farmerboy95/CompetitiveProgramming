/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - When k is fixed, every path has the same number k of moving downwards, so we want 
        to find the number of minimum times to move to the right.
        - The optimal strategy of moving is to move downwards as much as possible, and if 
        not possible, move to the right. This is due to that fact that, since we want to minimize 
        the number of movement towards right, we can always move to the right in the same way in 
        every row, thus we do not have to move to the right until needed. Now, the path is 
        uniquely determined when the starting square is fixed.
        - Calculate in the increasing order of k while managing the possible W pairs of positions 
        of starting end ending squares counted from the leftmost one. In the k-th process, for each 
        pair such that its ending square is between A[k] and B[k], inclusive, update its ending 
        square to B[k]+1, then answer the minimum difference of starting and ending squares. 
        Note that however, when B[k]=W, the endpoint should be updated to 1e9 instead of W+1.
        - This operations can be processed with segment trees, but this can also be processed with 
        ordered sets.
        - Once the ending square of two pairs becomes the same, they will have the common endpoint 
        from then on, so all of them except for the one having the maximum starting point can be 
        ignored. Prepare a set of (ending point, staring point) and a multiset of endting points 
        subtracted by starting points, and update them while removing the elements that are no 
        longer needed. The total time complexity will be O((H+W)log(H+W))
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

int n, m;
multiset<II> s;
multiset<int> ss;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m;
    FOR(i,1,m) {
        s.insert(II(i,i));
        ss.insert(0);
    }
    FOR(k,1,n) {
        int goDown = k;
        int L, R;
        cin >> L >> R;
        II pick = II(-1, -1);
        while (1) {
            auto it = s.lower_bound(II(L,0));
            if (it == s.end() || it->FI > R) break;
            if (pick.SE < it->SE) pick = *it;
            ss.erase(ss.find(it->FI - it->SE));
            s.erase(it);
        }
        if (pick.FI != -1 && R+1 <= m) {
            s.insert(II(R+1, pick.SE));
            ss.insert(R+1-pick.SE);
        }
        if (!SZ(ss)) cout << "-1\n";
        else cout << *ss.begin() + goDown << "\n";
    }
    return 0;
}
