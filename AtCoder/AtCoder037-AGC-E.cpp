/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: https://img.atcoder.jp/agc037/editorial.pdf (page 12)
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
const int MAXN = 5010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

string rev(string &s) {
    string t = s;
    reverse(ALL(t));
    return t;
}

int n, k, f[MAXN * 2];
string s, res = "";

void solve(string str, int k) {
    // for each string, the next choice is uniquely determined as we take all characters
    // that are the same as last character "last" in "str"
    FOR(i,1,k) {
        char last = str[SZ(str)-1];
        string u = str + rev(str);
        int r = n-1;
        FOR(j,n,2*n-1)
            if (u[j] == last) r++;
            else break;
        str = u.substr(r-n+1, n);
    }
    // note that it does not matter that the consecutive "last" character should come at
    // the beginning when i == K, we can simply reverse it (as we can choose string or reverse
    // of that string in u)
    str = rev(str);
    if (SZ(res) == 0) res = str;
    else if (res > str) res = str;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> k;
    cin >> s;

    // create u, let a be the lexicographically smallest letter that appears in s
    string u = s + rev(s);
    char a = s[0];
    FOR(i,0,n-1) a = min(a, s[i]);
    FOR(i,0,SZ(u)-1)
        if (i == 0) f[i] = (u[i] == a);
        else {
            if (u[i] == a) f[i] = f[i-1] + 1;
            else f[i] = 0;
        }
    // Let L be the maximum length of consecutive occurrences of a in U (in the beginning)
    int L = 0;
    FOR(i,0,SZ(u)-1) L = max(L, f[i]);

    // if 2^(k-1) * L > N, the resulting string simply contains all a
    if (k > 15) {
        FOR(i,1,n) cout << a;
        return 0;
    }

    int sum = 1;
    FOR(i,1,k-1) sum *= 2;
    sum *= L;

    if (sum > n) {
        FOR(i,1,n) cout << a;
        return 0;
    } 

    // otherwise, we consider all n-length string in u (k now is about 14 max)
    FOR(i,0,n) solve(u.substr(i, n), k-1);
    cout << res;
    return 0;
}
