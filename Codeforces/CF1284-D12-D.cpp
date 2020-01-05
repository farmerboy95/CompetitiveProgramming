/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: https://codeforces.com/blog/entry/72804
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
typedef pair<II, ll> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;
 
const ll MODBASE = 1000000007LL;
const int MAXN = 100010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n;
II a[MAXN], b[MAXN];
multiset<int> s, e;

struct Event {
    int t, s, e, isIn;
    Event(int t = 0, int s = 0, int e = 0, int isIn = 0) : t(t), s(s), e(e), isIn(isIn) {}
};

bool operator< (Event a, Event b) {
    if (a.t == b.t) return a.isIn < b.isIn;
    return a.t < b.t;
}

vector<Event> ev;

bool check(II *a, II *b) {
    s.clear(); e.clear(); ev.clear();
    FOR(i,1,n) {
        ev.emplace_back(Event(a[i].FI, b[i].FI, b[i].SE, 1));
        ev.emplace_back(Event(a[i].SE+1, b[i].FI, b[i].SE, 0));
    }
    sort(ALL(ev));
    FOR(i,0,SZ(ev)-1) {
        Event r = ev[i];
        if (r.isIn) {
            if (SZ(s)) {
                int maxS = *s.rbegin();
                int minE = *e.begin();
                if (minE < r.s || r.e < maxS) return false;
            }
            s.insert(r.s);
            e.insert(r.e);
        }
        else {
            s.erase(s.find(r.s));
            e.erase(e.find(r.e));
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n) {
        cin >> a[i].FI >> a[i].SE;
        cin >> b[i].FI >> b[i].SE;
    }
    if (check(a, b) && check(b, a)) cout << "YES";
    else cout << "NO";
    return 0;
}
