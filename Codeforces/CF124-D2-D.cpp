/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Transform (x, y) to (x+y, x-y) then the bad points would form vertical and horizontal lines,
        separate the space into many blocks.
        - When we move from (x, y) to adjacent cells in normal space, it means that we move diagonally in transformed space.
        - For example 
            a = 2, b = 4 => A = 2a = 4, B = 2b = 8, 
            (x, y) = (3, -1) => (x+y, x-y) = (2, 4), we have the following space
        
              0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7
            0 # # # # # # # # # # # # # # # #
            1 # . . . . . . . # . . . . . . .
            2 # . . . X . . . # . . . . . . .
            3 # . . . . . . . # . . . . . . .
            0 # # # # # # # # # # # # # # # #
            1 # . . . . . . . # . . . . . . .
            2 # . . . . . . . # . . . . . . .
            3 # . . . . . . . # . . . . . . .
        
        - If we move from one block to adjacent block, we would have to pass one bad point. The same thing would happen
        when we move from one block to diagonal block.
        => Find the blocks of start and end point, the problem reduced to finding the shortest path from one point to another point
        in the space if we can move to 8 adjacent cells.
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
#define WHATIS(x) cout << #x << " is " << x << endl;
#define ERROR(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
//__builtin_ffs(x) return 1 + index of least significant 1-bit of x
//__builtin_clz(x) return number of leading zeros of x
//__builtin_ctz(x) return number of trailing zeros of x

using namespace std;
using ll = long long;
using ld = double;
typedef pair<ll, ll> II;
typedef pair<II, int> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;

void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
    cout << *it << " = " << a << endl;
    err(++it, args...);
}

const ll MODBASE = 1000000007LL;
const int MAXN = 100010;
const int MAXM = 200010;
const int MAXK = 110;
const int MAXQ = 200010;

ll a, b, A, B;
II st, fi;

II transform(II p) {
    return II(p.FI + p.SE, p.FI - p.SE);
}

II findBlock(II p) {
    II res;
    if (p.FI >= 0) res.FI = p.FI / A;
    else res.FI = p.FI / A - (p.FI % A != 0);
    if (p.SE >= 0) res.SE = p.SE / B;
    else res.SE = p.SE / B - (p.SE % B != 0);
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> a >> b >> st.FI >> st.SE >> fi.FI >> fi.SE;
    A = a * 2;
    B = b * 2;
    st = transform(st);
    fi = transform(fi);
    II g = findBlock(st), h = findBlock(fi);
    cout << max(abs(g.FI - h.FI), abs(g.SE - h.SE));
    return 0;
}
