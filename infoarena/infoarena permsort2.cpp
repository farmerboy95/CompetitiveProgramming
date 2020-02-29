/*
    Author: Nguyen Tan Bao
    Status: AC
    Statement: 
        - Given a permutation length N and 2 kinds of operations: reversing prefixes and suffixes,
    use at most 2*N operations to sort this permutation.
    Idea:
        - For example we have a permutation 7 8 9 10 5 4 6 3 1 2, we can do reverse prefix 6 to get
        4 5 10 9 8 7 6 3 1 2 and reverse prefix 7 to get 6 7 8 9 10 5 4 3 1 2.
        - Here we can see that our initial state (k+1) is: a sorted array from k+1 to n (7 8 9 10) and 
        a permutation length k (5 4 6 3 1 2), we need to find the position of k (6) and reverse
        prefix k-1, then reverse prefix k to go to state k. We only use 2 operations to move one step
        down, so that it would take us 2*N operations at most.
        - The remaining problem is to find the position of k, we can use BIT to count number of numbers (x)
        that are larger than k and their indexes are also larger than index of k. Position of k = (initial
        position of k) + x, because when we are at step k+1, all numbers that are larger than k are placed 
        to the left of k, it means k would move to the right x steps.
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
const int MAXN = 100010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, a[MAXN], t[MAXN], pos[MAXN], numBigger[MAXN];
vector<int> res;

int get(int u) {
    int res = 0;
    while (u <= 100000) {
        res += t[u];
        u = u + (u & (-u));
    }
    return res;
}

void update(int u) {
    while (u) {
        t[u]++;
        u = u - (u & (-u));
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    freopen("permsort2.in", "r", stdin);
    freopen("permsort2.out", "w", stdout);
    cin >> n;
    FOR(i,1,n) cin >> a[i];
    FOR(i,1,n) pos[a[i]] = i;
    FORE(i,n,1) {
        numBigger[a[i]] = get(a[i]+1);
        update(a[i]);
    }

    FORE(i,n,1) {
        int p = pos[i] + numBigger[i];
        if (p-1 > 0) res.push_back(p-1);
        res.push_back(p);
    }
    cout << SZ(res) << "\n";
    FOR(i,0,SZ(res)-1) cout << "P " << res[i] << "\n";
    return 0;
}
