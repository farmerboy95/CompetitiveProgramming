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
typedef pair<ll, II> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;

void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
    cout << *it << " = " << a << endl;
    err(++it, args...);
}

int n, m, valid[300010], group, num;
string s;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    cin >> n >> m;
    cin >> s;
    s = " " + s;
    FOR(i,1,n) 
        if (s[i] == '.') {
            num++;
            if (s[i-1] != '.') group++;
            valid[i] = 1;
        }
    while (m--) {
        int u; char ch;
        cin >> u >> ch;
        bool a = valid[u], b = (ch == '.');
        if (a != b) {
            if (a) num--;
            else num++;
            if (valid[u-1] && valid[u+1] && !b) group++;
            if (valid[u-1] && valid[u+1] && b) group--;
            if (!valid[u-1] && !valid[u+1] && !b) group--;
            if (!valid[u-1] && !valid[u+1] && b) group++;
        }
        valid[u] = b;
        cout << num-group << "\n";
    }
    return 0; 
}
