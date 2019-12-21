#include <bits/stdc++.h>
#define base 1000000007LL
#define ll long long
#define X first
#define Y second
#define ld double
#define pb push_back
#define EPS 1e-9
#define all(a) a.begin(),a.end()
#define sz(a) int((a).size())
#define ms(s, n) memset(s, n, sizeof(s))
#define FOR(i,a,b) for (int i = (a); i <= (b); i++)
#define FORE(i,a,b) for (int i = (a); i >= (b); i--)
#define FORALL(it, a) for (__typeof((a).begin()) it = (a).begin(); it != (a).end(); it++)
#define what_is(x) cout << #x << " is " << x << endl;
#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
//__builtin_ffs(x) return 1 + index of least significant 1-bit of x
//__builtin_clz(x) return number of leading zeros of x
//__builtin_ctz(x) return number of trailing zeros of x

using namespace std;
typedef pair<int, int> II;
typedef pair<ll, II> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;

void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
	cout << *it << " = " << a << endl;
	err(++it, args...);
}

int n;
vcd a;

// only for sz(a) == 2^x
vcd fft(const vcd &a) {
    int n = sz(a);
    int k = 0;
    while ((1<<k) < n) k++;
    vector<int> rev(n);

    rev[0] = 0;
    int high1 = -1;
    FOR(i,1,n-1) {
        if ((i & (i-1)) == 0) high1++;
        rev[i] = rev[i ^ (1<<high1)];
        rev[i] |= (1 << (k-high1-1));
    }

    vcd roots(n);
    FOR(i,0,n-1) {
        double alpha = 2 * M_PI * i / n;
        roots[i] = cd(cos(alpha), sin(alpha));
    }

    vcd cur(n);
    FOR(i,0,n-1) cur[i] = a[rev[i]];

    for (int len = 1; len < n; len <<= 1) {
        vcd ncur(n);
        int rstep = sz(roots) / (len * 2);
        for (int pdest = 0; pdest < n;) {
            int p1 = pdest;
            FOR(i,0,len-1) {
                cd val = roots[i * rstep] * cur[p1 + len];
                ncur[pdest] = cur[p1] + val;
                ncur[pdest + len] = cur[p1] - val;
                pdest++, p1++;
            }
            pdest += len;
        }
        cur.swap(ncur);
    }

    return cur;
}

// only for sz(a) == 2^x
vcd fftRev(const vcd &a) {
    vcd res = fft(a);
    FOR(i,0,sz(res)-1) res[i] /= sz(a);
    reverse(res.begin()+1, res.end());
    return res;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(NULL);
    cin >> n;
    FOR(i,0,n-1) {
        int x;
        cin >> x;
        a.pb(x);
    }
    int k = 0;
    while ((1<<k) < sz(a)) k++;
    while (sz(a) < (1<<k)) a.pb(0);
    vcd res = fft(a);
    FOR(i,0,sz(a)-1) printf("%.4lf %.4lf\n", res[i].real(), res[i].imag());
    printf("\n");
    vcd fft_rev = fftRev(res);
    FOR(i,0,sz(a)-1) printf("%.4lf %.4lf\n", fft_rev[i].real(), fft_rev[i].imag());
    return 0;
}
