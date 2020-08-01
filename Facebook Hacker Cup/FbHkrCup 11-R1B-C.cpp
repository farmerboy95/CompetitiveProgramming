/*
    Author: Nguyen Tan Bao
    Statement: https://www.facebook.com/codingcompetitions/hacker-cup/2011/round-1b/problems/C
    Status: AC
    Idea:
        - Note that secret <= 10^7 as in the function, we modulo 10^7+1
        - So we iterate all secret and store all secret that produce the same x at cnt[x], there would
        surprisingly be 10^4 elements for each cnt[x].
        - Then we iterate through cnt[a[1]] and try to reproduce the initial array with each initial secret,
        and just do as the statement tells us to do.
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
typedef pair<II, int> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;

const ll MODBASE = 1000000007LL;
const int MAXN = 110;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

vector<int> cnt[1010];
int a[110];

int getRandomNumber(int &secret) {
    // note that the secret changes, the returning value is not the new secret
    secret = ((ll) secret * 5402147 + 54321) % 10000001;
    return int(secret % 1000);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    FOR(i,0,10000000) {
        int x = i;
        int g = getRandomNumber(x);
        cnt[g].push_back(i);
    }
    int t;
    cin >> t;
    FOR(o,1,t) {
        cout << "Case #" << o << ": ";
        int n;
        cin >> n;
        FOR(i,1,n) cin >> a[i];
        int res = -1, dem = 0;
        FOR(i,0,SZ(cnt[a[1]])-1) {
            int secret = cnt[a[1]][i];
            bool co = true;
            FOR(j,1,n) {
                int k = getRandomNumber(secret);
                if (k != a[j]) co = false;
            }
            if (co) {
                res = cnt[a[1]][i];
                dem++;
            }
        }
        if (res == -1) cout << "Wrong machine\n";
        else if (dem > 1) cout << "Not enough observations\n";
        else {
            int secret = res;
            FOR(i,1,n) getRandomNumber(secret);
            FOR(i,1,10) cout << getRandomNumber(secret) << " ";
            cout << "\n";
        }
    }
    return 0;
}
