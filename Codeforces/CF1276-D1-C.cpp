/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Create an array with distinct numbers of initial array and their occurences in the initial array
        - Sort new array ascending by the occurences
        - First, we would have to find the largest rectangle (N * M) that we can build
        - Assume that N <= M, so the max occurence of a number should not exceed N
        - Let N is an upper bound of occurence, we find the maximum number that we can take from initial array
        using binary search, let it be "sum". From "sum", we can easily get M
        - How to fill in numbers into the rectangle? We fill them diagonally
        - We start from (1, 1) then go to (2, 2) (3, 3) ... until we touch x = n, we go back to (2, 1). If
        y > M, we set y = 1 and continue to fill.
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
typedef pair<int, II> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;
 
const ll MODBASE = 1000000007LL;
const int MAXN = 400010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, a[MAXN], kq[MAXN];
vector<II> b;
vector<int> s;

int toIndex(int u, int v, int M) {
    return (u-1) * M + v;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n) cin >> a[i];
    sort(a+1, a+n+1);
    int cnt = 1;
    FOR(i,2,n)
        if (a[i] == a[i-1]) cnt++;
        else {
            b.emplace_back(II(cnt, a[i-1]));
            cnt = 1;
        }
    b.emplace_back(II(cnt, a[n]));

    sort(ALL(b));
    FOR(i,0,SZ(b)-1) {
        if (i == 0) s.emplace_back(b[0].FI);
        else s.emplace_back(s[SZ(s)-1] + b[i].FI);
    }
    II res = II(-1, -1);
    FOR(N,1,n) {
        int M = n / N;
        if (M >= N) {
            int dau = 0, cuoi = SZ(b)-1, mid;
            while (dau <= cuoi) {
                mid = (dau + cuoi) >> 1;
                if (b[mid].FI > N) cuoi = mid-1;
                else dau = mid+1;
            }

            int sum = 0;
            if (cuoi >= 0) {
                sum = s[cuoi] + (SZ(s) - cuoi - 1) * N;
            }
            else {
                sum = (SZ(s) - cuoi - 1) * N;
            }
            // cout << sum << endl;
            M = sum / N;
            if (M >= N) {
                if (res.FI == -1) res = II(N, M);
                else if (res.FI * res.SE < N * M) res = II(N, M);
            }
        }
    }

    cout << res.FI * res.SE << "\n";
    cout << res.FI << ' ' << res.SE << "\n";

    int x = 1, y = 1, rootY = 1;
    FORE(i,SZ(b)-1,0) {
        FOR(j,1,min(b[i].FI, res.FI)) {
            // cout << x << ' ' << y << ' ' << toIndex(x, y, res.SE) << endl;
            kq[toIndex(x, y, res.SE)] = b[i].SE;
            x = x + 1;
            y = y + 1;
            if (x > res.FI) {
                x = 1;
                rootY++;
                y = rootY;
            }
            if (y > res.SE) y = 1;
        }
    }
    FOR(i,1,res.FI*res.SE) {
        cout << kq[i] << ' ';
        if (i % res.SE == 0) cout << "\n";
    }
    return 0;
}
