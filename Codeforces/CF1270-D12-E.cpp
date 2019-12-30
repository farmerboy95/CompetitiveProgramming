/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: https://codeforces.com/blog/entry/72611
*/
 
#include <bits/stdc++.h>
#define FI first
#define SE second
#define EPS 1e-9
#define ALL(a) a.begin(),a.end()
#define SZ(a) int((a).size())
#define MS(s, n) memset(s, n, sizeof(s))
#define FOR(i,a,b) for (int i = (a); i <= (b); i++)
#define FORE(i,a,b) for (int i = (a); i >= (b); i--)
#define FORALL(it, a) for (__typeof((a).begin()) it = (a).begin(); it != (a).end(); it++)
//__builtin_ffs(x) return 1 + index of least significant 1-bit of x
//__builtin_clz(x) return number of leading zeros of x
//__builtin_ctz(x) return number of trailing zeros of x
 
using namespace std;
using ll = long long;
using ld = double;
typedef pair<int, int> II;
typedef pair<II, ll> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;
 
const ll MODBASE = 1000000007LL;
const int MAXN = 510;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

struct Point {
    int x, y, pos;
    Point(int x = 0, int y = 0, int pos = 0) : x(x), y(y), pos(pos) {}
};

vector<Point> a;
vector<int> b, res;
int n;
set<int> s;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n) {
        int u, v;
        cin >> u >> v;
        a.emplace_back(Point(u + 1000000, v + 1000000, i));
    }
    while (1) {
        b.clear();
        FOR(i,0,SZ(a)-1) {
            int u = a[i].x % 2, v = a[i].y % 2;
            if (u == v) b.emplace_back(u);
            else b.emplace_back(u+2);
        }
        s.clear();
        FOR(i,0,SZ(a)-1) s.insert(b[i]);
        int g = s.count(2) + s.count(3);
        int h = s.count(0) + s.count(1);
        if (g && h) {
            FOR(i,0,SZ(a)-1)
                if (b[i] == 0 || b[i] == 1) res.emplace_back(i+1);
            cout << SZ(res) << "\n";
            FOR(i,0,SZ(res)-1) cout << res[i] << " ";
            break;
        }
        else if (SZ(s) > 1) {
            int p = b[0];
            FOR(i,0,SZ(a)-1)
                if (b[i] == p) res.emplace_back(i+1);
            cout << SZ(res) << "\n";
            FOR(i,0,SZ(res)-1) cout << res[i] << " ";
            break;
        }
        
        FOR(i,0,SZ(a)-1) {
            a[i].x /= 2;
            a[i].y /= 2;
        }
    }
    return 0;
}
