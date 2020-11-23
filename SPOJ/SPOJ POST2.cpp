/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Create polynomial A with A[i] = number of i in the input A
        - Create polynomial B with B[i] = number of i in the input B
        - Multiply A and B using FFT. Degree of each polynomial is 100000 (using offset)
        - As the degree of the result is 200000, remember to use the offset properly to get the result.
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

void fft(vcd &a, int invert) {
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
        if (i < rev[i]) swap(a[i], a[rev[i]]);
    }

    // roots of unity w(n) ^ k = cos(2pi * k / n) (+/-) i * sin(2pi * k / n)
    vcd roots(n/2);
    ld alpha = 2 * acos(-1) / n * (invert ? -1 : 1);
    FOR(i,0,n/2-1) roots[i] = cd(cos(alpha * i), sin(alpha * i));

    for (int len = 2; len <= n; len <<= 1) {
        int step = n / len;
        for (int i = 0; i < n; i += len) {
            FOR(j,0,len/2-1) {
                cd u = a[i+j], v = a[i+j+len/2] * roots[j * step];
                a[i+j] = u+v;
                a[i+j+len/2] = u-v;
            }
        }
    }

    if (invert) FOR(i,0,n-1) a[i] /= n;
}

vector<ll> multiply(vector<ll> &polyA, vector<ll> &polyB) {
    vcd fPolyA(ALL(polyA)), fPolyB(ALL(polyB));
    int n = 1;
    while (n < SZ(polyA) + SZ(polyB) - 1) n <<= 1;
    fPolyA.resize(n); fPolyB.resize(n);

    fft(fPolyA, 0); fft(fPolyB, 0);
    FOR(i,0,n-1) fPolyA[i] *= fPolyB[i];

    fft(fPolyA, 1);
    n = SZ(polyA) + SZ(polyB) - 1;
    vector<ll> res(n);
    FOR(i,0,n-1) res[i] = (ll) round(fPolyA[i].real());

    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    vector<ll> a, b;
    int n;
    cin >> n;
    int N = 100000, offset = N / 2;
    a.resize(N+1);
    b.resize(N+1);
    FOR(i,1,n) {
        int x;
        cin >> x;
        a[x + offset]++;
    }
    FOR(i,1,n) {
        int x;
        cin >> x;
        b[x + offset]++;
    }

    vector<ll> res = multiply(a, b);
    ll kq = 0;
    FOR(i,1,n) {
        int x;
        cin >> x;
        x += N;
        kq += res[x];
    }
    cout << kq;
    return 0;
}
