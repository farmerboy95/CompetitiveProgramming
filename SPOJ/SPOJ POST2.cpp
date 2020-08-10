/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Create polynomial A with A[i] = number of i in the input A
        - Create polynomial B with B[i] = number of i in the input B
        - Multiply A and B using FFT. Degree of each polynomial is 100000 (using offset)
        - As the degree of the result is 200000, remember to extend the degree of A and B to 200000
        - Finally, use the offset to get the result.
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

const ld PI = acos(-1);

int n;
vcd a, b, fa, fb, fh, h;

// only for sz(a) == 2^x
vcd fft(const vcd &a) {
    int n = SZ(a);
    int k = 0;
    while ((1<<k) < n) k++;
    vector<int> rev(n);

    // 10110 -> rev = 01101
    rev[0] = 0;
    int high1 = -1;
    FOR(i,1,n-1) {
        if ((i & (i-1)) == 0) high1++;
        rev[i] = rev[i ^ (1<<high1)];
        rev[i] |= (1 << (k-high1-1));
    }

    // roots of unity w(n) ^ k = cos(2pi * k / n) + i * sin(2pi * k / n)
    vcd roots(n);
    FOR(i,0,n-1) {
        ld alpha = 2 * PI * i / n;
        roots[i] = cd(cos(alpha), sin(alpha));
    }

    vcd cur(n);
    FOR(i,0,n-1) cur[i] = a[rev[i]];

    // going from leaves to the root of the tree (deepest depth to the root)
    for (int len = 1; len < n; len <<= 1) {
        // next depth
        vcd ncur(n);

        // rstep = radian step
        // so for length len, we need len roots of unity, w(len * 2) ^ k, 0 <= k <= len-1
        // in other words, we consider w on one half of the circle
        int rstep = SZ(roots) / (len * 2);
        for (int pdest = 0; pdest < n;) {
            int p1 = pdest;
            FOR(i,0,len-1) {
                cd val = roots[i * rstep] * cur[p1 + len];
                ncur[pdest] = cur[p1] + val;
                ncur[pdest + len] = cur[p1] - val;
                pdest++; p1++;
            }
            pdest += len;
        }

        // move next depth to current depth
        cur.swap(ncur);
    }

    return cur;
}

// only for sz(a) == 2^x
vcd fftRev(const vcd &a) {
    vcd res = fft(a);
    FOR(i,0,SZ(res)-1) res[i] /= SZ(a);
    reverse(res.begin()+1, res.end());
    return res;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    cin >> n;
    int N = 100000, offset = N / 2;
    a.resize(2*N+1, 0);
    b.resize(2*N+1, 0);
    FOR(i,1,n) {
        int x;
        cin >> x;
        a[x + offset] += cd(1);
    }
    FOR(i,1,n) {
        int x;
        cin >> x;
        b[x + offset] += cd(1);
    }

    int k = 0;
    while ((1<<k) < SZ(a)) k++;
    while (SZ(a) < (1<<k)) a.push_back(0);

    k = 0;
    while ((1<<k) < SZ(b)) k++;
    while (SZ(b) < (1<<k)) b.push_back(0);

    fa = fft(a);
    fb = fft(b);

    fh.resize(SZ(fa));

    FOR(i,0,SZ(a)-1) fh[i] = fa[i] * fb[i];
    h = fftRev(fh);

    ll res = 0;
    FOR(i,1,n) {
        int x;
        cin >> x;
        x += N;
        res += (ll) (h[x].real() + 0.5);
    }
    cout << res;
    return 0;
}
