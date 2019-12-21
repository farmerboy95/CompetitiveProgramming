// Problem Link: https://codeforces.com/contest/1080/problem/F
// Algorithm Link: https://www.akalin.com/longest-palindrome-linear-time
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

int n, m, a[255][26];
char ch[255][255];
ll res;

bool isEqual(int u, int v) {
    FOR(i,0,25)
        if (a[u][i] != a[v][i]) return false;
    return true;
}

ll manacher(int u, int v)
{
    int seqLen = v-u+1;
    vector<int> l;
    int i = 0;
    int palLen = 0;
    while (i < seqLen) {
        if (i > palLen && isEqual(u + i - palLen - 1, u + i)) {
            palLen += 2;
            i += 1;
            continue;
        }
        l.pb(palLen);
        int s = sz(l) - 2;
        int e = s - palLen;
        bool co = false;
        FORE(j,s,e+1) {
            int d = j - e - 1;
            if (l[j] == d) {
                palLen = d;
                co = true;
                break;
            }
            l.pb(min(d, l[j]));
        }
        if (!co) {
            palLen = 1;
            i += 1;
        }
    }
    l.pb(palLen);
    int lLen = sz(l);
    int s = lLen - 2;
    int e = s - (2 * seqLen + 1 - lLen);
    FORE(i,s,e+1) {
        int d = i - e - 1;
        l.pb(min(d, l[i]));
    }
    FOR(i,0,sz(l)-1) res += l[i] / 2 + (l[i] % 2);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    cin >> n >> m;
    FOR(i,1,n)
        FOR(j,1,m) cin >> ch[i][j];
    FOR(j,1,m) {
        FOR(i,1,n) 
            FOR(alp,0,25) a[i][alp] = 0;
        FOR(k,j,m) {
            FOR(i,1,n) a[i][ch[i][k]-'a']++;

            vector<int> s;
            s.pb(0);

            FOR(i,1,n) {
                int le = (k-j+1) % 2;
                FOR(alp,0,25) le -= a[i][alp] % 2;
                if (le != 0) s.pb(i);
            }

            s.pb(n+1);

            FOR(i,0,sz(s)-2) res += manacher(s[i]+1, s[i+1]-1);
        }
        //cout << res << endl;
    }
    cout << res;
    return 0;
}
