/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let's consider 2 chameleons, one going right with color b and one going left with color a
                                      b            a
                                    ---->        <----
        - After collision, we have the following scene
                                    (a+b)%k        b
                                    <----        ---->
        - We may consider that the one with color b continue to go without changing color, and the one
        with color a changed its color, there is no turning back here
        - So those going right will continue to go until they fall out of the stick, and those going left
        will continue to go (with color changes) until they fall out of the stick.
        - Then we may come up with a O(N^2) solution, ones going right will have length added directly to
        the result. For ones going left, we consider chameleons standing to the left of it and consider from
        the nearest to furthest, get length, get new color, adding the length to the result...
        - But clearly it would lead to TLE verdict. Now, we notice that K <= 40, really small. We can also see
        that the distance of collision between 2 chameleons going right impacting with one going left will
        be equal no matter the distance of the one going left to 2 going right is.
        - So we can maintain an array D[x] = length in which a chameleon will have color x if that chameleon
        going left with color 0, it's easy to see that if the color is c, D[(c+x)%k] == D[x]
        - Complexity (O(N*K))
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
const int MAXK = 50;
const int MAXQ = 200010;

struct Chameleon {
    int pos, type;
    char dir;
    Chameleon(int pos = 0, int type = 0, char dir = 'A') : pos(pos), type(type), dir(dir) {}
};

int n, k, l;
ll res[MAXK];
int newD[MAXN], D[MAXN];
Chameleon a[MAXN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> k >> l;
    l *= 2;
    FOR(i,1,n) cin >> a[i].pos >> a[i].type >> a[i].dir;
    // multiple with 2 to remove float number, we can print out float number later
    FOR(i,1,n) a[i].pos *= 2;
    int firstPos = -1, lastPos = -1, sumMod = 0;
    FOR(i,1,n) {
        if (a[i].dir == 'D') {
            // going right? add distance from it to the right end directly to the result
            res[a[i].type] += l - a[i].pos;
            MS(newD, 0);
            // we can manage distance from the first one to left end and distance from the last one
            // to the one going left, D only store distance between those which going right
            // that distance = real distance / 2
            if (lastPos != -1) newD[a[i].type] += (a[i].pos - lastPos) / 2;
            // update D
            FOR(j,0,k-1) newD[(j + a[i].type) % k] += D[j];
            FOR(j,0,k-1) D[j] = newD[j];
            // get first (if needed) and last pos, update sum mod to get distance from the first one
            // to left end later
            if (firstPos == -1) firstPos = a[i].pos;
            lastPos = a[i].pos;
            sumMod = (sumMod + a[i].type) % k;
        }
        else {
            // no right one? update result immediately
            if (lastPos == -1) {
                res[a[i].type] += a[i].pos;
                continue;
            }
            // update result
            res[a[i].type] += (a[i].pos - lastPos) / 2;
            FOR(j,0,k-1) res[(j + a[i].type) % k] += D[j];
            // get the distance from the first one to left end and update res based on sum mod
            int lenFirst = (a[i].pos + firstPos) / 2;
            res[(sumMod + a[i].type) % k] += lenFirst;
        }
    }
    // use integer only, as the distance will be x/1 or x/2;
    FOR(i,0,k-1)
        if (res[i] % 2) cout << res[i]/2 << ".5\n";
        else cout << res[i]/2 << ".0\n";
    return 0;
}