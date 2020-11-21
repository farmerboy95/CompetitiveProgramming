/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let's denote all number a[1] to a[n]
        - First let's get f[i] = a[1] XOR a[i], i = 2 .. n
        - We need to find a[1] 
            => the rest using XOR
        - If it exist f[x] = 0 
            => a[1] = a[1] AND a[x] 
            => the rest (n-1 + 1 operations)
        - If it exist f[x] = f[y] 
            => a[x] = a[x] AND a[y] 
            => a[1] using f[x] = a[1] XOR a[x]
            => a[1] = f[x] XOR a[x]
            => the rest (n-1 + 1 operations)
        - If none of the above conditions exists, the array is a permutation of [0, n-1].
        - So the f[] array is also a permutation of [0, n-1], including f[1] = 0.
        - Let's check position x that a[1] XOR a[x] = 1, so we can get all the bits of a[1]
        except the least significant one with a[1] AND a[x].
        - Similarly, let's check position y that a[1] XOR a[y] = 2, so we can get all the 
        bits of a[1] except the second least significant one with a[1] AND a[y].
        - OR those value together, we have a[1].
        - Number of operations: n-1 XOR and 2 AND.
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

int a[MAXN], f[MAXN], n;
vector<int> b[MAXN];

int ask(string op, int i, int j) {
    cout << op << ' ' << i << ' ' << j << endl;
    int res;
    cin >> res;
    return res;
}

void printResult() {
    cout << "!";
    FOR(i,1,n) cout << " " << a[i];
    cout << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;

    FOR(i,2,n) {
        f[i] = ask("XOR", 1, i);
        b[f[i]].push_back(i);
    }

    if (SZ(b[0])) {
        int x = b[0][0];
        a[1] = ask("AND", 1, x);
        FOR(i,2,n) a[i] = f[i] ^ a[1];
        printResult();
        return 0;
    }

    FOR(i,1,n-1)
        if (SZ(b[i]) > 1) {
            int x = b[i][0], y = b[i][1];
            a[x] = ask("AND", x, y);
            a[1] = f[x] ^ a[x];
            FOR(j,2,n) a[j] = f[j] ^ a[1];
            printResult();
            return 0;
        }

    a[1] = ask("AND", 1, b[1][0]) | ask("AND", 1, b[2][0]);
    FOR(i,2,n) a[i] = f[i] ^ a[1];
    printResult();
    
    return 0;
}
