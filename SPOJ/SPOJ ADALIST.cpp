/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Use splay tree to solve
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

const int MAXN = 110;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

// Splay Tree Node
struct Node {
    // define parent node and its 2 children
    Node* parent, *children[2];
    // the size of the subtree with root as this node
    int size;
    // value of the node, Min of the subtree, and label of lazy addition
    ll val, Min, labelAdd;
    // label of lazy reversal
    int labelReverse;

    // constructor
    Node(int val) {
        parent = children[0] = children[1] = NULL;
        size = 1;
        this->val = val;
        Min = labelAdd = labelReverse = 0;
    }

    // add v to the subtree
    void add(ll v) {
        // add v to node's value, min and labelAdd
        val += v;
        Min += v;
        labelAdd += v;
    }

    // apply labels and push them down to children
    void pushDown() {
        if (labelReverse) {
            FOR(i,0,1) {
                if (children[i]) {
                    children[i]->reverse();
                }
            }
            labelReverse = 0;
        }

        if (labelAdd) {
            FOR(i,0,1) {
                if (children[i]) {
                    children[i]->add(labelAdd);
                }
            }
            labelAdd = 0;
        }
    }

    // update size of subtree and min of the subtree as well
    void update() {
        size = 1;
        Min = val;
        FOR(i,0,1) {
            if (children[i]) {
                size += children[i]->size;
                ckmin(Min, children[i]->Min);
            }
        }
    }

    // reverse the whole subtree, first thing is to swap 2 children
    void reverse() {
        swap(children[0], children[1]);
        labelReverse ^= 1;
    }
};

struct SplayTree {
    Node *root;

    // create splay tree with 2 dummy nodes (far-left and far-right)
    SplayTree() {
        root = new Node(-1);
        root->children[1] = new Node(-1);
        root->size = 2;
        root->children[1]->parent = root;
    }

    // since we have 2 dummy nodes, the size should be 2 less than the real size
    int size() { 
        return root->size - 2;
    }

    // Helper function to rotate node
    void rotate(Node *node) {
        int dirOfNode = (node->parent->children[1] == node);
        Node *parentNode = node->parent;

        Node *movingChildOfNode = node->children[dirOfNode ^ 1];

        if (parentNode->parent) {
            parentNode->parent->children[parentNode->parent->children[1] == parentNode] = node;
        }

        node->parent = parentNode->parent;
        node->children[dirOfNode ^ 1] = parentNode;

        parentNode->parent = node;
        parentNode->children[dirOfNode] = movingChildOfNode;

        if (movingChildOfNode) {
            movingChildOfNode->parent = parentNode;
        }

        parentNode->update();
        node->update();
    }

    // Splay node so that it is under desiredParent (or to root if desiredParent is null).
    void splay(Node *node, Node *desiredParent = NULL) {
        while (node->parent != desiredParent) {
            Node *parent = node->parent, *parentOfParent = parent->parent;
            if (parentOfParent == desiredParent) {
                rotate(node);
            } else if ((parentOfParent->children[0] == parent) == (parent->children[0] == node)) {
                rotate(parent);
                rotate(node);
            } else {
                rotate(node);
                rotate(node);
            }
        }
        if (!desiredParent) {
            root = node;
        }
    }

    // Helper function to walk down the tree.
    int walk(Node *node, int &dir, int &pos) {
        node->pushDown();
        int leftSize = node->children[0] ? node->children[0]->size : 0;
        dir = (leftSize < pos);
        if (dir) {
            pos -= leftSize + 1;
        }
        return leftSize;
    }

    // Insert node n to position pos
    void insert(Node *node, int pos) {
        Node *cur = root;
        int dir;
        // since we have the far-left dummy node and pos starts from 0, increase pos
        pos++;
        while (1) {
            walk(cur, dir, pos);
            if (!cur->children[dir]) {
                break;
            }
            cur = cur->children[dir];
        }

        cur->children[dir] = node;
        node->parent = cur;
        splay(node);
    }

    // Find the node at position pos. If sp is true, splay it.
    Node* find(int pos, int sp = true) {
        Node *cur = root;
        int dir;
        // since we have the far-left dummy node and pos starts from 0, increase pos
        pos++;
        while (pos < walk(cur, dir, pos) || dir) {
            cur = cur->children[dir];
        }
        if (sp) splay(cur);
        return cur;
    }

    // find range [posL, posR)
    // splay node posR to root, then splay posL-1 to below posR, then [posL, posR-1] will be right node of posL-1
    Node *findRange(int posL, int posR) {
        Node *r = find(posR), *l = find(posL - 1, false);
        splay(l, r);
        if (l->children[1]) l->children[1]->pushDown();
        return l->children[1];
    }

    // find range then disconnect it from the tree
    // remove from position [posL, posR)
    Node* eraseRange(int posL, int posR) {
        Node *range = findRange(posL, posR);
        range->parent->children[1] = NULL;
        range->parent->update();
        range->parent->parent->update();
        range->parent = NULL;
        return range;
    }

    // recursively print subtree with in-order traversal
    void print(Node *cur, string pref) {
        if (cur == NULL) return;
        print(cur->children[1], pref + "  ");
        cout << pref << cur->val << "\n";
        print(cur->children[0], pref + "  ");
    }

    // print the whole tree with in-order traversal
    // the tree shown in output will be the same as the real tree if you rotate it 90 degree clockwise
    void printTree() {
        print(root, "");
        cout << "\n";
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    SplayTree t;
    while (n--) {
        ll x;
        cin >> x;
        t.insert(new Node(x), t.size());
    }

    while (m--) {
        string s;
        int x, y, k;
        cin >> k;
        if (k == 1) {
            cin >> x >> y;
            t.insert(new Node(y), x-1);
        } else if (k == 2) {
            cin >> x;
            t.eraseRange(x-1, x);
        } else {
            cin >> x;
            Node *cur = t.find(x-1);
            cout << cur->val << "\n";
        }
    }
    return 0;
}
