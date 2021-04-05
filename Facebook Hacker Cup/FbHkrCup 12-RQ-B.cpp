/*
    Author: Nguyen Tan Bao
    Statement: https://www.facebook.com/codingcompetitions/hacker-cup/2012/qualification-round/problems/B
    Status: AC
    Idea:
        - Note that bargains and terrible deals are completely symmetrical under transformation 
        P’ = M + 1 – P, W’ = K + 1 – W. Therefore we only need to consider the bargains part of 
        the problem.
        - If the product is a bargain, it has minimum weight among all products with the same price. 
        Since the constraints on K and M are relatively low (at most 10^7), it’s possible to keep 
        track of the product with minimum weight for each particular price (Min[i]) and to consider only 
        these products in the rest of the solution. Also we should account for products with the 
        same weight and price by keeping the number of times each minimum occurs among products (occ[i]).
        - Let’s assume that these minimum weights have already been calculated. Then in order to find 
        all bargains we have to loop through all potential products in the order of increasing price, 
        maintaining current minimum of weight. If the next product weights less than the current 
        minimum, then it is in fact a bargain.
        - Notice that because of pseudorandomness the sequences of prices and weights are periodical, 
        maybe except for some small number of products in the beginning of the sequence. Even though 
        the full period of both product properties may be as large as K*M, we can take advantage of 
        the separate periods for price and weights.
        - First, we process the non-periodic part of the product sequence and determine the periods 
        of prices and weight — let them be periodP and periodW.
        - Consider all products that have price P[s], s < periodP. These are products with indices 
        s + i * periodP, i = 0, 1, .., ceil((N-s) / periodP)-1, let’s call this set B[s]. The 
        respective weights of products in B[s] are W[(s + i * periodP) mod periodW]. Now consider 
        products in B[(s + periodP) mod periodW]. They all have the same price and the sequence of 
        weights is the same as for B[s] starting from the second element. Thus if we write down 
        the cycle of weights ( W[(s + i*periodP) mod period W], i = 0,1,2,...) then weights of 
        products in B[x] appear as a continuous subsequence in this cycle.
        - We want to find the minimum value in each of these subsequences. Moreover, the number 
        of elements in B[s] for different s may differ at most by 1. This is a well-known Sliding 
        Range Minimum Query problem that can be solved in linear time. If periodP is not prime we
        may need to consider several such cycles in order to cover all possible weights of products.
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

const int MAXN = 10000010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

ll n, P, W, A, B, C, D, occ[MAXN];
vi p, w, periodP, periodW;
int m, k, Min[MAXN], ma[MAXN];
pi used[MAXN];
vector<pi> minOfCycles;
vector<vector<int> > cycles, num1Cycles, num2Cycles;

void input() {
    cin >> n >> P >> W >> m >> k >> A >> B >> C >> D;
}

inline ll getNext(ll A, ll B, ll now, ll mod) {
    return (A * now + B) % mod + 1;
}

void init() {
    p.clear();
    w.clear();
    periodP.clear();
    periodW.clear();

    // process to get the non-periodic part and the periodic part of P and W
    // let the non-periodic parts are p and w
    // periodic parts ard periodP and periodW
    p.push_back(P);
    FOR(i,1,m) ma[i] = -1;
    deque<int> tmpP;
    ma[P] = 0;
    while (1) {
        int g = getNext(A, B, p.back(), m);
        if (ma[g] != -1) {
            int idx = ma[g];
            while (SZ(p) > idx) {
                tmpP.push_front(p.back());
                p.pop_back();
            }
            break;
        } else {
            ma[g] = SZ(p);
            p.push_back(g);
        }
    }

    w.push_back(W);
    FOR(i,1,k) ma[i] = -1;
    deque<int> tmpW;
    ma[W] = 0;
    while (1) {
        int g = getNext(C, D, w.back(), k);
        if (ma[g] != -1) {
            int idx = ma[g];
            while (SZ(w) > idx) {
                tmpW.push_front(w.back());
                w.pop_back();
            }
            break;
        } else {
            ma[g] = SZ(w);
            w.push_back(g);
        }
    }

    // need to proceed equal non-periodic parts for simplicity
    while (SZ(p) < SZ(w)) {
        p.push_back(tmpP.front());
        tmpP.push_back(tmpP.front());
        tmpP.pop_front();
    }
    while (SZ(w) < SZ(p)) {
        w.push_back(tmpW.front());
        tmpW.push_back(tmpW.front());
        tmpW.pop_front();
    }
    while (SZ(tmpP)) {
        periodP.push_back(tmpP.front());
        tmpP.pop_front();
    }
    while (SZ(tmpW)) {
        periodW.push_back(tmpW.front());
        tmpW.pop_front();
    }
}

void reverse() {
    // bargains and terrible deals are symmetrical
    FOR(i,0,SZ(p)-1) p[i] = m - p[i] + 1;
    FOR(i,0,SZ(periodP)-1) periodP[i] = m - periodP[i] + 1;
    FOR(i,0,SZ(w)-1) w[i] = k - w[i] + 1;
    FOR(i,0,SZ(periodW)-1) periodW[i] = k - periodW[i] + 1;
}

ll solve() {
    ll res = 0;

    FOR(i,1,m) {
        Min[i] = -1;
        occ[i] = 0;
    }

    // process the non-periodic part
    // remember that n can be lower than the part
    FOR(i,0,min(n-1, (ll) SZ(p)-1)) {
        if (Min[p[i]] == -1 || w[i] < Min[p[i]]) {
            Min[p[i]] = w[i];
            occ[p[i]] = 1;
        } else if (w[i] == Min[p[i]]) {
            occ[p[i]]++;
        }
    }

    if (n > SZ(p)) {
        n -= SZ(p);
        // s + i * periodP < N
        // i < (N - s) / periodP
        // i = 0, 1, ..., ceil((N - s) / periodP) - 1
        cycles.clear();
        num1Cycles.clear();
        num2Cycles.clear();
        minOfCycles.clear();
        // diff = the distance of the next element from the current one in periodW.
        int diff = SZ(periodP) - SZ(periodW);
        // used[i] = {cycle index, index in the cycle} of the ith element in periodW
        FOR(i,0,SZ(periodW)-1) {
            used[i] = {-1, -1};
        }
        // O(k)
        FOR(i,0,SZ(periodP)-1) {
            int j = i % SZ(periodW);
            if (used[j].FI == -1) {
                int x = j;
                vi q;
                while (1) {
                    // keep moving until we meet j again, it's a cycle.
                    used[x].SE = SZ(q);
                    used[x].FI = SZ(cycles);
                    q.push_back(periodW[x]);
                    x = (x + diff) % SZ(periodW);
                    if (x < 0) x += SZ(periodW);
                    if (x == j) break;
                }
                cycles.push_back(q);
            }
        }

        // Since the number of elements in B[s] for different s may differ at most by 1, we get those 2 values
        ll num1 = (n - 0) / SZ(periodP) - ((n - 0) % SZ(periodP) == 0) + 1;
        ll num2 = (n - (SZ(periodP)-1)) / SZ(periodP) - ((n - (SZ(periodP)-1)) % SZ(periodP) == 0) + 1;

        FOR(i,0,SZ(cycles)-1) {
            // first, get the minimum element of the cycle and its position in the cycle, put it into minOfCycles
            int g = cycles[i][0], pos = 0;
            FOR(j,1,SZ(cycles[i])-1) {
                if (cycles[i][j] < g) {
                    g = cycles[i][j];
                    pos = j;
                }
            }
            minOfCycles.push_back({g, pos});

            // num1Cycles stores the minimum elements of each sequence with length num1
            // the same implies to num2Cycles
            // only calculate if num1 < SZ(cycles[i]) as otherwise, just use the minOfCycles
            num1Cycles.push_back({});
            num2Cycles.push_back({});
            vi tmp;
            // add 2 cycles to calculate for simplicity
            FOR(j,0,SZ(cycles[i])-1) tmp.push_back(cycles[i][j]);
            FOR(j,0,SZ(cycles[i])-1) tmp.push_back(cycles[i][j]);

            // use sliding window technique to solve
            if (num1 < SZ(cycles[i])) {
                deque<pi> window;
                int len = num1;
                FOR(j,0,SZ(tmp)-1) {
                    while (!window.empty() && window.back().FI >= tmp[j]) window.pop_back();
                    window.push_back({tmp[j], j});
                    while (window.front().SE <= j - len) window.pop_front();
                    if (j + 1 >= len) {
                        num1Cycles[i].push_back(window.front().FI);
                        if (SZ(num1Cycles[i]) == SZ(cycles[i])) break;
                    }
                }
            }

            if (num2 < SZ(cycles[i])) {
                deque<pi> window;
                int len = num2;
                FOR(j,0,SZ(tmp)-1) {
                    while (!window.empty() && window.back().FI >= tmp[j]) window.pop_back();
                    window.push_back({tmp[j], j});
                    while (window.front().SE <= j - len) window.pop_front();
                    if (j + 1 >= len) {
                        num2Cycles[i].push_back(window.front().FI);
                        if (SZ(num2Cycles[i]) == SZ(cycles[i])) break;
                    }
                }
            }
        }
        
        FOR(s,0,SZ(periodP)-1) {
            if (s >= n) break;
            ll num = (n - s) / SZ(periodP) - ((n - s) % SZ(periodP) == 0) + 1;
            // 0 ... num-1
            int j = s % SZ(periodW);
            int cycleIdx = used[j].FI, idx = used[j].SE;
            if (num >= SZ(cycles[cycleIdx])) {
                // if num >= cycle length, there would be multiple occurences of the min element (from minOfCycles)
                pi x = minOfCycles[cycleIdx];
                ll minVal = x.FI;
                ll occurence = num / SZ(cycles[cycleIdx]);
                // remember to check the remaining part
                ll remain = num % SZ(cycles[cycleIdx]);
                while (x.SE < idx) x.SE += SZ(cycles[cycleIdx]);
                if (x.SE - idx + 1 <= remain) occurence++;

                if (Min[periodP[s]] == -1 || minVal < Min[periodP[s]]) {
                    Min[periodP[s]] = minVal;
                    occ[periodP[s]] = occurence;
                } else if (minVal == Min[periodP[s]]) {
                    occ[periodP[s]] += occurence;
                }
            } else if (num == num1) {
                // otherwise, there is only one occurence of minVal (as the elements in periodW are different)
                ll minVal = num1Cycles[cycleIdx][idx];

                if (Min[periodP[s]] == -1 || minVal < Min[periodP[s]]) {
                    Min[periodP[s]] = minVal;
                    occ[periodP[s]] = 1;
                } else if (minVal == Min[periodP[s]]) {
                    occ[periodP[s]] += 1;
                }
            } else {
                ll minVal = num2Cycles[cycleIdx][idx];

                if (Min[periodP[s]] == -1 || minVal < Min[periodP[s]]) {
                    Min[periodP[s]] = minVal;
                    occ[periodP[s]] = 1;
                } else if (minVal == Min[periodP[s]]) {
                    occ[periodP[s]] += 1;
                }
            }
        }
    }

    // finally, count the number of bargains (or terrible deals)
    int MinW = k+1;
    FOR(i,1,m) {
        if (Min[i] != -1) {
            if (Min[i] < MinW) {
                MinW = Min[i];
                res += occ[i];
            }
        }
    }

    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int te;
    cin >> te;
    FOR(o,1,te) {
        cout << "Case #" << o << ": ";
        input();
        init();
        // bargains
        ll res1 = solve();
        reverse();
        // terrible deals
        ll res2 = solve();
        cout << res2 << ' ' << res1 << "\n";
    }
    return 0;
}
