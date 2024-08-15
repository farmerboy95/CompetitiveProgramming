/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let's build a binary tree from the expression.
        - Then let dp[i][j] = {max, min} value of the subtree rooted at node i, with j operators
        (plus or minus) left to use.
        - If at the current node we use plus, then dp value at the current node is
            + Max = max left + max right
            + Min = min left + min right
        - If at the current node we use minus, then dp value at the current node is
            + Max = max left - min right
            + Min = min left - max right
        - At the end, we print out max of the root node.
        - Since min(P, M) <= 100, we can use it as the second dimension of the dp array, but
        the implementation is a bit tricky.
        - Complexity O(n * min(P, M)^2), n is the number of nodes in the tree, not the length of
        the string.
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

const int MAXN = 10010;
const int MAXM = 110;
const int MAXK = 16;
const int MAXQ = 200010;

struct Node {
    int idx, val, cnt;
    Node* left;
    Node* right;
};

string s;
int p, m, l[MAXN], r[MAXN], nodeCnt;
pi dp[MAXN][MAXM];

Node* buildTree(int lef, int rig) {
    // number
    if (lef == rig) {
        Node* cur = new Node();
        cur->idx = nodeCnt++;
        cur->cnt = 0;
        cur->val = s[lef] - '0';
        return cur;
    }

    // expression start with (
    if (s[lef] == '(') {
        if (s[rig] == ')' && r[lef] == rig) {
            return buildTree(lef+1, rig-1);
        }
        int k = r[lef];
        Node* cur = new Node();
        cur->idx = nodeCnt++;
        cur->val = -1;
        cur->cnt = 1;
        cur->left = buildTree(lef, k);
        cur->cnt += cur->left->cnt;
        cur->right = buildTree(k+2, rig);
        cur->cnt += cur->right->cnt;
        return cur;
    }

    // expression but start with number
    int k = lef;
    Node* cur = new Node();
    cur->idx = nodeCnt++;
    cur->val = -1;
    cur->cnt = 1;
    cur->left = buildTree(lef, k);
    cur->cnt += cur->left->cnt;
    cur->right = buildTree(k+2, rig);
    cur->cnt += cur->right->cnt;
    return cur;
}

void checkTree(Node *cur) {
    dbg(cur->idx, cur->cnt, cur->val);
    if (cur->left != NULL) {
        dbg("left", cur->idx, cur->left->idx);
        checkTree(cur->left);
    }
    if (cur->right != NULL) {
        dbg("right", cur->idx, cur->right->idx);
        checkTree(cur->right);
    }
}

void dfs(Node *cur, int P, int M, int x) {
    if (cur->val != -1) {
        dp[cur->idx][0] = {cur->val, cur->val};
        return;
    }

    if (x == 0) {
        if (dp[cur->idx][P].FI != -1) return;
    } else {
        if (dp[cur->idx][M].FI != -1) return;
    }

    pi res = {-INF, INF}; // max, min

    if (P) {
        int nextP = P-1;
        int nextM = M;
        if (x == 0) {
            FOR(i,0,min(nextP, cur->left->cnt)) {
                if (nextP-i > cur->right->cnt) continue;
                dfs(cur->left, i, cur->left->cnt - i, x);
                dfs(cur->right, nextP-i, cur->right->cnt - (nextP - i), x);
                ckmax(res.FI, dp[cur->left->idx][i].FI + dp[cur->right->idx][nextP-i].FI);
                ckmin(res.SE, dp[cur->left->idx][i].SE + dp[cur->right->idx][nextP-i].SE);
            }
        } else {
            FOR(i,0,min(nextM, cur->left->cnt)) {
                if (nextM-i > cur->right->cnt) continue;
                dfs(cur->left, cur->left->cnt - i, i, x);
                dfs(cur->right, cur->right->cnt - (nextM - i), nextM-i, x);
                ckmax(res.FI, dp[cur->left->idx][i].FI + dp[cur->right->idx][nextM-i].FI);
                ckmin(res.SE, dp[cur->left->idx][i].SE + dp[cur->right->idx][nextM-i].SE);
            }
        }
    }

    if (M) {
        int nextP = P;
        int nextM = M-1;
        if (x == 0) {
            FOR(i,0,min(nextP, cur->left->cnt)) {
                if (nextP-i > cur->right->cnt) continue;
                dfs(cur->left, i, cur->left->cnt - i, x);
                dfs(cur->right, nextP-i, cur->right->cnt - (nextP - i), x);
                ckmax(res.FI, dp[cur->left->idx][i].FI - dp[cur->right->idx][nextP-i].SE);
                ckmin(res.SE, dp[cur->left->idx][i].SE - dp[cur->right->idx][nextP-i].FI);
            }
        } else {
            FOR(i,0,min(nextM, cur->left->cnt)) {
                if (nextM-i > cur->right->cnt) continue;
                dfs(cur->left, cur->left->cnt - i, i, x);
                dfs(cur->right, cur->right->cnt - (nextM - i), nextM-i, x);
                ckmax(res.FI, dp[cur->left->idx][i].FI - dp[cur->right->idx][nextM-i].SE);
                ckmin(res.SE, dp[cur->left->idx][i].SE - dp[cur->right->idx][nextM-i].FI);
            }
        }
    }

    if (x == 0) {
        dp[cur->idx][P] = res;
    } else {
        dp[cur->idx][M] = res;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> s;
    cin >> p >> m;

    stack<int> st;
    FOR(i,0,SZ(s)-1) {
        if (s[i] == '(') {
            st.push(i);
        } else if (s[i] == ')') {
            int lef = st.top();
            st.pop();
            r[lef] = i;
            l[i] = lef;
        }
    }

    Node* root = buildTree(0, SZ(s)-1);
    int x = 0;
    if (p > m) x = 1;
    FOR(i,0,nodeCnt-1)
        FOR(j,0,min(p, m)) dp[i][j] = {-1, -1};
    dfs(root, p, m, x);

    cout << dp[root->idx][min(p, m)].FI;
    return 0;
}
