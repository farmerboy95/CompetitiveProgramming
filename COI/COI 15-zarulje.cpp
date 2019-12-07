/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let i is the initial position, l and r are positions on the left and right of i that 
        we are considering which to turn off
        - a[l] == a[r] if and only if there is no a[j] (l < j < i and i < j < r) that a[j] < a[l], a[r]
        - It means that the list of number which can be put into consideration on the left and right of i
        will be descending from i to respective left and right end of the array.

        - For first 2 subtasks, for each initial position, we can create left and right array, for each number
        k, multiply the result by C(leftCount(k) + rightCount(k), leftCount(k)), because number k will be appeared
        consecutively in each array (if exists), and we choose leftCount(k) in the list of leftCount(k) + rightCount(k)

        - For the last subtask, let smallR[i] is the nearest number to the right of i that a[smallR[i]] <= a[i],
        we can calculate this array using a simple stack, then we can create right array when initial pos = 1
        - As we move i from 1 to n, we can create left array using stack but only store the changed values of leftCount.
        Similarly, we modify the right array as we move i to the right and store the changed values of rightCount
        - How can we detect all the changed values of rightCount? If a[i+1] <= a[i] (we move from i-1 to i), there is no
        change but to remove a[i] (as smallR[i] == i+1), otherwise (a[i+1] > a[i]), we may have to add some values to 
        rightCount, we can use smallR[i] to add (stop when we meet an already added value).
        - This operation takes O(n) because each value could only be added and removed once in the whole iteration (remove
        only when i touch that value)

        - We can use a set to store list of changed values, remove all changed values from result, update new leftCount and
        rightCount, then add changed values to result.
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
typedef pair<int, II> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;
 
const ll MODBASE = 1000000007LL;
const int MAXN = 200010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, q, a[MAXN], smallR[MAXN], lCnt[MAXN], rCnt[MAXN], f[MAXN];
ll res[MAXN], fac[MAXN], inv[MAXN];
stack<int> s;
vector<II> lChanges, rChanges;
set<int> changed;

ll C(int n, int k) {
    return fac[n] * inv[n-k] % MODBASE * inv[k] % MODBASE;
}

ll invC(int n, int k) {
    return fac[n-k] * fac[k] % MODBASE * inv[n] % MODBASE;
}

ll binPowMod(ll a, ll b, ll m) {
    a %= m;
    ll res = 1;
    while (b > 0) {
        if (b & 1LL) res = res * a % m;
        a = a * a % m;
        b >>= 1LL;
    }
    return res;
}

void solve() {
    a[0] = a[n+1] = 0;
    // init factorial and inverse factorial
    fac[0] = 1;
    inv[0] = binPowMod(fac[0], MODBASE-2, MODBASE);
    FOR(i,1,n) {
        fac[i] = fac[i-1] * i % MODBASE;
        inv[i] = binPowMod(fac[i], MODBASE-2, MODBASE);
    }

    // get smallR
    s.push(0);
    FOR(i,1,n+1) {
        while (SZ(s) && a[i] <= a[s.top()]) {
            int h = s.top();
            smallR[h] = i;
            s.pop();
        }
        s.push(i);
    }
    while (SZ(s)) s.pop();

    // init right part when position is 1
    int p = 2;
    while (p <= n) {
        rCnt[a[p]]++;
        f[p] = 1;
        p = smallR[p];
    }

    res[1] = 1;
    res[n] = 1;
    s.push(0);
    ll kq = 1;
    FOR(i,2,n-1) {
        changed.clear();
        lChanges.clear();
        rChanges.clear();
        while (a[i-1] < a[s.top()]) {
            int h = s.top();
            lChanges.emplace_back(II(a[h], -1));
            changed.insert(a[h]);
            s.pop();
        }
        s.push(i-1);
        lChanges.emplace_back(II(a[i-1], 1));
        changed.insert(a[i-1]); 

        f[i] = 0;
        rChanges.emplace_back(II(a[i], -1));
        changed.insert(a[i]); 

        int p = i+1;
        while (p <= n) {
            if (f[p]) break;
            rChanges.emplace_back(II(a[p], 1));
            changed.insert(a[p]);
            f[p] = 1;
            p = smallR[p];
        }

        // remove from result
        FORALL(it, changed) kq = kq * invC(lCnt[*it] + rCnt[*it], lCnt[*it]) % MODBASE;

        // update cnt arrays
        FOR(j,0,SZ(lChanges)-1) lCnt[lChanges[j].FI] += lChanges[j].SE;
        FOR(j,0,SZ(rChanges)-1) rCnt[rChanges[j].FI] += rChanges[j].SE;

        // add
        FORALL(it, changed) kq = kq * C(lCnt[*it] + rCnt[*it], lCnt[*it]) % MODBASE;

        res[i] = kq;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> q;
    FOR(i,1,n) cin >> a[i];

    solve();

    while (q--) {
        int x;
        cin >> x;
        cout << res[x] << "\n";
    }
    return 0;
}
