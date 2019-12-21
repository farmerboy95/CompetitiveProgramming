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

string s, t;
int b[1000010];

void kmpPreprocess() {
    b[0] = 0;
    FOR(i,1,sz(t)-1) {
        int k = b[i-1];
        while (k > 0 && t[k] != t[i]) k = b[k-1];
        if (t[k] == t[i]) b[i] = k+1;
        else k = 0;
    }
}

void kmpSearch() {
    int j = 0;
    FOR(i,0,sz(s)-1) {
        while (j > 0 && s[i] != t[j]) j = b[j-1];
        if (s[i] == t[j]) j++;
        else j = 0;
        if (j == sz(t)) {
            cout << i-sz(t)+2 << ' ';
            j = b[j-1];
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    cin >> s >> t;
    kmpPreprocess();
    kmpSearch();
    return 0; 
}
