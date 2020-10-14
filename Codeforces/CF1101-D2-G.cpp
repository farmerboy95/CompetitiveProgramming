/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - https://codeforces.com/blog/entry/68953
        - Notice that, saying all subsets of a set yield non-zero xor is equivalent to saying 
        all subsets of that set yield different xor-sum. The xor-sums of segments in the answer 
        partition need to be independent vectors. This is the first of the two main observations.
        - The second one is that, suppose we picked some segments [l1=1, r1], [l2=r1+1, r2] , ...,
        [lk=r[k-1]+1, rk]. Let p[i] be the xor of the xor-sums of the first i segments. Then, observe 
        that, every possible xor of the numbers from some non-empty subset of these segments can also 
        be obtained by xor-ing some subset from the set {p1, p2, ..., pk} and vice versa, which means 
        that the set of xor-sums of these segments and the set of prefix xors of these segments produces
        the exact same set of vectors in Z(30, 2). So, if the xor-sums of these segments has to be 
        independent, then so does the prefix xors of these segments. Thus, the answer simply equals 
        the basis size of the n prefix xors of the array. The only exception when the answer equals 
        −1 happens, when the xor-sum of all the elements in the array is 0.
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

int n;
int basis[30];
int D = 30, sz = 0;

void insertVector(int mask) {
    FOR(i,0,D-1) {
        if (!(mask & (1<<i))) continue;
        if (!basis[i]) {
            basis[i] = mask;
            sz++;
            return;
        }
        mask ^= basis[i];
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    int prefix = 0;
    FOR(i,1,n) {
        int x;
        cin >> x;
        prefix ^= x;
        insertVector(prefix);
    }
    if (prefix == 0) cout << -1;
    else cout << sz;
    return 0;
}
