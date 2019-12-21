#include <bits/stdc++.h>
#define base 1000000007LL
#define ll long long
#define X first
#define Y second
#define ld double
#define eb emplace_back
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

const int MAXN = 400010;

int t, SA[MAXN], RA[MAXN], c[MAXN], tempRA[MAXN], tempSA[MAXN], n, behind[MAXN], LCP[MAXN], PLCP[MAXN], q, Min[MAXN][20];
string s;

void countingSort(int k)
{
    int sum = 0, maxi = max(300, n);
    memset(c, 0, sizeof(c));
    FOR(i,0,n-1)
        if (i+k < n) c[RA[i+k]]++;
        else c[0]++;
    FOR(i,0,maxi-1) {
        int t = c[i];
        c[i] = sum;
        sum += t; 
    }
    FOR(i,0,n-1) {
        int a = 0;
        if (SA[i]+k < n) a = RA[SA[i]+k];
        tempSA[c[a]++] = SA[i];
    }
    FOR(i,0,n-1) SA[i] = tempSA[i];
}

void suffixArray()
{
    int r;
    FOR(i,0,n-1) SA[i] = i; FOR(i,0,n-1) RA[i] = s[i];
    for (int k = 1; k < n; k <<= 1) {
        countingSort(k);
        countingSort(0);
        tempRA[SA[0]] = r = 0;
        FOR(i,1,n-1) {
            if (RA[SA[i]] != RA[SA[i-1]]) {
                tempRA[SA[i]] = ++r;
                continue;
            }
            int a, b;
            if (SA[i]+k >= n) a = 0;
            else a = RA[SA[i]+k];
            if (SA[i-1]+k >= n) b = 0;
            else b = RA[SA[i-1]+k];
            if (a == b) tempRA[SA[i]] = r;
            else tempRA[SA[i]] = ++r;
        }
        FOR(i,0,n-1) RA[i] = tempRA[i];
        if (r == n-1) break;
    }
}

void buildLCP() 
{
    behind[SA[0]] = -1;
    FOR(i,1,n-1) behind[SA[i]] = SA[i-1]; int L = 0;
    FOR(i,0,n-1) {
        if (behind[i] == -1) {
            PLCP[i] = 0;
            continue; 
        }
        while (s[i+L] == s[behind[i]+L]) L++; PLCP[i] = L;
        L = max(L-1,0);
    }
    FOR(i,0,n-1) LCP[i] = PLCP[SA[i]]; 
}

struct Point {
    int vt, team;
    Point(int vt = 0, int team = 0) : vt(vt), team(team) {}
};

bool operator< (Point a, Point b) {
    return a.vt < b.vt;
}

vector<Point> p;
map<int, int> ma;

int getMin(int i, int j) {
    int v = log2(j-i);
    return min(Min[i+1][v], Min[j-(1<<v)+1][v]);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    cin >> n >> q;
    int N = n;
    cin >> s;
    s = s + "$" + s + "#";
    n = sz(s);
    suffixArray();
    buildLCP();
    FOR(i,0,sz(s)-1) Min[i][0] = LCP[i];
    for (int j = 1; (1<<j) < sz(s); j++)
        for (int i = 0; i+(1<<j)-1 < sz(s); i++) Min[i][j] = min(Min[i][j-1], Min[i+(1<<(j-1))][j-1]);
    //FOR(i,0,sz(s)-1) cout << ((SA[i] > N) ? "1 " : "0 ") << SA[i] << ' ' << LCP[i] << ' ' << s.substr(SA[i], sz(s)-SA[i]) << endl;
    while (q--) {
        int x, y;
        cin >> x >> y;
        ll res = 0;
        p.clear();
        FOR(i,1,x) {
            int k;
            cin >> k;
            p.eb(Point(RA[k-1], 0));
        }
        FOR(i,1,y) {
            int k;
            cin >> k;
            p.eb(Point(RA[k+N], 1));
        }
        sort(all(p));
        FOR(w,0,1) {
            int teamFirst = -1;
            ma.clear();
            ll sum = 0;
            FOR(i,0,sz(p)-1) {
                //cout << p[i].vt << endl;
                if (p[i].team == w) {
                    if (teamFirst == -1) continue;
                }
                else {
                    if (teamFirst == -1) {
                        teamFirst = p[i].vt;
                        continue;
                    }
                }
                int lcp = getMin(teamFirst, p[i].vt);
                ma[lcp]++;
                sum += lcp;
                while (!ma.empty()) {
                    map<int, int>::iterator it = --ma.end();
                    if (it->X <= lcp) break;
                    sum -= 1LL * it->X * it->Y;
                    ma[lcp] += it->Y;
                    sum += 1LL * it->Y * lcp;
                    ma.erase(it);
                }
                if (p[i].team == w) {
                    res += sum;
                    ma[lcp]--;
                    sum -= lcp;
                }
                else teamFirst = p[i].vt;
                //cout << i << " " << res << endl;
            }
        }
        cout << res << endl;
    }
    return 0; 
}
