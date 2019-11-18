/*
    Author: Nguyen Tan Bao
    Status: AC
    Statement: 
        - Given N (1 <= N <= 20000) list of strings, each list contains K (1 <= K <= 15) strings, each string has P (1 <= P <= 30) characters (1)
        - Given list of string which has length M (1 <= M <= 30000), each string has P characters. (2)
        - Given Q queries,
            + for each query, we have X (0 <= X <= 30) and K numbers, they are indices of strings in (2)
            + get K strings from list (2), let them y1, y2, y3 ... yk
            + print out the number of lists in (1) which have F = min(lcp(x1, y1), lcp(x2, y2), ..., lcp(xk, yk)) = X
    Idea:
        - Basically, we count (number of lists in (1) which have F >= X) - (number of lists in (1) which have F >= X+1) (3)
        - Handling queries offline, sort all queries by X
        - Use map to save number of strings formed by concat(charAt1) + concat(charAt2) + ... + concat(charAtX)
            + For example, string list abcd efgh => aebfcgdh, this is more effective than abcdefgh, as we can add concat(char at i+1) easily
        - For each query, reform the string list to X and X+1, use (3) to calculate the result.
        - Remember to increase map data as X is increasing.
        - Remember to handle corner cases (X = 0 or X > P)
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
const int MAXN = 20010;
const int MAXM = 30010;
const int MAXK = 16;
const int MAXQ = 200010;

struct Data {
    int x, cs;
    vector<int> a;
    Data(int x = 0, int cs = 0, vector<int> a = {}) : x(x), cs(cs), a(a) {}
};

bool operator< (Data a, Data b) {
    return a.x < b.x;
}

int n, k, m, p, q, res[MAXN];
string s[MAXN][MAXK], b[MAXM], s3[MAXN][MAXK];
vector<Data> Q;
unordered_map<string, int> ma[2];
string SS[MAXN];
int mainMap;

void inc(int &now) {
    now++;
    mainMap = 1-mainMap;
    ma[1-mainMap].clear();
    if (now == p) return;
    FOR(i,1,n) {
        FOR(j,1,k) SS[i] += s[i][j][now];
        ma[1-mainMap][SS[i]]++;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    freopen("sabin.in", "r", stdin);
    freopen("sabin.out", "w", stdout);
    cin >> n >> k >> m >> p >> q;
    FOR(i,1,n)
        FOR(j,1,k) {
            cin >> s[i][j];
            s[i][j] += " ";
        }
    FOR(i,1,m) {
        cin >> b[i];
        b[i] += " ";
    }
    FOR(i,1,q) {
        int x;
        cin >> x;
        Data d;
        d.x = x;
        d.cs = i;
        FOR(j,1,k) {
            cin >> x;
            d.a.emplace_back(x);
        }
        Q.emplace_back(d);
    }
    sort(ALL(Q));

    FOR(i,1,n) {
        FOR(j,1,k) SS[i] += s[i][j][0];
        ma[0][SS[i]]++;
    }
    FOR(i,1,n) {
        FOR(j,1,k) SS[i] += s[i][j][1];
        ma[1][SS[i]]++;
    }
    int now = 1;
    mainMap = 0;

    FOR(i,0,q-1) {
        if (Q[i].x > p) {
            res[Q[i].cs] = 0;
            continue;
        }
        if (Q[i].x == 0) {
            string S = "";
            FOR(j,0,SZ(Q[i].a)-1) S += b[Q[i].a[j]][0];
            res[Q[i].cs] = n;
            if (ma[mainMap].count(S)) res[Q[i].cs] -= ma[mainMap][S];
            continue;
        }
        while (now < Q[i].x) inc(now);
        
        string S = "", S2 = "";
        FOR(z,0,Q[i].x) {
            FOR(j,0,SZ(Q[i].a)-1) {
                if (z < Q[i].x) S += b[Q[i].a[j]][z];
                if (now < p) S2 += b[Q[i].a[j]][z];
            }
        }
        if (ma[mainMap].count(S)) res[Q[i].cs] = ma[mainMap][S];
        if (now < p)
            if (ma[1-mainMap].count(S2)) res[Q[i].cs] -= ma[1-mainMap][S2];
    }

    FOR(i,1,q) cout << res[i] << "\n";
    return 0;
}
