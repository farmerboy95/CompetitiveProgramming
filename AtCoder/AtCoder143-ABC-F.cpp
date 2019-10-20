/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let f[i] is the number of time i appear in initial array a
        - Put all f[i] in array b, sort descending
        - For each k:
            + If k > size(b), simply print 0
            + Let numOfGroup = k, numInEach = n / k, N = n
            + The result for k cannot be larger than numInEach, so we binary search the number of b[i] >= numInEach
            then deduct sum(those b[i]) from N and deduct number of b[i] from numOfGroup
            + Iterate through the remaining b[i], if b[i] > N / numOfGroup then b[i] is in its own group and deduct from N and numOfGroup
            this costs O(sqrt(n))
            + Then simply get numInEach = N / numOfGroup if numOfGroup > 0 and print result
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
const int MAXN = 300010;
const int MAXM = 1010;
const int MAXK = 110;
const int MAXQ = 200010;

int n, a[MAXN], f[MAXN];
vector<int> b, s;

int getNumberOfLarger(int u) {
    if (b[0] < u) return 0;

    int dau = 0, cuoi = SZ(b)-1;
    while (dau <= cuoi) {
        int mid = (dau + cuoi) >> 1;
        if (b[mid] >= u) dau = mid+1;
        else cuoi = mid-1;
    }
    return cuoi+1;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n) cin >> a[i];
    FOR(i,1,n) f[a[i]]++;
    FOR(i,1,n)
        if (f[i]) b.emplace_back(f[i]);
    sort(ALL(b));
    reverse(ALL(b));

    FOR(i,0,SZ(b)-1) 
        if (i == 0) s.emplace_back(b[i]);
        else s.emplace_back(s[SZ(s)-1] + b[i]);

    FOR(k,1,n) {
        // simply print 0 if k is larger than number of group
        if (k > SZ(b)) {
            cout << 0 << "\n";
            continue;
        }
        int numOfGroup = k;
        int numInEach = n / k;

        int cnt = getNumberOfLarger(numInEach);

        numOfGroup -= cnt;

        if (numOfGroup <= 0) {
            cout << numInEach << "\n";
            continue;
        }
        int N = n;
        int Min = 1000000000;
        if (cnt) {
            N = n - s[cnt-1];
            Min = b[cnt-1];
        }

        // O(sqrt(n))
        while (cnt < SZ(b) && b[cnt] > N / numOfGroup) {
            Min = min(Min, b[cnt]);
            N -= b[cnt];
            cnt++;
            numOfGroup--;
        }
        
        if (numOfGroup) numInEach = N / numOfGroup;
        else numInEach = 1000000000;

        cout << min(Min, numInEach) << "\n";
    }
    return 0;
}
