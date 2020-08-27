/*
    Author: Nguyen Tan Bao
    Statement: https://www.facebook.com/codingcompetitions/hacker-cup/2012/qualification-round/problems/A
    Status: AC
    Idea:
        - Count number of each character in the string HACKERCUP, put in cnt[i]
        - Do the same thing with input, put in cnt2[i], then res = min(cnt2[i] / cnt[i]) with i is 
        a character in HACKERCUP
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

int cnt[26], cnt2[26];
string s;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int te;
    cin >> te;
    string t = "HACKERCUP";
    FOR(i,0,SZ(t)-1) cnt[t[i] - 'A']++;
    getline(cin, s);
    FOR(o,1,te) {
        cout << "Case #" << o << ": ";
        getline(cin, s);
        FOR(i,0,25) cnt2[i] = 0;
        FOR(i,0,SZ(s)-1)
            if (s[i] == ' ') continue;
            else cnt2[s[i] - 'A']++;
        int res = 1e9;
        FOR(i,0,25)
            if (cnt[i]) res = min(res, cnt2[i] / cnt[i]);
        cout << res << "\n";
    }
    return 0;
}
