/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Mainly from https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/COCI/official/2012/contest3_solutions/solutions.pdf
*/

#include <bits/stdc++.h>
#define FI first
#define SE second
#define EPS 1e-9
#define ALL(a) a.begin(), a.end()
#define SZ(a) int((a).size())
#define MS(s, n) memset(s, n, sizeof(s))
#define FOR(i, a, b) for (int i = (a); i <= (b); i++)
#define FORE(i, a, b) for (int i = (a); i >= (b); i--)
#define FORALL(it, a) for (__typeof((a).begin()) it = (a).begin(); it != (a).end(); it++)
//__builtin_ffs(x) return 1 + index of least significant 1-bit of x
//__builtin_clz(x) return number of leading zeros of x
//__builtin_ctz(x) return number of trailing zeros of x

using namespace std;
using ll = long long;
using ld = double;
typedef pair<ll, ll> II;
typedef pair<II, int> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;

const ll MODBASE = 1000000007LL;
const int MAXN = 100010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, m, T[MAXN], F[MAXN];
vector<II> a;
vector<ll> M, C;

ld getIntersection(int l1, int l2) {
    if (l2 == SZ(M)) return 1e20;
    return (ld) (C[l1] - C[l2]) / (M[l2] - M[l1]);
}

int query(ld k) {
    int dau = 0, cuoi = SZ(M) - 1;
    while (dau <= cuoi) {
        int mid = (dau + cuoi) >> 1;
        if (k <= getIntersection(mid, mid + 1)) cuoi = mid - 1;
        else dau = mid + 1;
    }
    return dau;
}

bool isBad(int l1, int l2, int l3) {
    // bad when intersection of l1 and l3 is to the left of intersection of l1 and l2 
    // intersection(l1,l2) has x-coordinate (c1-c2)/(m2-m1)
    // intersection(l1,l3) has x-coordinate (c1-c3)/(m3-m1)
    return (ld) (C[l3] - C[l1]) / (M[l1] - M[l3]) < (ld) (C[l2] - C[l1]) / (M[l1] - M[l2]);
}

void add(ll m, ll c) {
    M.push_back(m);
    C.push_back(c);
    while (SZ(M) >= 3 && isBad(SZ(M) - 3, SZ(M) - 2, SZ(M) - 1)) {
        M.erase(M.end() - 2);
        C.erase(C.end() - 2);
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m;
    FOR(i,1,n) cin >> T[i];
    FOR(i,1,m) cin >> F[i];

    // f(x) = F[i] * S[j+1] - F[i+1] * S[j]
    // => f'(x) = f(x) / F[i+1] = (F[i] / F[i+1]) * S[j+1] - S[j] = S[j+1] * x - S[j]
    ll last = 0;
    FOR(i,1,n) {
        a.push_back(II(last + T[i], -last));
        last += T[i];
    }
    // sort by the slope
    sort(ALL(a));

    // corner case
    if (n == 1) {
        ll res = 0;
        FOR(i,1,m) res += F[i];
        res *= T[1];
        cout << res;
        return 0;
    }

    // init lines y = Mx + C
    M.push_back(a[0].FI); M.push_back(a[1].FI);
    C.push_back(a[0].SE); C.push_back(a[1].SE);

    // adding new lines
    FOR(i,2,SZ(a)-1) add(a[i].FI, a[i].SE);

    // starting with the last segment and adding difference of each consecutive pair of segments
    ll res = last * F[m];
    FOR(i,2,m) {
        int pos = query((ld) F[i-1] / F[i]);
        // we need to calculate f(x), not f'(x)
        res += M[pos] * F[i-1] + C[pos] * F[i];
    }
    cout << res;
    return 0;
}
