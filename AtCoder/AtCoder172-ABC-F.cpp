/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - So the problem is to find minimum k (0 <= k < a[1]) that (a[1]-k) ^ (a[2]+k) ^ a[3] ^ a[4] ^ ... ^ a[n] == 0
        <=> (a[1]-k) ^ (a[2]+k) == a[3] ^ a[4] ^ ... ^ a[n]
        - Or we can rephrase it as: Find 2 numbers A, B that
        A + B = a[1] + a[2] = sum
        A ^ B = a[3] ^ a[4] ^ ... ^ a[n] = xorSum
        1 <= A <= a[1], A max
        - So we have A + B = (A ^ B) + 2 * (A & B)
        - Or sum = xorSum + 2 * andSum
        <=> andSum = (sum - xorSum) / 2
        - If sum - xorSum < 0 or sum - xorSum is odd => -1
        - Now we check every bits of xorSum from most significant bit to the least one. We have this table
        A 1 1 0 0
        B 1 0 1 0
        ^ 0 1 1 0
        & 1 0 0 0
        - So if xorSum contains a 1 at a specific bit (at k-th bit), if andSum also contains a 1 at k, there
        is no answer (-1), otherwise, we greedily set k-th bit of B is 1. If xorSum contains a 0 at k-th bit,
        it depends on the k-th bit of andSum to set bit for A and B.
        - The reason of doing this is to find the smallest A, to see if smallest A <= a[1] or not, if not,
        there is no answer. 
        - Otherwise, there is only one case left, xor = 1, and = 0, we are not very sure k-th bit of which number
        is set. We can check xorSum again as above and check for xorSum containing a 1 at k-th bit only, if adding
        this bit to A does not make A > a[1], we can just set that bit for A, obviously, as this would make the
        answer largest. Do the same thing to the rest of the iteration.
        - Finally, remember to check if A = 0 after all, if yes, there is no answer.
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
const int MAXN = 310;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n;
ll a[MAXN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n) cin >> a[i];
    ll xorSum = 0;
    FOR(i,3,n) xorSum ^= a[i];
    ll sum = a[1] + a[2];
    if (sum - xorSum < 0 || (sum - xorSum) % 2) {
        cout << -1;
        return 0;
    }
    ll andSum = (sum - xorSum) / 2;
    ll A = 0, B = 0;
    FORE(i,45,0)
        if (xorSum & (1LL << i)) {
            if (andSum & (1LL << i)) {
                cout << -1;
                return 0;
            }
            B |= (1LL << i);
        } else {
            if (andSum & (1LL << i)) {
                A |= (1LL << i);
                B |= (1LL << i);
            }
        }
    if (A > a[1]) {
        cout << -1;
        return 0;
    }
    FORE(i,45,0)
        if (xorSum & (1LL << i)) {
            if ((A ^ (1LL << i)) <= a[1]) {
                A ^= (1LL << i);
                B ^= (1LL << i);
            }
        }
    if (A == 0) {
        cout << -1;
        return 0;
    }
    cout << a[1] - A;
    return 0;
}
