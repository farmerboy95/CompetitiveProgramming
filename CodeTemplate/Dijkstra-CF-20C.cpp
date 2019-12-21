#include <bits/stdc++.h>
#define base 1000000007LL
#define ll long long
#define X first
#define Y second
#define ld double
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
typedef pair<ll, int> IIh;
typedef pair<ll, II> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;

void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
    cout << *it << " = " << a << endl;
    err(++it, args...);
}

int n, m, trace[100010];
bool lck[100010];
ll d[100010];
priority_queue<IIh, vector<IIh>, greater<IIh> > h;
vector<II> A[100010];

ll ijk(int s, int t) {
    FOR(i,1,n) lck[i] = false;
    FOR(i,1,n) d[i] = 1e18;
    d[s] = 0;
    h.push(IIh(0, s));
    while (1) {
        while (!h.empty() && h.top().X != d[h.top().Y]) h.pop(); 
        if (h.empty()) break;
        int u = h.top().Y;
        h.pop();
        lck[u] = true;
        FOR(i,0,sz(A[u])-1) {
            int v = A[u][i].X;
            int c = A[u][i].Y;
            if (lck[v] == false && d[v] > d[u] + c) {
                d[v] = d[u] + c;
                h.push(IIh(d[v], v));
                trace[v] = u;
            }
        } 
    }
    return d[t];
}
 

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    cin >> n >> m;
    FOR(i,1,m) {
        int u, v, c;
        cin >> u >> v >> c;
        A[u].emplace_back(II(v, c));
        A[v].emplace_back(II(u, c));
    }
    ll res = ijk(1, n);
    if (res < 1e18) {
        vector<int> kq;
        int g = n;
        kq.emplace_back(g);
        while (g != 1) {
            g = trace[g];
            kq.emplace_back(g);
        }
        FORE(i,sz(kq)-1,0) cout << kq[i] << ' ';
    }
    else cout << -1;
    return 0; 
}
