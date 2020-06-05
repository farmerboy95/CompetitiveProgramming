/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Same as the editorial: https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/CEOI/official/2005/solfence.pdf
        - Comments in implementation below
*/

#include <bits/stdc++.h>
#include "lookup.h"
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

int n, m, leftMost = -1;

struct pointType {
    bool isLeft, cross;
};
pointType p[MAXN];

int getNext(int u) {
    return u % n + 1;
}

bool isLeft(int i, int j) {
    int iNext = getNext(i), jNext = getNext(j);
    bool ok = 0;
    // check by 4 cases shown in the editorial
    // personally, i think getting leftMost should be separated from getting point types
    // as isLeft[i] are not fully filled
    if (p[iNext].isLeft && Drift(i, iNext, j) <= 0 && Drift(i, iNext, jNext) <= 0) ok = 1;
    if (p[i].isLeft && Drift(i, iNext, j) >= 0 && Drift(i, iNext, jNext) >= 0) ok = 1;
    if (p[jNext].isLeft && Drift(j, jNext, i) >= 0 && Drift(j, jNext, iNext) >= 0) ok = 1;
    if (p[j].isLeft && Drift(j, jNext, i) <= 0 && Drift(j, jNext, iNext) <= 0) ok = 1;
    return ok;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    n = GetN();
    FOR(i,1,n) {
        int iNext = getNext(i);
        int side = Drift(n+1, n+2, i), sideNext = Drift(n+1, n+2, iNext);
        // cross means the segment (i, iNext) crosses the road line or not
        p[i].cross = (side * sideNext < 0);
        // isLeft means post i is on the left of road line (from a to b) 
        p[i].isLeft = (side > 0);
    }
    // get leftMost, which is the left most intersection of a segment and the road line
    // the intersection is represented by post label i
    FOR(i,1,n)
        if (p[i].cross) {
            m++;
            if (leftMost == -1) leftMost = i;
            else if (isLeft(i, leftMost)) leftMost = i;
        }

    // special case: m = 0, one region
    if (m == 0) {
        if (p[1].isLeft) Answer(1, 0);
        else Answer(0, 1);
        return 0;
    }
    
    // now we start to go as described in the editorial
    int side = 1;
    int i = leftMost;
    int d = (p[leftMost].isLeft ? -1 : 1);
    int leftpart = 0;
    do {
        // move until it crosses the road line
        int iEnd = i;
        do {
            iEnd += d;
            if (iEnd < 1) iEnd = n;
            if (iEnd > n) iEnd = 1;
        } while (p[iEnd].cross == 0);
        // determine if it's the left or right part
        if (side && isLeft(i, iEnd)) leftpart++;
        // update i and side, continue to move
        i = iEnd;
        side = !side;
        // until we reach leftMost again
    } while (i != leftMost);
    Answer(leftpart, m/2 + 1 - leftpart);
    return 0;
}
