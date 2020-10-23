/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - The statement seems very complicated. Let's simplify it a little bit:
            Find a permutation p[0], p[1], ..., p[2^N-1] of (0,1,...,2^N-1) such that 
            p[i] xor p[(i+1) mod 2^N] has exactly K ones in its binary representation for
            each i, or declare that such p does not exist.
        - Let's imagine a graph, 2 numbers that satisfy the above condition can be connected
        by an edge.
        - So we can start at a 0, how many numbers x that 0 xor x has exactly K ones in
        its binary representation? We can find those numbers in O(N * 2^N).
        - What about a 1, how many numbers? We can easily see that 1 connects with the same
        number of numbers, but the list here is altered a bit, it would be (the list of 0) xor 1.
        In other words, the numbers in the set of 1 would be the numbers in the set of 0 xor 1.
        The same thing applies to the list of adjacent nodes of every single node.
        - So let's get back to the list of adjacent nodes of 0, we might hear about a problem
        that given 2^N nodes (indexing from 0 to 2^N-1) and a list of numbers, 2 nodes are connected
        when xor sum of 2 indices is in that list. Find the number of connected components.
        Yes, it's CODECHEF XORCMPNT. The number of components is 2^(N - SZ(basis)), basis is the
        xor basis of the list of numbers.
        - Well, get back to our problem. If the number of components > 1 => there is no way to construct
        the answer. Otherwise, there will always be at least one answer. How to construct one?
        - Now we have a xor basis of size N, we start at 0. We can choose a subset of basis to reach every
        single node from 0 to 2^N-1, but we need to reach the adjacent node. So let's choose one in the
        basis to move. Now we reach another node than 0, we have to go to the next node, what should we
        do? We can choose one in the basis that is different from the previous one.
        - Ok, let's define something like this, if we choose a number of values in the xor basis, we
        set the bit at those positions, if not, we don't set the bit. So from the previous try, we
        can see that we have to construct a list of number that 2 consecutive numbers (including the first
        and the last ones) differ in only one bit => That's the Gray Code.
        - So we can use Gray Code to choose the values in xor basis and get xor sum.
        - Ok, we can construct the list starting at 0, what about starting at S? It will mostly be the same.
        We just need to change the initial xor sum to be S and that's it.
        - Complexity O(N * 2^N)
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

const int D = 19;
int basis[D];
vector<int> a;

void insertVector(int mask) {
    int originalMask = mask;
    FOR(i,0,D-1) {
        if (!(mask & (1<<i))) continue;
        if (!basis[i]) {
            basis[i] = mask;
            a.push_back(originalMask);
            return;
        }
        mask ^= basis[i];
    }
}

int gray(int n) {
    return n ^ (n >> 1);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);

    int n, k, t;
    cin >> n >> k >> t;
    string s;
    cin >> s;
    int fi = 0;
    FOR(i,0,SZ(s)-1) fi = fi * 2 + s[i] - '0';
    FOR(j,1,(1<<n)-1)
        if (__builtin_popcount(j) == k) insertVector(j);
    if (SZ(a) < n) {
        cout << "-1";
        return 0;
    }
    cout << (1<<n) << '\n';
    FOR(i,0,(1<<n)-1) {
        int x = gray(i);
        int res = fi;
        FOR(j,0,n-1)
            if (x & (1<<j)) res ^= a[j];
        FORE(j,n-1,0) cout << (res >> j & 1);
        cout << "\n";
    }
    return 0;
}
