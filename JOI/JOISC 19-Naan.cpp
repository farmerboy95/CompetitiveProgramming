/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Mainly from https://github.com/stefdasca/CompetitiveProgramming/blob/master/JOI/Spring%20Camp/JOISC%2019-naan.cpp
        - So here for each person i, we try to find the position of the j-th cut (last j would definitely
        be n), put it into num[i][j] (numerator of the position) and den[i][j] (denominator of the position)
        - When finding the permutation, for example, we need to find the first person for the first cut, we
        find the smallest num[i][1] / den[i][1] and remove it from the list, then we find the smallest one
        for the second cut and so on...
        - Why? Because when we find the shortest num[i][j] / den[i][j], the next smallest num[k][j+1] / den[k][j+1]
        will always be available as the length of the next cut can be a bit longer than expected. Then we can
        always find a result with this way of solving
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
const int MAXN = 2010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, l, v[MAXN][MAXN];
ll num[MAXN][MAXN], den[MAXN][MAXN];
bool choose[MAXN];
vector<int> res;

bool isSmaller(int a, int b, int pos) {
    ld realPosB = (ld) num[b][pos] / den[b][pos];
    ld realPosA = (ld) num[a][pos] / den[a][pos];
    return realPosA < realPosB;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> l;
    FOR(i,1,n)
        FOR(j,1,l) cin >> v[i][j];
    FOR(i,1,n) {
        // get sum of v[i][j] -> s
        int s = 0;
        FOR(j,1,l) s += v[i][j];
        int curS = 0, itr = 0;
        FOR(j,1,n) {
            // for ith cut, we find until curS / j >= s / n, definitely
            while ((ll) curS * n < (ll) s * j) curS += v[i][++itr];
            // as curS / j - s / n >= 0
            // => the position = itr - ((curS / j - s / n) * j / v[i][itr])
            //                 = itr - (curS * n - s * j) / (n * v[i][itr])
            //                 = (itr * n * v[i][itr] - curS * n + s * j) / (n * v[i][itr])
            num[i][j] = (ll) itr * n * v[i][itr] - (ll) curS * n + (ll) s * j;
            den[i][j] = (ll) n * v[i][itr];
        }
    }
    FOR(i,1,n) {
        int vt = 0;
        FOR(j,1,n)
            if (!choose[j])
                if (!vt || isSmaller(j, vt, i)) vt = j;
        res.push_back(vt);
        choose[vt] = true;
    }
    FOR(i,0,n-2) cout << num[res[i]][i+1] << ' ' << den[res[i]][i+1] << "\n";
    FOR(i,0,n-1) cout << res[i] << ' ';
    return 0;
}
