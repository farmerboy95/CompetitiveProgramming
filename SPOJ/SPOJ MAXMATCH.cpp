/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - There are only 3 different types of characters in the string: a, b, c
        - We consider each character, create a binary vector using the character, for example, character a
        - So the element at i is 0 if s[i] != 'a', otherwise, the element at i is 1
        - Now we have 2 identical binary strings, we need to shift one on another and find the number
        of (1, 1) pairs in each shift
                            11011110
                     11011110                => 0
                      11011110               => 1 (first 1)
                       11011110              => 2 (first 1 and second 1, pair (0, 0) does not count)
                        11011110             => 2
                         11011110            => 3
                          11011110           => 3
                           11011110          => 4
                            11011110         => 6
                             11011110        => 4
                              11011110       => 3
                               11011110      => 3
                                11011110     => 2
                                 11011110    => 2
                                  11011110   => 1
                                   11011110  => 0
        - We create a polynomial based on the binary string we've got. For the above string, the polynomial
        should be: 0x^0 + 1x^1 + 1x^2 + 1x^3 + 1x^4 + 0x^5 + 1x^6 + 1x^7
        - Let's multiply the above polynomial with the reverse of itself, we should get the polynomial with
        the same coefficients as the above example. Now we can use coefficients that the problem need to solve
        it.
        - It's hard to describe but this is a famous example of applications of FFT, one should read here
        https://cp-algorithms.com/algebra/fft.html or FFT part in CP4 book to understand.
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

string s;
vector<int> a, lis;
int res[MAXN];
vector<char> dict = {'a', 'b', 'c'};

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
    cin >> s;
    for (char ch : dict) {
        a.clear();
        FOR(i,0,SZ(s)-1) a.push_back((s[i] == ch));

        A.clear();
        B.clear();
        FOR(i,0,SZ(a)-1) {
            A.push_back(a[i]);
            B.push_back(a[i]);
        }
        reverse(ALL(A));

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

        FOR(i,0,SZ(s)-2) {
            int g = int(H[i].real() + 0.5);
            res[SZ(s)-1-i] += g;
        }

    }
    int Max = -1;
    FOR(i,1,SZ(s))
        if (res[i] > Max) {
            Max = res[i];
            lis.clear();
            lis.push_back(i);
        } else if (res[i] == Max) lis.push_back(i);
    cout << Max << "\n";
    FOR(i,0,SZ(lis)-1) cout << lis[i] << ' ';
    return 0;
}
