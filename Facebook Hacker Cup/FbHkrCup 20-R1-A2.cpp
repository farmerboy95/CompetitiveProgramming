/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Notice that H1 >= H2 >= ... >= HN. So we only need to care about starting points
        and ending points of unions.
        - We maintain a set of pair (position, open-0/close-1). So for one room, we need to
        subtract from p all the points (number of points * h[i]) in the set between starting 
        and ending points of current room. Then elmininate all those points
        - For height needed to add, we need to see if current points are between any pair
        of starting, ending points. If yes, we add h[i] to the result (add max 2 * h[i] if both
        are not between, and h[i] if only one of 2 are not between).
        - For width, we can easily see that we add (2 * width) for segments that are not occupied
        by any union, we can utilize the set to find those segments.
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
const int MAXN = 1000010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, k;
ll l[MAXN], h[MAXN], w[MAXN];
set<II> s;
vector<set<II>::iterator> itVec;

void init() {
    s.clear();
}

void input() {
    ll A, B, C, D;
    cin >> n >> k;

    FOR(i,1,k) cin >> l[i];
    cin >> A >> B >> C >> D;
    FOR(i,k+1,n) l[i] = (A * l[i-2] + B * l[i-1] + C) % D + 1;

    FOR(i,1,k) cin >> w[i];
    cin >> A >> B >> C >> D;
    FOR(i,k+1,n) w[i] = (A * w[i-2] + B * w[i-1] + C) % D + 1;

    FOR(i,1,k) cin >> h[i];
    cin >> A >> B >> C >> D;
    FOR(i,k+1,n) h[i] = (A * h[i-2] + B * h[i-1] + C) % D + 1;
}

ll handle() {
    ll res = 1, p = 0;

    FOR(i,1,n) {
        int L = l[i], R = l[i] + w[i];
        set<II>::iterator itL = s.upper_bound(II(L, 0));

        bool addL = true, addR = true;
        if (itL != s.end() && itL->SE == 1) addL = false;

        set<II>::iterator it = itL;
        itVec.clear();
        while (it != s.end()) {
            if (*it <= II(R, 0)) itVec.push_back(it);
            else break;
            it++;
        }
        if (SZ(itVec) && itVec.back()->SE == 0) addR = false;
        if (!addL && SZ(itVec) == 0) addR = false;

        int last = L;
        FOR(j,0,SZ(itVec)-1) {
            // subtract height
            p = (p - h[i] + MODBASE) % MODBASE;
            if (itVec[j]->SE == 0) {
                // add width
                p = (p + 2LL * (itVec[j]->FI - last));
            } else {
                last = itVec[j]->FI;
            }
        }

        FORE(j,SZ(itVec)-1,0) s.erase(itVec[j]);
        if (addL) {
            // add height
            p = (p + h[i]) % MODBASE;
            s.insert(II(L, 0));
        }
        if (addR) {
            // add height
            p = (p + h[i]) % MODBASE;
            // add width at the end if needed
            p = (p + 2LL * (R - last)) % MODBASE;
            s.insert(II(R, 1));
        }

        res = res * p % MODBASE;
    }

    return res;
}

ll solve() {
    input();
    init();
    return handle();
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int te;
    cin >> te;
    FOR(o,1,te) {
        cout << "Case #" << o << ": ";
        cout << solve() << "\n";
    }
    return 0;
}
