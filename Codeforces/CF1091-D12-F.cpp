/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: More or less like https://codeforces.com/blog/entry/64196
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

int n;
ll l[MAXN];
string s;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n) cin >> l[i];
    cin >> s;
    s = " " + s;
    // use greedy: fly over lava, swim on water and walk on grass
    // issue 1: not enough stamina to fly over lava
    // issue 2: we have some leftover stamina at the end
    bool hasWater = false;
    ll time = 0, stamina = 0, twiceGrass = 0;
    FOR(i,1,n) {
        if (s[i] == 'G') {
            twiceGrass += 2 * l[i];
            time += 5 * l[i];
            stamina += l[i];
        } else if (s[i] == 'W') {
            hasWater = true;
            time += 3 * l[i];
            stamina += l[i];
        } else {
            time += l[i];
            stamina -= l[i];
            // not enough stamina? walk or swim in place to gain it
            if (stamina < 0) {
                // it takes less time to gain stamina in place swimming than walking
                if (hasWater) time -= stamina * 3;
                else time -= stamina * 5;
                stamina = 0;
            }
        }
        // no more than stamina/2 of walking can be converted to flying to save time
        // as converting 1 meter of movement costs us 2 stamina
        // otherwise there would not be enough stamina at this point
        twiceGrass = min(twiceGrass, stamina);
    }
    if (stamina) {
        // twiceGrass <= stamina
        // convert twiceGrass distance of walking to flying
        time -= (5 - 1) * twiceGrass / 2;
        // convert the remaining from swimming to flying
        time -= (3 - 1) * (stamina - twiceGrass) / 2;
    }
    cout << time;
    return 0;
}
