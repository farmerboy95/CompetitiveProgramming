#include <bits/stdc++.h>
#define base 1000000007LL
#define ll long long
#define X first
#define Y second
#define ld double
#define pb push_back
#define EPS 1e-9
#define all(a) a.begin(),a.end()
#define sz(a) int((a).size())
#define ms(s, n) memset(s, n, sizeof(s))
#define FOR(i,a,b) for (int i = (a); i <= (b); i++)
#define FORE(i,a,b) for (int i = (a); i >= (b); i--)
#define FORALL(it, a) for (__typeof((a).begin()) it = (a).begin(); it != (a).end(); it++)
#define what_is(x) cout << #x << " is " << x << endl;
#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
//__builtin_ffs(x) return 1 + index of least significant 1-bit of x
//__builtin_clz(x) return number of leading zeros of x
//__builtin_ctz(x) return number of trailing zeros of x

using namespace std;
typedef pair<int, int> II;
typedef pair<ll, II> III;

void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
	cout << *it << " = " << a << endl;
	err(++it, args...);
}

// heap min
struct Node {
    int vt, gold;
    Node(int vt = 0, int gold = 0) : vt(vt), gold(gold) {}
    bool friend operator< (Node a, Node b)
	{
		return a.gold > b.gold;
	}
};

int n;
priority_queue<Node> h;
vector<int> res;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    cin >> n;
    char ch;
    int x;
    FOR(i,2,n) {    
        cin >> ch >> x;
        if (ch == 'd') {
            h.push(Node(i, x));
        }
        else if (n != i) {
            while (sz(h) >= x) h.pop();
        }
    }
    if (sz(h) < x) {
        cout << -1;
        return 0;
    }
    int sum = 0;
    while (!h.empty()) {
        Node w = h.top();
        res.pb(w.vt);
        sum += w.gold;
        h.pop();
    }
    cout << sum << endl;
    cout << sz(res) << endl;
    sort(all(res));
    FOR(i,0,sz(res)-1) cout << res[i] << " ";
    
    return 0;
}
