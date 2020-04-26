/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Mainly from 
            + https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/COCI/official/2015/contest3_solutions/solutions.pdf
            + https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/COCI/official/2015/contest3_solutions/kamioni.cpp
        - Specific comments in the code
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

// dir = {0: abducted, 1: right, -1: left}

struct Event {
    int truckId, x, dir;
    ll time;
};

bool operator< (Event a, Event b) {
    if (a.time == b.time) return a.dir < b.dir;
    return a.time < b.time;
}

// wasLeft is maintained to be the position of truckId to the query truckId
struct Query {
    int truckId, wasLeft, queryId;
};

struct Truck {
    int k, x, dir;
    ll time;
    vector<Query> queries;
};

Truck trucks[MAXN];
int n, m, res[MAXN];
vector<Event> events;
map<II, vector<int> > ma;

void applyEvent(Event &e) {
    trucks[e.truckId].x = e.x;
    trucks[e.truckId].dir = e.dir;
    trucks[e.truckId].time = e.time;
}

int checkIsLeft(const Truck &a, const Truck &b, ll prevTime, int prevDir) {
    // special case, as the b truck is removed before or at the prevTime
    if (b.dir == 0 && prevTime >= b.time) return 0;
    int aPos, bPos;
    if (b.dir == 0) {
        // if b truck is removed after the prevTime
        // we should move a back to the moment b disappears
        bPos = b.x;
        aPos = (a.time - b.time) * (-prevDir) + a.x;
    } else {
        // otherwise, move b with time
        aPos = a.x;
        bPos = (a.time - b.time) * b.dir + b.x;
    }
    if (bPos < aPos) return -1;
    return 1;
}

void solveQuery(const Truck &t, Query &q, ll prevTime, int prevDir) {
    // now q.wasLeft was the position of q.truckId to t.truckId, we need to check
    // the new position of q.truckId after (t.time - trucks[q.truckId].time)
    int isLeft = checkIsLeft(t, trucks[q.truckId], prevTime, prevDir);
    res[q.queryId] += (isLeft * q.wasLeft < 0);
    // update wasLeft
    q.wasLeft = isLeft;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m;
    FOR(i,1,n) {
        ll sumTime = 0;
        int x, newX;
        cin >> trucks[i].k >> x;
        FOR(j,2,trucks[i].k) {
            cin >> newX;
            // we store truckId, x, direction and the moment that event is started
            Event e = {i, x, x < newX ? 1 : -1, sumTime};
            // no need to store the first event of each truck as we apply it directly
            // to the truck initially
            if (j == 2) applyEvent(e);
            else events.push_back(e);
            // update sumTime and x
            sumTime += abs(x - newX);
            x = newX;
        }
        // remember to store the last moment a truck exists
        Event e = {i, x, 0, sumTime};
        events.push_back(e);
    }

    FOR(i,1,m) {
        int u, v;
        cin >> u >> v;
        if (u > v) swap(u, v);
        ma[II(u,v)].push_back(i);
        // check if pair (u, v) already proceed
        if (SZ(ma[II(u, v)]) > 1) continue;
        // query the truck with smaller number of cities, as the complexity would be O(S*sqrt(S))
        // proof is in solution.pdf
        if (trucks[u].k > trucks[v].k) swap(u, v);
        // add the truck v to the list of queries of u
        trucks[u].queries.push_back({v, trucks[v].x < trucks[u].x ? -1 : 1, i});
    }

    // sort and iterate through events
    sort(ALL(events));
    for (auto e : events) {
        ll prevTime = trucks[e.truckId].time;
        int prevDir = trucks[e.truckId].dir;
        // apply new event to e.truckId
        applyEvent(e);
        // then iterate through queries
        for (Query &q : trucks[e.truckId].queries) solveQuery(trucks[e.truckId], q, prevTime, prevDir);
    }

    // update same queries
    FORALL(it, ma) {
        int r = res[it->SE[0]];
        for (int z : it->SE) res[z] = r;
    }

    FOR(i,1,m) cout << res[i] << "\n";
    return 0;
}
