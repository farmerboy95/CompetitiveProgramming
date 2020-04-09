/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: Mainly from https://csacademy.com/contest/ioi-2016-training-round-5/task/balanced-string/solution/
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

int t;
string s;

bool check(string s) {
    // simply a corner case
    if (SZ(s) == 0) return true;

    // compress consecutive A and B into element (number of consecutive chars, the character)
    char ch = s[0];
    int cnt = 1;
    vector<pair<int, char> > cp;
    FOR(i,1,SZ(s)-1)
        if (s[i] == ch) cnt++;
        else {
            cp.push_back(make_pair(cnt, ch));
            ch = s[i];
            cnt = 1;
        }
    cp.push_back(make_pair(cnt, ch));

    // if number of elements is 1, simply return true
    if (SZ(cp) == 1) return true;

    // there would be a case that the character at the end is the same as the one at the beginning
    // simply merge those 2 elements
    if (cp[SZ(cp)-1].SE == cp[0].SE) {
        cp[0].FI += cp[SZ(cp)-1].FI;
        cp.pop_back();
    }

    // check number of elements again for sure
    if (SZ(cp) == 1) return true;

    vector<int> encEven, encOdd;
    bool has2Even = false, has2Odd = false;

    // now assume first element is A, so second is B, third is A again and so on
    // here we have has2Odd = true if we have more than 1 A in one element, has2Even = true if we have more than 1 B
    FOR(i,0,SZ(cp)-1)
        if (i % 2) {
            encOdd.push_back(cp[i].FI);
            if (cp[i].FI > 1) has2Odd = true;
        }
        else {
            encEven.push_back(cp[i].FI);
            if (cp[i].FI > 1) has2Even = true;
        }

    // if we have both AA and BB, the string s will not be balanced
    if (has2Even && has2Odd) return false;

    // choose the string to be encoded, prefer the one that has has2 = true
    vector<int> encoding;
    if (has2Odd) encoding = encOdd;
    else encoding = encEven;

    // get Max and Min element of encoding array, their difference should be at most 1
    int Min = 1000000000, Max = 0;
    FOR(i,0,SZ(encoding)-1) {
        Min = min(Min, encoding[i]);
        Max = max(Max, encoding[i]);
    }
    if (Max - Min > 1) return false;
    else if (Max == Min) return true;

    // create new string based on encoding array
    string newS = "";
    FOR(i,0,SZ(encoding)-1)
        if (encoding[i] == Min) newS += 'A';
        else newS += 'B';
    
    // go back to the original problem but now the string is at least half size than s
    return check(newS);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> t;
    while (t--) {
        cin >> s;
        cout << check(s) << "\n";
    }
    return 0;
}
