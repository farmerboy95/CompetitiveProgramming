/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Binary search the result as the greater the font is, the harder it could be put into 
        the billboard.
        - Put word by word into the billboard. Remember to put space between words in the same
        row.
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

int w, h;
string s, t;
vector<string> words;

bool check(int font) {
    int col = w / font;
    int row = h / font;

    FOR(i,0,SZ(words)-1)
        if (SZ(words[i]) > col) return false;

    int now = col, line = 0;
    FOR(i,0,SZ(words)-1) {
        t = words[i];
        if (now + 1 + SZ(t) > col) {
            now = 0;
            line++;
            if (line > row) return false;
        }
        if (now == 0) now += SZ(t);
        else now += 1 + SZ(t);
    }

    return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int te;
    cin >> te;
    FOR(o,1,te) {
        cout << "Case #" << o << ": ";
        cin >> w >> h;
        getline(cin, s);
        words.clear();
        stringstream sin(s);
        while (sin >> t) words.push_back(t);

        int dau = 1, cuoi = 1000;
        while (dau <= cuoi) {
            int mid = (dau + cuoi) >> 1;
            if (check(mid)) dau = mid+1;
            else cuoi = mid-1;
        }
        cout << cuoi << "\n";
    }
    return 0;
}
