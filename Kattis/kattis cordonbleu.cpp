/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Min Cost Matching using Hungarian Algorithm
        - n bottles on the left group and m couriers + (n-1) clone restaurant on the right.
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

const int MAXN = 1010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

struct HungarianAlgo {
    vi Lmate, Rmate;
    int n, m;
    vector<vi> cost;

    HungarianAlgo(int _N, int _M) {
        Lmate.resize(_N);
        Rmate.resize(_M);
        n = _N;
        m = _M;
        vi tmp(m);
        cost.clear();
        FOR(i,0,n-1) cost.push_back(tmp);
    }

    void setCost(int i, int j, int x) {
        // dbg(i, j, x);
        cost[i][j] = x;
    }

    void getMatching() {
        // min cost matching
        // Labelling: u[i] + v[j] <= A[i][j]

        // construct dual feasible solution
        vi u(n), v(m);
        FOR(i,0,n-1) {
            u[i] = cost[i][0];
            FOR(j,1,m-1) ckmin(u[i], cost[i][j]);
        }

        // FOR(j,0,m-1) {
        //     v[j] = cost[0][j] - u[0];
        //     FOR(i,1,n-1) ckmin(v[j], cost[i][j] - u[i]);
        // }

        // construct primal solution satisfying complementary slackness
        FOR(i,0,n-1) Lmate[i] = -1;
        FOR(i,0,m-1) Rmate[i] = -1;
        int mated = 0;
        FOR(i,0,n-1)
            FOR(j,0,m-1) {
                if (Rmate[j] != -1) continue;
                if (abs(cost[i][j] - u[i] - v[j]) == 0) {
                    Lmate[i] = j;
                    Rmate[j] = i;
                    mated++;
                    break;
                }
            }
        
        // repeat until primal solution is feasible
        vi dist(m);
        vi seen(m), dad(m);
        while (mated < n) {
            // find an unmatched left node
            int s = 0;
            while (Lmate[s] != -1) s++;

            // initialize Dijkstra
            fill(ALL(dad), -1);
            fill(ALL(seen), 0);
            FOR(k,0,m-1) dist[k] = cost[s][k] - u[s] - v[k];

            int j = 0;
            while (1) {
                // find closest
                j = -1;
                FOR(k,0,m-1) {
                    if (seen[k]) continue;
                    if (j == -1 || dist[k] < dist[j]) j = k;
                }
                seen[j] = 1;

                // termination condition
                if (Rmate[j] == -1) break;

                // relax neighbors
                int i = Rmate[j];
                FOR(k,0,m-1) {
                    if (seen[k]) continue;
                    ld newDist = dist[j] + cost[i][k] - u[i] - v[k];
                    if (dist[k] > newDist) {
                        dist[k] = newDist;
                        dad[k] = j;
                    }
                }
            }

            // update dual variables
            FOR(k,0,m-1) {
                if (k == j || !seen[k]) continue;
                int i = Rmate[k];
                v[k] += dist[k] - dist[j];
                u[i] -= dist[k] - dist[j];
            }
            u[s] += dist[j];
            // augment along path
            while (dad[j] >= 0) {
                int d = dad[j];
                Rmate[j] = Rmate[d];
                Lmate[Rmate[j]] = j;
                j = d;
            }
            Rmate[j] = s;
            Lmate[s] = j;
            mated++;
        }
    }

    ll getMatchingValue() {
        ll value = 0;
        FOR(i,0,n-1) value += cost[i][Lmate[i]];
        return value;
    }
};

int n, m, x[MAXN], y[MAXN], u[MAXN], v[MAXN], p, q;

int dist(int xx, int yy, int uu, int vv) {
    return abs(xx-uu) + abs(yy-vv);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m;
    FOR(i,0,n-1) cin >> x[i] >> y[i];
    FOR(i,0,m-1) cin >> u[i] >> v[i];
    cin >> p >> q;

    // n bottles - m courier + (n-1) clone restaurant
    HungarianAlgo hungarian(n, n-1 + m);
    FOR(i,0,n-1) {
        FOR(j,0,m-1) {
            hungarian.setCost(i, j, dist(u[j], v[j], x[i], y[i]) + dist(x[i], y[i], p, q));
        }
        FOR(j,m,m+n-2) {
            hungarian.setCost(i, j, dist(x[i], y[i], p, q) * 2);
        }
    }
    hungarian.getMatching();
    cout << hungarian.getMatchingValue();
    return 0;
}
