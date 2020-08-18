/*
    Author: Nguyen Tan Bao
    Statement: https://www.facebook.com/codingcompetitions/hacker-cup/2020/round-1/problems/A3
    Status: AC
    Idea:
        - In the final figure that we use to calculate perimeter, we can see that there are some
        vertical lines and horizontal lines. We will manage the vertical lines only (horizontal lines 
        will be managed by 2 vertical lines). We are going to maintain a set which contains vertical 
        lines with these attributes:
            + x: position of the line
            + typ: 0 - open line, 1 - close line (open means the right side of the line is in the room
            close means the reverse)
            + l, r: from y = l to y = r, l < r if open and l > r if close.
        - So for each new room, we are going to add at most 2 vertical lines to the set, because
        H1 <= H2 <= ... <= Hn.
        - The first thing we should do is to subtract (then remove) all the line length from L to 
        R (= L + W). In addition, we should check if some segments is not covered by horizontal lines, 
        we add 2 * segment length to p. We don't need to care about covered segments (easy to see).
        - Finally, we check if we can add the whole h[i] to the left or right using addL and addR.
        If for example addL = false, there is a chance that we can add a vertical line into the set,
        based on r of previous line in the set. The same thing is applied to addR = false.
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

struct Col {
    int x, l, r, typ;
    Col(int x = 0, int l = 0, int r = 0, int typ = 0) : x(x), l(l), r(r), typ(typ) {}
    bool operator<(const Col& t) const { 
        if (x == t.x) return typ < t.typ;
        return x < t.x; 
    }
    bool operator<=(const Col& t) const { 
        if (x == t.x) return typ <= t.typ;
        return x <= t.x; 
    } 
};

int n, k, l[MAXN], h[MAXN], w[MAXN];
set<Col> s;
vector<set<Col>::iterator> itVec;

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
        auto itL = s.lower_bound(Col(L, 0, 0, 0));
        auto it = itL;
        itVec.clear();
        bool addL = false, addR = false;
        while (it != s.end()) {
            if (*it <= Col(R, 0, 0, 1)) itVec.push_back(it);
            else break;
            it++;
        }
        if (itL == s.end()) addL = true;
        if (itL != s.end() && itL->typ == 0 && itL->l == 0) addL = true;
        if (addL && SZ(itVec) == 0) addR = true;
        if (SZ(itVec) && itVec.back()->typ == 1 && itVec.back()->r == 0) addR = true;

        int last = L;
        FOR(j,0,SZ(itVec)-1) {
            // subtract height
            p = (p - abs(itVec[j]->r - itVec[j]->l) + MODBASE) % MODBASE;
            if (itVec[j]->typ == 0 && itVec[j]->l == 0) {
                // add width
                p = (p + 2LL * (itVec[j]->x - last)) % MODBASE;
            } else if (itVec[j]->typ == 1 && itVec[j]->r == 0) {
                last = itVec[j]->x;
            }
        }

        vector<Col> add;
        if (addL) {
            // add height
            p = (p + h[i]) % MODBASE;
            add.push_back(Col(L, 0, h[i], 0));
        } else {
            itL = s.lower_bound(Col(L, 0, 0, 0));
            itL--;
            // previous line
            if (itL->r < h[i]) {
                // add new vertical line
                add.push_back(Col(L, itL->r, h[i], 0));
                p = (p + h[i] - itL->r) % MODBASE;
            }
        }
        
        if (addR) {
            // add height
            p = (p + h[i]) % MODBASE;
            // add width at the end if needed
            p = (p + 2LL * (R - last)) % MODBASE;
            add.push_back(Col(R, h[i], 0, 1));
        } else {
            it = s.upper_bound(Col(R, 0, 0, 1));
            // next line
            if (it->l < h[i]) {
                // add new vertical line
                add.push_back(Col(R, h[i], it->l, 1));
                p = (p + h[i] - it->l) % MODBASE;
            }
        }

        // time to remove the old lines and insert new ones.
        FORE(j,SZ(itVec)-1,0) s.erase(itVec[j]);
        for (Col x : add) s.insert(x);

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