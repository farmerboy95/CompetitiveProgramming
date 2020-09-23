/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - We define types of chains like this (let X is a digit)
            ... -> 0
            XXX -> 1
            X.. -> 2
            .X. -> 3
            ..X -> 4
            XX. -> 5
            X.X -> 6
            .XX -> 7
        - We first check if all chains are in type 0 => return 0
        - We get max value of each chain (beware of chain type 6)
        - Now we form the max result like this
            (Chain type 4 or 7) + (Many chain type 1) + (Chain type 2 or 5)
        - Something is missing here, yes, type 6 can be used in both left or right if possible.
        - So we calculate the result with 0 type 6, 1 type 6 (left or right) and 2 type 6 (both left
        and right).
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

class DengklekMakingChains {
    public:

    int getType(string &s) {
        bool f[3];
        FOR(i,0,2) f[i] = (s[i] != '.');
        if (!f[0] && !f[1] && !f[2]) return 0;
        if (f[0] && f[1] && f[2]) return 1;
        if (f[0] && !f[1] && !f[2]) return 2;
        if (!f[0] && f[1] && !f[2]) return 3;
        if (!f[0] && !f[1] && f[2]) return 4;
        if (f[0] && f[1] && !f[2]) return 5;
        if (f[0] && !f[1] && f[2]) return 6;
        return 7;
    }

    int getVal(string &s) {
        int res = 0;
        FOR(i,0,2)
            if (s[i] >= '0' && s[i] <= '9') res += s[i] - '0';
        return res;
    }

    int maxBeauty(vector<string> a) {
        int n = SZ(a);
        vector<string> b[8];
        int res = 0;
        FOR(i,0,n-1) {
            int t = getType(a[i]);
            b[t].push_back(a[i]);
            if (t != 6) res = max(res, getVal(a[i]));
            else res = max(res, max(a[i][0] - '0', a[i][2] - '0'));
        }
        if (SZ(b[0]) == n) return res;
        int now = 0;
        FOR(i,0,SZ(b[1])-1) now += getVal(b[1][i]);

        int maxLef = 0;
        FOR(i,0,SZ(b[4])-1) maxLef = max(maxLef, getVal(b[4][i]));
        FOR(i,0,SZ(b[7])-1) maxLef = max(maxLef, getVal(b[7][i]));

        int maxRig = 0;
        FOR(i,0,SZ(b[2])-1) maxRig = max(maxRig, getVal(b[2][i]));
        FOR(i,0,SZ(b[5])-1) maxRig = max(maxRig, getVal(b[5][i]));

        res = max(res, maxLef + maxRig + now);

        int maxLef6 = 0;
        FOR(i,0,SZ(b[6])-1) maxLef6 = max(maxLef6, b[6][i][2] - '0');
        int maxRig6 = 0;
        FOR(i,0,SZ(b[6])-1) maxRig6 = max(maxRig6, b[6][i][0] - '0');

        res = max(res, maxLef6 + maxRig + now);
        res = max(res, maxLef + maxRig6 + now);

        FOR(i,0,SZ(b[6])-1)
            FOR(j,0,SZ(b[6])-1) {
                if (i == j) continue;
                // i lef, j rig
                res = max(res, now + b[6][i][2] - '0' + b[6][j][0] - '0');
            }

        return res;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    DengklekMakingChains s;
    cout << s.maxBeauty({"3.6"}) << endl;
    cout << s.maxBeauty({".15", "7..", "402", "..3"}) << endl;
    cout << s.maxBeauty({"..1", "7..", "567", "24.", "8..", "234"}) << endl;
    cout << s.maxBeauty({"...", "..."}) << endl;
    cout << s.maxBeauty({"16.", "9.8", ".24", "52.", "3.1", "532", "4.4", "111"}) << endl;
    cout << s.maxBeauty({"..1", "3..", "2..", ".7."}) << endl;
    cout << s.maxBeauty({"412", "..7", ".58", "7.8", "32.", "6..", "351", "3.9", "985", "...", ".46"}) << endl;
    return 0;
}
