/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - First, find the number of a and b in the string
            + Check with a 300-length string "aaaa..aa" we would get p = nb + x (1)
            + Check with a 300-length string "aaaa..aa" we would get q = na + x (2)
            + x = 300 - n => n + x = 300
            => p + q = na + nb + 2*x = n + x + x = 300 + x
            => x = p + q - 300
            => na and nb
        - Now we have n queries left
        - We would have to check each character i from n to 1, we check string "aaaa...a" + ("a" / "b" at i) + determined characters
        - Compare character at i and choose the suitable one.
        - But it would cost us n+1 queries
        - Actually we don't need to query "aaa..aa" (n characters "a") because we can get its answer at (1), it would be nb
        (note that if nb = 0, just requery it and exit)
        => We only need to query n+2 times
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
typedef pair<ll, ll> II;
typedef pair<II, ll> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;
 
const ll MODBASE = 1000000007LL;
const int MAXN = 310;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

map<string, int> ma;
int a[MAXN], b[MAXN], n, na, nb;

int query(string s) {
    if (ma.count(s)) return ma[s];
    cout << s << endl;
    int x;
    cin >> x;
    if (x <= 0) exit(0);
    ma[s] = x;
    return x;
}

int blindCheck(char ch) {
    string s = "";
    FOR(i,1,300) s += ch;
    return query(s);
}

int realCheck(int len, char ch) {
    string s = "";
    FOR(i,1,n)
        if (i < len) {
            s += 'a';
        }
        else if (i == len) {
            s += ch;
        }
        else {
            if (b[i] == 0) s += 'a';
            else s += 'b';
        }
    if (len == n && ch == 'a') {
        if (nb) ma[s] = nb;
    }
    return query(s);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int p = blindCheck('a');
    int q = blindCheck('b');
    int x = p + q - 300;
    n = p + q - 2 * x;
    na = q - x;
    nb = p - x;
    FOR(i,1,n) b[i] = -1;
    FORE(i,n,1) {
        int g = realCheck(i, 'a');
        int h = realCheck(i, 'b');
        if (g < h) b[i] = 0;
        else b[i] = 1;
    }
    return 0;
}
