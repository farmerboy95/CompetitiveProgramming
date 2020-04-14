/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: 
        - Mainly from https://github.com/win11905/submission/blob/master/OCN/16/1B.cpp
        - Use a strategy to ask until 2 beeps are heard, and the index of the special button is uniquely
        determined.
        - First, we ask [1 ... n/2] and [n/2 ... 1], then ask [n/2+1 ... n] and [n ... n/2+1], we
        can draft some cases in paper to know how it's uniquely determined. If it's not enough to 
        get 2 beeps, keep asking 1 until we hear, this will take at most 3*n times of asking. After 
        getting 2 beeps, we know where the special button is, then we can just ask that button 2*n
        remaining times to get n beeps. Total 5*n times.
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

int n, m, q, step;
string s;
vector<int> guess, res;
map<vector<int>, int> ma;

void gue(int u) {
    cout << u << "\n";
    cout.flush();
    cin >> s;
    if (s[0] == 'B') res.push_back(step);
    step++;
}

void check() {
    if (ma.count(res)) {
        int x = ma[res];
        FOR(i,1,2*n) gue(x);
        exit(0);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> s >> n >> m >> q;
    FOR(i,1,n/2) guess.push_back(i);
    FORE(i,n/2,1) guess.push_back(i);
    // it does not matter that the remaining part can be larger sometimes, 
    // the N-silent-times condition can still be achieved.
    FOR(i,n/2+1,n) guess.push_back(i);
    FORE(i,n,n/2+1) guess.push_back(i);

    // as positions of 2 beeps are unique, push those positions into a map to determine
    FOR(k,0,n-1)
        FOR(i,1,n) {
            vector<int> now;
            FOR(j,0,SZ(guess)-1)
                if (guess[j] == i) {
                    int idx = j + k;
                    now.push_back(idx);
                }
            ma[now] = i;
        }
    for (auto x : guess) {
        gue(x);
        check();
    }
    while (1) {
        gue(1);
        check();
    }
    return 0;
}
