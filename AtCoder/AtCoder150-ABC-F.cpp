/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - The value of k uniquely determines x = a[k] xor b[0]. We can determine which k 
        work for each bit independently and take the intersection to get the final answer. 
        In the 1-bit version, we want to know which rotations of a are equal to either b 
        or !b (corresponding to x=0 and x=1). We can do it by doubling a and applying a 
        string-searching algorithm (e.g. KMP) to find all occurrences of b and !b.
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
const int MAXN = 400010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, a[MAXN], b[MAXN], A[MAXN], B[MAXN], bak[MAXN];
bool g[MAXN][2];
int f[MAXN];

void kmpPreprocess() {
    bak[0] = 0;
    FOR(i,1,n-1) {
        int k = bak[i-1];
        while (k > 0 && B[k] != B[i]) k = bak[k-1];
        if (B[k] == B[i]) bak[i] = k+1;
        else k = 0;
    }
}

void kmpSearch(int w) {
    int j = 0;
    FOR(i,0,2*n-2) {
        while (j > 0 && A[i] != B[j]) j = bak[j-1];
        if (A[i] == B[j]) j++;
        else j = 0;
        if (j == n) {
            g[i-n+1][w] = true;
            j = bak[j-1];
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,0,n-1) cin >> a[i];
    // doubling a
    FOR(i,n,2*n-2) a[i] = a[i-n];
    FOR(i,0,n-1) cin >> b[i];
    FOR(i,0,n-1) f[i] = 0;
    // consider each bit
    FORE(bit,29,0) {
        FOR(i,0,2*n-2) A[i] = (a[i] >> bit) & 1;
        FOR(i,0,n-1) B[i] = (b[i] >> bit) & 1;
        FOR(i,0,n-1) g[i][0] = g[i][1] = false;
        // use kmp to find B in A
        kmpPreprocess();
        kmpSearch(0);
        // reverse B, find it in A
        FOR(i,0,n-1) B[i] = 1-B[i];
        kmpPreprocess();
        kmpSearch(1);
        FOR(i,0,n-1)
            if (f[i] != -1) {
                // remove positions in A that do not have appearance of B
                if (!(g[i][0] | g[i][1])) f[i] = -1;
                // otherwise, calculate the answer
                else if (g[i][1]) f[i] += (1<<bit);
            }
    }
    FOR(i,0,n-1)
        if (f[i] != -1) cout << i << ' ' << f[i] << "\n";
    return 0;
}
