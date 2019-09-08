/*
    Author: Nguyen Tan Bao

    Idea: 
        - The number of happy people can increase at most 2. So that we use greedy approach. We choose to flip consecutive Rs or Ls.
        - For example, LLRRRLLRRL and k = 2, we choose to flip 2 inner groups of Rs.
        - Firstly, compress number of consecutive Rs and Ls and put them in array a.
        - Let K = k + k + 1 (k + 1 groups of L in example), we can get number of happy people in K consecutive groups is numOfPeopleInGroups - 1
        - Add results some other separate groups L and R.
        - Move K groups forward and get results.
        - Print out maximum of results.
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
#define WHATIS(x) cout << #x << " is " << x << endl;
#define ERROR(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
//__builtin_ffs(x) return 1 + index of least significant 1-bit of x
//__builtin_clz(x) return number of leading zeros of x
//__builtin_ctz(x) return number of trailing zeros of x

using namespace std;
using ll = long long;
using ld = double;
typedef pair<int, int> II;
typedef pair<II, int> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;

void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
    cout << *it << " = " << a << endl;
    err(++it, args...);
}

const ll MODBASE = 1000000007LL;
const int MAXN = 300000;
const int MAXM = 200010;
const int MAXK = 110;
const int MAXQ = 200010;

int n, k;
string s;
vector<int> a, l, r;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> k;
    cin >> s;
    // compress consecutive same elements and put them in array a
    int cnt = 1;
    FOR(i,1,SZ(s)) {
        if (i == SZ(s)) {
            a.emplace_back(cnt);
            break;
        }
        if (s[i] == s[i-1]) cnt++;
        else {
            a.emplace_back(cnt);
            cnt = 1;
        }
    }
    int K = k + k + 1;
    // if K > number of groups, we can simply return n - 1, as we can flip "R" groups or "L" groups
    if (K >= SZ(a)) cout << n-1;
    else {
        int res = 0;
        int cnt = 0;
        FOR(i,0,K-1) cnt += a[i];
        FOR(i,0,SZ(a)-1) {
            l.emplace_back(0);
            r.emplace_back(0);
        }
        // get results of separate groups
        FOR(i,0,SZ(a)-1) {
            if (i < 1) l[i] = a[i]-1;
            else l[i] = l[i-1] + a[i]-1;
        }
        FORE(i,SZ(a)-1,0) {
            if (i >= SZ(a)-1) r[i] = a[i]-1;
            else r[i] = r[i+1] + a[i]-1;
        }
        // init result of first K consecutive groups
        if (K < SZ(a)) res = max(res, cnt - 1 + r[K]);
        else res = max(res, cnt - 1);
        
        FOR(i,K,SZ(a)-1) {
            // move K groups forward and get result
            cnt += a[i];
            cnt -= a[i-K];
            int kq = cnt - 1;
            int lef = i-K+1, rig = i;
            if (rig + 1 < SZ(a)) kq += r[rig+1];
            if (lef - 1 >= 0) kq += l[lef-1];
            res = max(res, kq);
        }
        cout << res;
    }
    return 0;
}
