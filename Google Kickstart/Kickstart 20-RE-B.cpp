/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - There are A buildings that are visible to the first person, there are B buildings that
        are visible to the second person, and there are C buildings that are visible to both of them.
        - As the first person will see buildings with height increasing, and so would the second person.
        Then there are A - C buildings that are solely visible to the first person and there are B - C 
        buildings that are solely visible to the second person.
        - The idea is to put A-C buildings with height n-1 (from left), B buildings with height n (in the middle) 
        and B-C buildings with height n-1 (from right), the remaining buildings would have 1 as their height. 
        - But there is a problem, what if A-C == 0 or B-C == 0? We should place a n-1 height building at the
        right of A-C group or at the left of B-C group if such things happen.
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
const int MAXN = 110;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int res[MAXN];
vector<int> f[MAXN];

bool check(int n, int a, int b, int c) {
    if (n == 1) {
        res[1] = 1;
        return true;
    }
    MS(res, 0);
    a -= c;
    b -= c;
    if (a + b + c > n) return false;
    FOR(i,1,n) res[i] = 0;
    FOR(i,1,a) {
        res[i] = n-1;
        if (res[i] == 0) return false;
    }
    FORE(i,n,n-b+1) {
        res[i] = n-1;
        if (res[i] == 0) return false; 
    }
    int C = c;
    if (a == 0) {
        if (C) {
            res[1] = n;
            C--;
        }
        else return false;
    }
    if (b == 0) {
        if (C) {
            res[n] = n;
            C--;
        }
        else return false;
    }
    FOR(i,1,n)
        if (res[i] == 0 && C) {
            res[i] = n;
            C--;
        } 
    FOR(i,1,n)
        if (res[i] == 0) res[i] = 1;

    // check again for sure
    int highest = 1, cntA = 0, cntB = 0, cntC = 0;
    FOR(i,1,n) f[i].clear();
    FOR(i,1,n)
        if (res[i] >= highest) {
            f[i].push_back(1);
            highest = res[i];
        }
    highest = 1;
    FORE(i,n,1)
        if (res[i] >= highest) {
            f[i].push_back(2);
            highest = res[i];
        }
    FOR(i,1,n)
        if (SZ(f[i]) == 1) {
            if (f[i][0] == 1) cntA++;
            else cntB++;
        } else if (SZ(f[i]) == 2) {
            cntC++;
        }
    return cntA == a && cntB == b && cntC == c;
}

// for subtest 1 only
bool dq(int u, int n, int a, int b, int c) {
    if (u > n) {
        int highest = 1, cntA = 0, cntB = 0, cntC = 0;
        FOR(i,1,n) f[i].clear();
        FOR(i,1,n)
            if (res[i] >= highest) {
                f[i].push_back(1);
                highest = res[i];
            }
        highest = 1;
        FORE(i,n,1)
            if (res[i] >= highest) {
                f[i].push_back(2);
                highest = res[i];
            }
        FOR(i,1,n)
            if (SZ(f[i]) == 1) {
                if (f[i][0] == 1) cntA++;
                else cntB++;
            } else if (SZ(f[i]) == 2) {
                cntA++;
                cntB++;
                cntC++;
            }
        return cntA == a && cntB == b && cntC == c;
    }
    FOR(i,1,n) {
        res[u] = i;
        if (dq(u+1, n, a, b, c)) return true;
    }
    return false;
}

bool checkTrau(int n, int a, int b, int c) {
    return dq(1, n, a, b, c);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    // for subtest 1 only
    // FOR(n,1,5)
    //     FOR(c,1,n)
    //         FOR(a,c,n)
    //             FOR(b,c,n) {
    //                 cout << n << ' ' << a << ' ' << b << ' ' << c << ": ";
    //                 if (!check(n, a, b, c)) {
    //                     if (!checkTrau(n, a, b, c)) cout << "IMPOSSIBLE\n";
    //                         else {
    //                             cout << "WA ";
    //                             FOR(i,1,n) cout << res[i] << ' ';
    //                             cout << "\n";
    //                         }
    //                 }
    //                 else {
    //                     FOR(i,1,n) cout << res[i] << ' ';
    //                     cout << "\n";
    //                 }
    //             }
    int te;
    cin >> te;
    FOR(o,1,te) {
        cout << "Case #" << o << ": ";
        int n, a, b, c;
        cin >> n >> a >> b >> c;
        if (!check(n, a, b, c)) {
            cout << "IMPOSSIBLE\n";
            continue;
        }
        FOR(i,1,n) cout << res[i] << ' ';
        cout << "\n";
    }
    return 0;
}
