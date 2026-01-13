/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let's consider each of the letters, let's say "a", you will see this format
            + ------aaaaaa-----aaa----aaaa---aa-a-----
        - We have a number of groups here, we can store them as a pair of number of
        consecutive letters "a" and something else. What is this something else? It's
        something we can use to know if all the letters between 2 separate groups of "a"
        disappear. It's the bitmask of those letters. We store bitmask of non-a letters
        to the right of the current group along with the count. The last group does not
        have any bitmask to the right of it. This part will take O(nk). Now our groups 
        will be [{6, M1}, {3, M2}, {4, M3}, {2, M4}, {1, 0}].
        - Now what? Let's say we can merge the first 3 groups, so we can add 
        6*6 + 6*3 + 6*4 + 3*6 + 3*3 + 3*4 + 4*6 + 4*3 + 4*4 to the result (trust me, 
        just need to expand (a+b+c)^2 to have it, and it applies to (a+b+..+z)^2 as well).
        So looks like, if the query can cover the first and second in-between bitmasks,
        we can add that to the result.
        - Let's fix some first group and expand the right border, we notice that there
        are only O(k) different bitmasks to cover from first group to the right. So we
        can do binary search to find out those different bitmasks with the help of some
        OR-sum RMQ-based array. We call dp[mask] storing the additional sum corresponding
        to the new different bitmask. At each step, we add product of twice of the count
        sum from old to new bitmask and the current count of our left border. Why twice?
        It's because when merged, we need twice of the product of count of 2 different groups.
        Only the product of count of one group with itself is not doubled.
        - Finally, do SOS DP on dp array, we will have the result for a letter when a
        bitmask is removed from the original string.
        - When querying, create a mask representing the query, then add to the result
        when i-th bit is not set in the mask.
        - Complexity O(k^2 * 2^k + k^2 * n)
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
string ts(bool b) { return (b ? "true" : "false"); }

template<class T> using V = vector<T>;
template<class T> string ts(complex<T> c);
string ts(V<bool> v);
template<size_t sz> string ts(bitset<sz> b);
template<class T> string ts(T v);
template<class T, class U> string ts(pair<T,U> p);
template<class ...U> string ts(tuple<U...> u);

template<class T> string ts(complex<T> c) { stringstream ss; ss << c; return ss.str(); }
string ts(V<bool> v) {string res = "{"; FOR(i,0,SZ(v)-1) res += char('0'+v[i]); res += "}"; return res; }
template<size_t sz> string ts(bitset<sz> b) { string res = ""; FOR(i,0,SZ(b)-1) res += char('0'+b[i]); return res; }
template<class T> string ts(T v) { // containers with begin(), end()
    bool fst = 1; string res = "";
    for (const auto& x: v) { if (!fst) res += " "; fst = 0; res += ts(x); }
    return res;
}
template<class T, class U> string ts(pair<T,U> p) { return "(" + ts(p.FI) + ", " + ts(p.SE) + ")"; }
template<size_t i, class T> string print_tuple_utils(const T& tup) { if constexpr(i == tuple_size<T>::value) return ")"; else return (i ? ", " : "(") + ts(get<i>(tup)) + print_tuple_utils<i + 1, T>(tup); }
template<class ...U> string ts(tuple<U...> u) { return print_tuple_utils<0, tuple<U...>>(u); }

// OUTPUT
template<class T> void pr(T x) { cout << ts(x); }
template<class T, class ...U> void pr(const T& t, const U&... u) { pr(t); pr(u...); }
void ps() { pr("\n"); } // print w/ spaces
template<class T, class ...U> void ps(const T& t, const U&... u) { pr(t); if (sizeof...(u)) pr(" "); ps(u...); }

// DEBUG
void DBG() { cerr << "]" << endl; }
template<class T, class ...U> void DBG(const T& t, const U&... u) { cerr << ts(t); if (sizeof...(u)) cerr << ", "; DBG(u...); }

#ifdef LOCAL_DEBUG
#define CONCAT(x, y) x##y
#define with_level setw(__db_level * 2) << setfill(' ') << "" << setw(0)
#define dbg(...) cerr << with_level << "Line(" << __LINE__ << ") -> [" << #__VA_ARGS__ << "]: [", DBG(__VA_ARGS__)
#define chk(...) if (!(__VA_ARGS__)) cerr << setw(__db_level * 2) << setfill(' ') << "" << setw(0) << "Line(" << __LINE__ << ") -> function(" << __FUNCTION__  << ") -> CHK FAILED: (" << #__VA_ARGS__ << ")" << "\n", exit(0);
#define db_block() debug_block CONCAT(dbbl, __LINE__)
int __db_level = 0;
struct debug_block {
    debug_block() { cerr << with_level << "{" << endl; ++__db_level; }
    ~debug_block() { --__db_level; cerr << with_level << "}" << endl; }
};
#else
#define dbg(...) 0
#define chk(...) 0
#define db_block() 0
#endif

const ld PI = acos(-1.0);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
const ld EPS = 1e-9;
const ll MODBASE = 1000000007LL;
const int INF = 0x3f3f3f3f;

const int MAXN = 200000;
const int MAXM = 1000;
const int MAXK = 18;
const int MAXQ = 200010;

int n, k, orSum[MAXN][MAXK], pref[MAXN];
ll dp[MAXK][1<<MAXK];
string s;
vi pos[MAXK];
vpi group[MAXK];

int getMask(int l, int r) {
    int res = 0;
    FOR(i,l,r) {
        int x = s[i] - 'a';
        res |= (1<<x);
    }
    return res;
}

int getSum(int l, int r) {
    if (l == 0) return pref[r];
    return pref[r] - pref[l-1];
}

int getOrSum(int l, int r) {
    int p = log2(r - l + 1);
    return orSum[l][p] | orSum[r-(1<<p)+1][p];
}

void preprocess() {
    FOR(i,0,n-1) {
        int x = s[i] - 'a';
        pos[x].push_back(i);
    }

    // Create the groups
    FOR(i,0,k-1) {
        if (SZ(pos[i]) == 0) {
            continue;
        }
        int cnt = 1;
        FOR(j,1,SZ(pos[i])-1) {
            if (pos[i][j-1] + 1 == pos[i][j]) {
                cnt++;
            } else {
                int l = pos[i][j-1] + 1, r = pos[i][j] - 1;
                group[i].push_back({cnt, getMask(l, r)});
                cnt = 1;
            }
        }
        group[i].push_back({cnt, 0});
    }
    
    // For each of the letter kinds
    FOR(i,0,k-1) {
        int N = SZ(group[i]);
        if (N == 0) {
            continue;
        }
        
        // build to get range OR sum
        FOR(j,0,N-1) {
            orSum[j][0] = 0;
        }
        FOR(p,1,MAXK-1) {
            FOR(j,0,N-1) {
                if (j + (1<<(p-1)) >= N) {
                    orSum[j][p] = orSum[j][p-1];
                    continue;
                }
                orSum[j][p] = orSum[j][p-1] | orSum[j + (1<<(p-1))][p-1] | group[i][j + (1<<(p-1)) - 1].SE;
            }
        }
        // build to get range sum of count
        FOR(j,0,N-1) {
            if (j == 0) pref[j] = group[i][j].FI;
            else pref[j] = pref[j-1] + group[i][j].FI;
        }

        FOR(j,0,N-1) {
            dp[i][0] += (ll) group[i][j].FI * group[i][j].FI;
            if (j + 1 >= N) continue;
            
            int l = j, r = j + 1;
            int mask = getOrSum(l, r);
            while (r < N) {
                int L = r, R = N - 1;
                while (L <= R) {
                    int mid = (L + R) >> 1;
                    if (getOrSum(l, mid) != mask) R = mid - 1;
                    else L = mid + 1;
                }
                dp[i][mask] += getSum(r, R) * 2LL * group[i][j].FI;
                r = L;
                mask = getOrSum(l, r);
            }
        }
    }

    // SOS DP for each of the letter kinds
    FOR(x,0,k-1) {
        FOR(i,0,k-1) {
            FOR(mask,0,(1<<k)-1) {
                if (mask & (1<<i)) {
                    dp[x][mask] += dp[x][mask ^ (1<<i)];
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> k;
    cin >> s;

    preprocess();

    int q;
    cin >> q;
    while (q--) {
        string allergy;
        cin >> allergy;
        int aMask = 0;
        FOR(i,0,SZ(allergy)-1) {
            aMask |= (1<<(allergy[i] - 'a'));
        }

        ll res = 0;
        FOR(i,0,k-1) {
            if (aMask & (1<<i)) continue;
            res += dp[i][aMask];
        }
        cout << res << "\n";
    }
    return 0;
}
