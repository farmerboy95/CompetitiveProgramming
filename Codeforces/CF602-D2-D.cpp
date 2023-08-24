/*
	Template Version: 1.0.0 - 20220620
	Author: Nguyen Tan Bao
	Status: AC
	Idea:
        - Mainly from https://codeforces.com/blog/entry/21755
        - The key observation is that it's sufficient to consider j = i+1 when calculating the
        Lipschitz, the proof is in the link above
        - After the calculation, we can create a new array with elements as |a[i+1] - a[i]|.
        - When finding the Lipschitz constant of a subarray, we just get max in the range
        of the new array.
        - But when getting sum of all subarrays in the range, we need to get how many times
        an element is contributed to the final sum, we can find the nearest left element and
        nearest right element that is larger or equal and larger than the current element,
        respectively. Then the number of times that element is contributed to the final sum
        is the product of the left and right ranges of the element.
        - Finding nearest element is done by stack.
        - Complexity O(N * Q)
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

const int MAXN = 100010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, a[MAXN], d[MAXN], N, q, l[MAXN], r[MAXN];
stack<pi> s;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	cin >> n >> q;
	FOR(i,1,n) cin >> a[i];
	FOR(i,1,n-1) d[i] = abs(a[i+1] - a[i]);
	N = n-1;

	FOR(i,1,N) {
		l[i] = 0;
		while (SZ(s)) {
			pi g = s.top();
			if (g.first < d[i]) s.pop();
			else {
				l[i] = g.second;
				break;
			}
		}
		s.push({d[i], i});
	}

	while (SZ(s)) s.pop();
	FORE(i,N,1) {
		r[i] = N+1;
		while (SZ(s)) {
			pi g = s.top();
			if (g.first <= d[i]) s.pop();
			else {
				r[i] = g.second;
				break;
			}
		}
		s.push({d[i], i});
	}

	while (q--) {
		int u, v;
		cin >> u >> v;
		v--;
		ll res = 0;
		FOR(i,u,v) {
            // finding the nearest left element that is larger or equal to the current element
            // it can be out of the range because we won't count it anyways
			int L = max(l[i], u-1);
            // finding the nearest right element that is larger than the current element
            // why are these 2 not the same, you can draw a range with a number of same elemnents to see
			int R = min(r[i], v+1);
			res += 1LL * d[i] * (i - L) * (R - i);
		}
		cout << res << "\n";
	}
	return 0;
}
