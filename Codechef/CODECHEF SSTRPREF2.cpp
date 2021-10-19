/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - The idea is to separate the substring into 2 parts: P and Q. Let's fix the Q and find
        all the P to update
        - To find the longest prefix of S2 that can be placed to position i of string X, we can
        use Z algorithm then sort the indices of X decreasingly by the Z values.
        - For P, we can use KMP to find the longest prefix that can be placed to position i (the
        end of the prefis is placed at i), put them all into "match" array.
        - Ok, let's iterate through all the Z values decreasingly, let it be p, let i be the 
        position of this Z value. We clearly can place Q at i, and there are p+1 such Qs, the
        problem now is to find all the P to update, but we only have match[i-1] as the longest
        prefix of S1, we cannot do the same as Q in this case.
        - Let kq[w] = number of Qs when len(P) = w, we can move match[i-1] back and update kq.
        But one thing happens, there are so many kq[w] to update. Here is the place where iterating
        through decreasing Z values shines. Since we get the greatest value for kq[w], we can ignore
        updating it in the next Z values, and the update for kq is O(n)
        - But there is something missing, we have not considered the case when P is not empty and Q
        is empty and placed at the end of the string S2, we can brute force to solve it. Note that
        we only update the result when kq[w] is not set only, otherwise we will recalculate some
        values.
*/

#include <bits/stdc++.h>
#define FI first
#define SE second
#define ALL(a) a.begin(), a.end()
#define SZ(a) int((a).size())
#define MS(s, n) memset(s, n, sizeof(s))
#define FOR(i,a,b) for (int i = (a); i <= (b); i++)
#define FORE(i,a,b) for (int i = (a); i >= (b); i--)
#define FORALL(it, a) for (__typeof((a).begin()) it = (a).begin(); it != (a).end(); it++)
#define TRAV(x, a) for (auto &x : a)

using namespace std;
using ll = long long; using ld = double; 
using pi = pair<int, int>; using pl = pair<ll, ll>; using pd = pair<ld, ld>;
using cd = complex<ld>; using vcd = vector<cd>;

using vi = vector<int>; using vl = vector<ll>;
using vd = vector<ld>; using vs = vector<string>;
using vpi = vector<pi>; using vpl = vector<pl>; using vpd = vector<pd>; // vector<pair>

template<class T> using min_pq = priority_queue<T, vector<T>, greater<T> >;
template<class T> inline int ckmin(T& a, const T& val) { return val < a ? a = val, 1 : 0; }
template<class T> inline int ckmax(T& a, const T& val) { return a < val ? a = val, 1 : 0; }
template<class T> void remDup(vector<T>& v) { sort(ALL(v)); v.erase(unique(ALL(v)), end(v)); }

constexpr int pct(int x) { return __builtin_popcount(x); } // # of bits set
constexpr int bits(int x) { return x == 0 ? 0 : 31-__builtin_clz(x); } // floor(log2(x)) 
constexpr int p2(int x) { return 1<<x; }
constexpr int msk2(int x) { return p2(x)-1; }

ll ceilDiv(ll a, ll b) { return a / b + ((a ^ b) > 0 && a % b); } // divide a by b rounded up
ll floorDiv(ll a, ll b) { return a / b - ((a ^ b) < 0 && a % b); } // divide a by b rounded down
void setPrec(int x) { cout << fixed << setprecision(x); }

// TO_STRING
#define ts to_string
string ts(char c) { return string(1, c); }
string ts(const char* s) { return (string) s; }
string ts(string s) { return s; }
string ts(bool b) { return ts((int)b); }
template<class T> string ts(complex<T> c) { stringstream ss; ss << c; return ss.str(); }
template<class T> using V = vector<T>;
string ts(V<bool> v) {string res = "{"; FOR(i,0,SZ(v)-1) res += char('0'+v[i]); res += "}"; return res; }
template<size_t sz> string ts(bitset<sz> b) { string res = ""; FOR(i,0,SZ(b)-1) res += char('0'+b[i]); return res; }
template<class T, class U> string ts(pair<T,U> p);
template<class T> string ts(T v) { // containers with begin(), end()
    bool fst = 1; string res = "";
    for (const auto& x: v) { if (!fst) res += " "; fst = 0; res += ts(x); }
    return res;
}
template<class T, class U> string ts(pair<T,U> p) { return "("+ts(p.FI)+", "+ts(p.SE)+")"; }

// OUTPUT
template<class T> void pr(T x) { cout << ts(x); }
template<class T, class ...U> void pr(const T& t, const U&... u) { pr(t); pr(u...); }
void ps() { pr("\n"); } // print w/ spaces
template<class T, class ...U> void ps(const T& t, const U&... u) { pr(t); if (sizeof...(u)) pr(" "); ps(u...); }

// DEBUG
void DBG() { cerr << "]" << endl; }
template<class T, class ...U> void DBG(const T& t, const U&... u) { cerr << ts(t); if (sizeof...(u)) cerr << ", "; DBG(u...); }
#define dbg(...) cerr << "Line(" << __LINE__ << ") -> [" << #__VA_ARGS__ << "]: [", DBG(__VA_ARGS__)
#define chk(...) if (!(__VA_ARGS__)) cerr << "Line(" << __LINE__ << ") -> function(" \
        << __FUNCTION__  << ") -> CHK FAILED: (" << #__VA_ARGS__ << ")" << "\n", exit(0);

const ld PI = acos(-1.0);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
const ld EPS = 1e-9;
const ll MODBASE = 1000000007LL;
const int INF = 0x3f3f3f3f;

const int MAXN = 1000010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

string S1, S2, X;
vi ZS2X;
int kq[MAXN];

bool cmp(int u, int v) {
    return ZS2X[u] > ZS2X[v];
}

void ZFunction(string &s, vi &z, int prefixLength) {
    int L = 0, R = 0;
    vi Z(SZ(s));
    Z[0] = SZ(s);
    FOR(i,1,SZ(s)-1) {
        if (i > R) {
            L = R = i;
            while (R < SZ(s) && s[R] == s[R-L]) R++;
            Z[i] = R-L; 
            R--;
        }
        else {
            int k = i-L;
            if (Z[k] < R-i+1) Z[i] = Z[k];
            else {
                L = i;
                while (R < SZ(s) && s[R] == s[R-L]) R++;
                Z[i] = R-L;
                R--;
            }
        }
    }
    z.clear();
    FOR(i,prefixLength+1,SZ(s)-1) z.push_back(Z[i]);
}

void kmpPreprocess(string &s, vi &b) {
    b.clear();
    b.push_back(0);
    FOR(i,1,SZ(s)-1) {
        int k = b[i-1];
        while (k > 0 && s[k] != s[i]) k = b[k-1];
        if (s[k] == s[i]) b.push_back(k+1);
        else {
            k = 0;
            b.push_back(0);
        }
    }
}

void kmpSearch(string &s, string &t, vi &b, vi &match) {
    // find t in s
    int j = 0;
    match.clear();
    FOR(i,0,SZ(s)-1) {
        while (j > 0 && s[i] != t[j]) j = b[j-1];
        if (s[i] == t[j]) j++;
        else j = 0;
        match.push_back(j);
        if (j == SZ(t)) j = b[j-1];
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int te;
    cin >> te;
    while (te--) {
        cin >> S1 >> S2 >> X;

        string S2X = S2 + "#" + X;
        ZFunction(S2X, ZS2X, SZ(S2));
        vi g;
        FOR(i,0,SZ(ZS2X)-1) g.push_back(i);
        sort(ALL(g), cmp);

        vi tmp, match;
        kmpPreprocess(S1, tmp);
        kmpSearch(X, S1, tmp, match);
        FOR(i,0,SZ(S1)) kq[i] = -1;

        FOR(i,0,SZ(g)-1) {
            int pos = g[i], lenQ = ZS2X[pos];
            int j = 0;
            if (pos > 0) j = match[pos-1];
            while (j >= 0 && kq[j] == -1) {
                kq[j] = lenQ + 1;
                if (j == 0) j = -1;
                else j = tmp[j-1];
            }
        }
        
        ll res = 0;
        FOR(i,0,SZ(S1)) {
            if (kq[i] == -1) continue;
            res += kq[i];
        }

        // non-empty P + empty Q (P as X's suffix) was not considered
        int j = match[SZ(X)-1];
        while (j > 0) {
            if (kq[j] == -1) res++;
            j = tmp[j-1];
        }

        cout << res << "\n";
    }
    return 0;
}
