/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Easily see that if the last turn is for 1, player 1 will win no matter what.
        - Let span(x, y, z ...) is the set containing the xor sums that subsets of x, y, z ...
        can produce.
        - Let's checkout one simple case 111...11000...0000. We can see that if there exists 
        some x in span(A[1]...A[i]) but not in span(A[i+1]...A[n]) then player 1 wins, otherwise 
        player 1 loses. In other words, If there exists some number in A[1]...A[i] not in 
        span(A[i+1]...A[n]) then player 1 wins, otherwise player 1 loses.
        - What about a more complicated case, like 11001100? Let's see the value of a 1, at i, if 
        this value is not in span(A[x], s[x] == 0, x > i), so 1 will always win, clearly. Otherwise,
        there would always be a way for 0 to cover that value, if and only if the next 1s satisfy the
        condition of being in span of next values of 0 => 0 wins.
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
const int MAXN = 210;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

const int D = 60;
ll basis[D];
int n;
ll a[MAXN];
string s;

void insertVector(ll mask) {
    FOR(i,0,D-1) {
        if (!(mask & (1LL << i))) continue;
        if (!basis[i]) {
            basis[i] = mask;
            return;
        }
        mask ^= basis[i];
    }
}

bool inside(ll mask) {
    FOR(i,0,D-1) {
        if (!(mask & (1LL << i))) continue;
        if (!basis[i]) return false;
        mask ^= basis[i];
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        cin >> n;
        FOR(i,1,n) cin >> a[i];
        cin >> s;
        s = " " + s;
        MS(basis, 0);
        bool co = true;
        FORE(i,n,1)
            if (s[i] == '1') {
                if (!inside(a[i])) {
                    co = false;
                    break;
                }
            } else {
                insertVector(a[i]);
            }
        if (co) cout << "0\n";
        else cout << "1\n";
    }
    return 0;
}
