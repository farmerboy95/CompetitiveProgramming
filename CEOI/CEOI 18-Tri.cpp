
/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - First, choose 2 arbitrary points (here I choose n and 1)
        - Query (n, i, 1) with all i from 2 to n-1, if the result is true then the point i is lying
        to the left side of vector (n, 1), otherwise the point i is lying to the right side. Put them
        into 2 lists described above.
        - Sort each of the list in the clockwise order of point n. Merge 2 lists together with n as the
        first point, then the left list, 1 as the middle point, then the right list.
        - So now we can use convex hull idea to find the convex hull starting from point n. Because
        the list is in clockwise order, we can easily find the convex hull.
        - But it's not the end. The "convex hull" can be concave at our first point (point n). So here
        we can make it convex by querying with its 2 neighbours in the "convex hull" until we cannot find
        any concave element.
*/
 
#include <bits/stdc++.h>
#include "trilib.h"
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
const int MAXN = 110;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;
 
int n;
vector<int> lef, rig, cmb, convexHull;
 
bool cmp(int a, int b) {
    return is_clockwise(n,a,b);
}
 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    n = get_n();
    FOR(i,2,n-1)
        if (is_clockwise(n,i,1)) lef.push_back(i);
        else rig.push_back(i);
    sort(ALL(lef), cmp);
    sort(ALL(rig), cmp);
    cmb.push_back(n);
    for (int x : lef) cmb.push_back(x);
    cmb.push_back(1);
    for (int x : rig) cmb.push_back(x);
 
    convexHull.push_back(cmb[0]);
    convexHull.push_back(cmb[1]);
    FOR(i,2,SZ(cmb)-1) {
        while (SZ(convexHull) >= 2 && !is_clockwise(convexHull[SZ(convexHull)-2], convexHull[SZ(convexHull)-1], cmb[i])) convexHull.pop_back();
        convexHull.push_back(cmb[i]);
    }
 
    int la = SZ(convexHull)-1;
    int fi = 0;
    while (la - fi + 1 >= 3) {
        if (!is_clockwise(convexHull[la], convexHull[fi], convexHull[fi+1])) fi++;
        else if (!is_clockwise(convexHull[la-1], convexHull[la], convexHull[fi])) la--;
        else break;
    }
    give_answer(max(3, la-fi+1));
    return 0;
}