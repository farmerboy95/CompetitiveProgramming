/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: Fully from https://codeforces.com/blog/entry/53567
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

ll l, r;
int n, res, num[15], now[15];
vector<int> a, b;

bool exist(int l, int r) {
    // check if there exists an unused digit from digit l to digit r
    if (l > r) return false;
    FOR(i,l,r)
        if (now[i]) return true;
    return false;
}

bool dfs(int pos, int lFlag, int rFlag) {
    // cases like in the editorial
    if (pos == n) return true;
    int l = a[pos], r = b[pos];
    if (lFlag && rFlag) {
        if (l == r) {
            if (now[l]) {
                now[l]--;
                if (dfs(pos+1, 1, 1)) return true;
                now[l]++;
            }
            return false;
        }
        if (exist(l+1, r-1)) return true;
        if (now[l]) {
            now[l]--;
            if (dfs(pos+1, 1, 0)) return true;
            now[l]++;
        }
        if (now[r]) {
            now[r]--;
            if (dfs(pos+1, 0, 1)) return true;
            now[r]++;
        }
        return false;
    }
    else if (lFlag) {
        if (exist(l+1, 9)) return true;
        if (now[l]) {
            now[l]--;
            if (dfs(pos+1, 1, 0)) return true;
            now[l]++;
        }
    }
    else if (rFlag) {
        if (exist(0, r-1)) return true;
        if (now[r]) {
            now[r]--;
            if (dfs(pos+1, 0, 1)) return true;
            now[r]++;
        }
    }
    return false;
}

void go(int k, int len) {
    if (k == 10) {
        FOR(i,1,9) now[i] = num[i];
        // number of digit 0 is the remaining len
        now[0] = len;
        if (dfs(0,1,1)) res++;
        return;
    }
    // get the number of each digit from 1 to 9 using backtracking
    FOR(i,0,len) {
        num[k] = i;
        go(k+1, len-i);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> l >> r;
    // corner case
    if (l == r) {
        cout << 1;
        return 0;
    }
    // break the numbers l and r into digits
    while (l) {
        a.emplace_back(l % 10);
        l /= 10;
    }
    while (r) {
        b.emplace_back(r % 10);
        r /= 10;
    }
    // size of array a and b should be the same, we can add trailing zeroes to a
    while (SZ(a) != SZ(b)) a.emplace_back(0);
    reverse(ALL(a));
    reverse(ALL(b));
    n = SZ(b);

    go(1, n);
    cout << res;

    return 0;
}
