/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let a[i] is the number of steps that the pawn i must take to reach position m
        - We can easily see that when we have the number of pawns that have the same a[i], we can deduct some a[i] by 1
        - Let group[j] stores the number of pawns that have the same a[i] and the a[i] itself
        - This mechanism is the same thing as Staircase Nim, but the target is to move all pawns to a[i] = 2, not 0
        because when one player is able to move all pawns to 2, the other player must move at least one pawn to 1, which
        is a losing case.
        - Of course we must resolve the corner case which exists a[i] = 1 => print number of pawns having a[i] = 1
        - Otherwise, get xor sum of all odd-a[i] groups, if xor sum = 0 => print 0, otherwise, get all winning moves.
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
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int m, n, a[MAXN];
vector<II> group;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> m >> n;
    FOR(i,1,n) {
        int x;
        cin >> x;
        a[i] = m - x - (n-i);
    }
    int cnt = 1;
    FOR(i,2,n)
        if (a[i] == a[i-1]) cnt++;
        else {
            group.emplace_back(II(a[i-1], cnt));
            cnt = 1;
        }
    group.emplace_back(II(a[n], cnt));

    int nimSum = 0;
    FOR(i,0,SZ(group)-1)
        if (group[i].FI % 2) nimSum ^= group[i].SE;
    
    if (group[SZ(group)-1].FI == 1) {
        cout << group[SZ(group)-1].SE;
        return 0;
    }
    if (nimSum == 0) {
        cout << 0;
        return 0;
    }

    int res = 0;
    FOR(i,0,SZ(group)-1)
        if (group[i].FI % 2) {
            // if a[i] is odd
            if ((group[i].SE ^ nimSum) < group[i].SE) res++;
        }
        else if (group[i].FI != 2) {
            // if a[i] is even (not 2), simply get the number of pieces required to move from a[i] to a[i]-1 to achieve nimSum = 0
            int nextGroupSize = 0;
            if (i+1 == SZ(group) || group[i+1].FI < group[i].FI - 1) nextGroupSize = 0;
            else nextGroupSize = group[i+1].SE;

            int piecesToNextGroup = (nimSum ^ nextGroupSize) - nextGroupSize;
            if (piecesToNextGroup > 0 && piecesToNextGroup <= group[i].SE) res++;
        }
    cout << res;
    return 0;
}
