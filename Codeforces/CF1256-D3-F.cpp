/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Find the occurence of each character from 'a' to 'z' in S and T, if there is one character ch
        that cntS[ch] != cntT[ch] => NO
        - We only use reverse string with length 2. More formally, we consider swapping 2 adjacent characters.
        - Find the number of swap needed to sort all character in S (opS) and T (opT)
        - If there is one character ch that cntS[ch] > 1 => YES, as we can swap these 2 identical characters in
        for example string S, and continue to sort string T
        - Otherwise, if opS and opT have different parity => NO, else => YES, as we can sort one string and keep
        swapping the same one pair of characters of the other string
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
typedef pair<int, II> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;
 
const ll MODBASE = 1000000007LL;
const int MAXN = 200010;
const int MAXM = 10010;
const int MAXK = 110;
const int MAXQ = 200010;

int q, n, cntS[26], cntT[26], cnt[26];
string s, t;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> q;
    while (q--) {
        cin >> n;
        cin >> s >> t;
        FOR(i,0,25) cntS[i] = cntT[i] = 0;
        FOR(i,0,n-1) {
            cntS[s[i] - 'a']++;
            cntT[t[i] - 'a']++;
        }
        bool co = true;
        FOR(i,0,25)
            if (cntS[i] != cntT[i]) co = false;
        if (!co) {
            cout << "NO\n";
            continue;
        }

        FOR(i,0,25) cnt[i] = 0;
        ll opS = 0, opT = 0;
        FOR(i,0,n-1) {
            int g = s[i] - 'a';
            FOR(j,g+1,25) opS += cnt[j];
            cnt[g]++;
        }

        FOR(i,0,25) cnt[i] = 0;
        FOR(i,0,n-1) {
            int g = t[i] - 'a';
            FOR(j,g+1,25) opT += cnt[j];
            cnt[g]++;
        }

        co = false;
        FOR(i,0,25)
            if (cntS[i] > 1) co = true;

        if (!co) {
            if (abs(opS - opT) % 2) cout << "NO\n";
            else cout << "YES\n";
        }
        else cout << "YES\n";

    }
    return 0;
}