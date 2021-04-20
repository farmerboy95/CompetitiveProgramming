/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - https://raw.githubusercontent.com/veljko02/CompetitiveProgramming/master/CodeChef/subsets.cpp
        - Firstly, notice that we basically have a graph with n nodes and we want to find 
        the number of its complete subgraphs. It is natural to try some meet in the middle, 
        so let's divide the nodes into two halves. Now, we can easily compute for each subset 
        of both halves whether the resulting subgraph is complete in O(n*2^(n/2)). Now, it is 
        quite natural to try to fix a subset from the first half and count how many subsets of 
        the second half give a complete subgraph. In order to do so, we can firstly take care 
        of edges between the two halves. We can do that just by passing over all the nodes in 
        the second half and checking whether it is connected to all of the chosen nodes in the 
        already fixed subset of the first half. Then all it remains for us to do is to check 
        how many subsets of those vertices in the second half are complete in fact and we can 
        do that by SOS dp in O(n*2^(n/2)).
        - Do not use vector and push_back at line 146, 149 as it costs a lot of time => TLE
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

const int MAXN = 45;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int nt[230010], n, adj[MAXN][MAXN], len[2], closure[2000000][2], f[2000000];
ll a[MAXN];
vl primes;
pi seg[2];

void sieveBase(int n) {
    FOR(i,2,n) {
        if (nt[i] == 0) {
            primes.push_back(i);
            nt[i] = i;
            for (ll j = (ll) i * i; j <= n; j += i) nt[j] = i;
        }
    }
}

bool ok(ll u) {
    TRAV(x, primes) {
        ll g = x * x * x;
        if (u % g == 0) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    sieveBase(230000);

    int te;
    cin >> te;
    while (te--) {
        cin >> n;
        FOR(i,0,n-1) cin >> a[i];

        // build adjacent matrix
        FOR(i,0,n-1)
            FOR(j,i+1,n-1) adj[i][j] = adj[j][i] = ok(a[i] * a[j]);
        
        // meet-in-the-middle, divide n points into 2 parts
        seg[0].FI = 0; seg[0].SE = (n-1) / 2;
        seg[1].FI = seg[0].SE + 1; seg[1].SE = n-1;

        // closure[mask] = 1 when graph created by mask is a closure
        FOR(part,0,1) {
            len[part] = seg[part].SE - seg[part].FI + 1;

            FOR(mask,0,(1<<len[part])-1) {
                closure[mask][part] = 1;
                if (pct(mask) < 2) continue;

                int g[2], cnt = 0;
                FOR(i,0,len[part]-1) {
                    if (mask & (1<<i)) {
                        g[cnt++] = i;
                        closure[mask][part] &= closure[mask ^ (1<<i)][part];
                        if (cnt == 2) break;
                    }
                }
                closure[mask][part] &= adj[g[0] + seg[part].FI][g[1] + seg[part].FI];
            }
        }

        // sos dp to count the number of closures that are subset of a mask
        FOR(i,0,len[1]-1)
            FOR(mask,0,(1<<len[1])-1) 
                if (mask & (1<<i)) closure[mask][1] += closure[mask ^ (1<<i)][1];

        // f[i] = the set of left half nodes that i + seg[1].FI can connect
        FOR(i,seg[1].FI,seg[1].SE) {
            int mask = 0;
            FOR(j,seg[0].FI,seg[0].SE)
                if (adj[i][j]) mask |= (1<<j);
            f[i - seg[1].FI] = mask;
        }

        ll res = 0;
        FOR(mask,0,(1<<len[0])-1) {
            if (closure[mask][0] == 0) continue;

            // vi vertices;
            // FOR(i,0,len[0]-1)
            //     if (mask & (1<<i)) vertices.push_back(i);

            // rightMask is the set of right half nodes that they can all connect to the set of nodes in mask
            int rightMask = 0;
            FOR(i,seg[1].FI,seg[1].SE) {
                // bool co = true;
                // TRAV(x, vertices) 
                //     if (adj[x][i] == 0) {
                //         co = false;
                //         break;
                //     }
                // if (co) rightMask += 1<<(i-seg[1].FI);

                // the commented code can be replaced by this to reduce the complexity
                if ((f[i - seg[1].FI] & mask) == mask) rightMask += 1<<(i-seg[1].FI);
            }

            res += closure[rightMask][1];
        }

        cout << res << "\n";
    }
    return 0;
}
