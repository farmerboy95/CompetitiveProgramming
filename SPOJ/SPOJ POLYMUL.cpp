/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: Purely polynomial multiplication, using FFT
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
const ld PI = acos(-1);

int n, t;
vcd A, B, fa, fb, fh, H;

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

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> t;
    while (t--) {
        cin >> n;
        A.clear();
        B.clear();
        FOR(i,0,n) {
            int x;
            cin >> x;
            A.push_back(x);
        }
        FOR(i,0,n) {
            int x;
            cin >> x;
            B.push_back(x);
        }
        reverse(ALL(A));
        reverse(ALL(B));
        while (SZ(A) < SZ(B)) A.push_back(0);
        while (SZ(A) > SZ(B)) B.push_back(0);

        int k = 0;
        while ((1<<k) < SZ(A)) k++;
        while (SZ(A) < (1<<k)) {
            A.push_back(0);
            B.push_back(0);
        }

        FOR(i,1,(1<<k)) {
            A.push_back(0);
            B.push_back(0);
        }

        fa = fft(A);
        fb = fft(B);

        fh.resize(SZ(fa));
        FOR(i,0,SZ(A)-1) fh[i] = fa[i] * fb[i];
        H = fftRev(fh);

        bool co = false;
        FORE(i,SZ(H)-1,0) {
            ll val = (ll) (H[i].real() + 0.5);
            if (val > 0) co = true;
            if (co) cout << val << " ";
        }
        cout << "\n";
    }
    return 0;
}
