/*
    Author: Nguyen Tan Bao

    Idea: 
        - Initial slime should be the largest one in the input multiset
        - Using greedy approach, for each slime, we can only produce a smaller slime, so that
        we make it produce the largest possible slime we need to build. If at any step we cannot
        produce, the answer is No, otherwise, the answer is Yes
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

int n, a[MAXN];
multiset<int> s;
vector<int> slimes, newSlimes;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,(1<<n)) cin >> a[i];

    // use negative set to make use of upper_bound
    FOR(i,1,(1<<n)) s.insert(-a[i]);
    slimes.emplace_back(*s.begin());
    s.erase(s.begin());
    
    // each second, we produce new array of slimes based on the available ones
    FOR(i,1,n) {
        newSlimes.clear();
        FOR(j,0,SZ(slimes)-1) {
            multiset<int>::iterator it = s.upper_bound(slimes[j]);
            if (it == s.end()) {
                cout << "No";
                return 0;
            }
            newSlimes.emplace_back(*it);
            s.erase(it);
        }
        FOR(j,0,SZ(newSlimes)-1) slimes.emplace_back(newSlimes[j]);
        sort(ALL(slimes));
    }
    cout << "Yes";
    return 0;
}
