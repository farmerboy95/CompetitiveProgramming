/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - We use the Oxy coordinate like geometry for simple imagination (it means to swap input x and y)
        - For each person, when we move the firework point (x = k) from left to right, the shortest distance 
        that the person has to move changes in the following way:
            + If |y| >= S, first the result would constantly be |y|, then when the firework point is x - |y|,
        the result would start to reduce by 1 until the firework point is x, then it would increase to |y|
        again (at x + |y|)
            + If |y| < S, again the result would constantly be |y| first, then the changing point is at x - S,
        the result would start to increase as we go closer to the firework point, here we have 2 values,
        the closest safe point on Ox (|y| first) and the closest safe point on x = k (S + S - |y| first).
        When we go closer to the firework point, value on Ox will increase and value on x=k will decrease,
        and the increment will go until value = S, then it would decrease till S - |y| (the person is now
        on x = k), then because of the symmetry of the condition of the firework point, the result would
        increase again, then decrease and go on constantly.
            + There is a special case of the above case, where y = 0, then the first increase will reach
        S and then not reaching S - |y| because it S == S - |y| now. The value will go up and down and then
        go on constantly. Note: MUST NOT merge this one and the above one because more than one direction
        at a same point of a person may cause wrong answer (because of sorting method).
        - Now we know the variability of the result of each person, so we may use a sweep line to check the
        number of going up, going down and going straight (i.e. how the result change from the previous result)
        and get the minimum.
        - But there are a lot of place to conduct the firework, how can we know which one could be optimal?
        We can easily see that the optimal point should be one of the point we noted above. Why? Let's consider
        one x, we have the number of going down is more than the number of going up, so surely we should move on
        to find the nearest turning point of any person. On the other hand, let's suppose we have the number
        of going down is less than the number of going up, so we can move reversely to find the nearest turning
        point.
        - So checking the turning points is optimal, there are O(n) of such turning points. Complexity O(nlogn)
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

struct Point {
    int x, y;
    Point(int xx = 0, int yy = 0) : x(xx), y(yy) {}
};

struct Event {
    ll pos;
    int diff, idx;
    Event(ll poss = 0, int difff = 0, int idxx = 0) : pos(poss), diff(difff), idx(idxx) {}
};

bool operator< (Event a, Event b) {
    return a.pos < b.pos;
}

int n, S;
ll f[MAXN];
Point a[MAXN];
vector<Event> events;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> S;
    FOR(i,1,n) cin >> a[i].y >> a[i].x;

    ll sum = 0;
    FOR(i,1,n) sum += abs(a[i].y);
    FOR(i,1,n) {
        if (abs(a[i].y) >= S) {
            // case 1: down and up and straight
            events.push_back(Event(a[i].x - abs(a[i].y), -1, i));
            events.push_back(Event(a[i].x, 1, i));
            events.push_back(Event(a[i].x + abs(a[i].y), 0, i));
        }
        else {
            // case 2: up down up down straight
            ll pos = a[i].x - S;
            ll top = S + S - abs(a[i].y), bot = abs(a[i].y);
            ll mid = (bot + top) / 2;
            events.push_back(Event(pos, 1, i));

            // case 3: up and down and straight only
            pos += mid - bot;
            if (pos != events.back().pos) events.push_back(Event(pos, -1, i));
            ll nex = S - abs(a[i].y);
            pos += abs(nex - mid);
            if (pos != events.back().pos) events.push_back(Event(pos, 1, i));


            pos += abs(nex - mid);
            events.push_back(Event(pos, -1, i));
            pos += mid - bot;
            events.push_back(Event(pos, 0, i));
        }
    }
    ll res = sum;
    sort(ALL(events));
    // diff is the difference of number of going down and number of going up
    ll diff = 0, pre = -1e14;
    for (auto e : events) {
        ll now = e.pos;
        sum += diff * (now - pre);
        res = min(res, sum);

        // remember to update diff and new direction
        diff += e.diff - f[e.idx];
        f[e.idx] = e.diff;

        pre = now;
    }
    cout << res;
    return 0;
}
