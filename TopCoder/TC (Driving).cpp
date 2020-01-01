/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: https://www.topcoder.com/tc?module=Static&d1=match_editorials&d2=tccc05_online_rd_2
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

struct Input {
    ld s, p, c;
    Input(ld s = 0, ld p = 0, ld c = 0) : s(s), p(p), c(c) {}
};

ld costOfTime;
vector<Input> tickets, costPerMile;

Input parseTicket(string s) {
    stringstream sin(s);
    ld x, y, z;
    sin >> x >> y >> z;
    return Input(x, y, z);
}

Input parseCost(string s) {
    stringstream sin(s);
    ld x, y;
    sin >> x >> y;
    return Input(x, 1, y);
}

ld calc(Input t1, Input t2, Input c1, Input c2, ld sp) {
    ld res = costOfTime / sp;
    ld prob = t1.p + (t2.p - t1.p) * (sp - t1.s) / (t2.s - t1.s);
    res += prob * t1.c;
    ld cpm = c1.c + (c2.c - c1.c) * (sp - c1.s) / (c2.s - c1.s);
    res += cpm;
    return res;
}

ld test(int x, int y) {
    Input t1 = tickets[x], t2 = tickets[x+1], c1 = costPerMile[y], c2 = costPerMile[y+1];
    ld LL = max(t1.s, c1.s), RR = min(t2.s, c2.s);
    FOR(i,1,1000) {
        ld ML = (LL + LL + RR) / 3, MR = (LL + RR + RR) / 3;
        ld g = calc(t1, t2, c1, c2, ML);
        ld h = calc(t1, t2, c1, c2, MR);
        if (g > h) LL = ML;
        else RR = MR;
    }
    return calc(t1, t2, c1, c2, LL);
}

struct Driving {
    public:
    ld lowestCost(int _costOfTime, vector <string> _tickets, vector <string> _costPerMile) {
        costOfTime = _costOfTime;
        tickets.clear();
        tickets.emplace_back(Input(0,0,0));
        FOR(i,0,SZ(_tickets)-1) tickets.emplace_back(parseTicket(_tickets[i]));
        costPerMile.clear();
        FOR(i,0,SZ(_costPerMile)-1) costPerMile.emplace_back(parseCost(_costPerMile[i]));

        // solve
        ld res = 1e18;
        int x = 0, y = 0;
        while (x < SZ(tickets)-1 && y < SZ(costPerMile)-1) {
            ld z = test(x, y);
            res = min(res, z);
            if (tickets[x+1].s < costPerMile[y+1].s) x++;
            else if (tickets[x+1].s > costPerMile[y+1].s) y++;
            else {
                x++;
                y++;
            }
        }
        return res;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    Driving d;
    cout << fixed << setprecision(9) << d.lowestCost(50, {"80 0.001 100"}, {"0 0.01","30 0.40","55 0.37","65 0.42","75 0.53"});
    cout << endl;
    cout << fixed << setprecision(9) << d.lowestCost(50, {"60 0.00001 50","65 0.00003 70","70 0.0001 110","75 0.001 180"}, {"0 0.01","30 0.40","55 0.37","65 0.42","75 0.53"});
    cout << endl;
    cout << fixed << setprecision(9) << d.lowestCost(100, {"60 0.00001 50","65 0.00003 70","70 0.0001 110","75 0.001 180"}, {"0 0.01","30 0.40","55 0.37","65 0.42","75 0.53"});
    cout << endl;
    cout << fixed << setprecision(9) << d.lowestCost(1000, {"60.50 0.00002 50.53","65 0.00007 70", "070 0.0002 150","75 0.002 200", "080.001 0.004 300","85. 0.004 1000000", "150 0.004 1000000"}, {"0 0.50","30 0.40","55.5 0.37","65 0.42","75 0.63","80 0.87","95 1.30"});
    cout << endl;
    return 0;
}
