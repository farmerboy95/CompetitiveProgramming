/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Use MO's algorithm
        - Some proofs and explanation: https://blog.anudeep2011.com/mos-algorithm/
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
const int MAXN = 500010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

struct Data {
    int l, r, cs, block;
    Data(int l = 0, int r = 0, int cs = 0, int block = 0) : l(l), r(r), cs(cs), block(block) {}
};

bool operator<(Data a, Data b) {
    if (a.block == b.block) return a.r < b.r; 
    return a.block < b.block;
}

vector<Data> b;
int n, q, a[MAXN], kq, cnt[MAXN], res[MAXN];

void add(int u) {
    kq += (cnt[a[u]]++ == 0);
}
void del(int u) {
    kq -= (--cnt[a[u]] == 0);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> q;
    FOR(i,1,n) cin >> a[i];

    // length of one block
    int k = int(sqrt(n));
    // num of blocks
    int part = n / k + (n % k > 0);

    FOR(i,1,q) {
        int l, r;
        cin >> l >> r;
        b.push_back(Data(l, r, i, l / part - (l % part == 0)));
    }

    sort(ALL(b));
    int currL = 1, currR = 1;
    cnt[a[1]]++;
    kq = 1;
    FOR(i,0,q-1) {
        while (currR > b[i].r) del(currR--);
        while (currR < b[i].r) add(++currR);
        while (currL < b[i].l) del(currL++);
        while (currL > b[i].l) add(--currL);
        res[b[i].cs] = kq;
    }

    FOR(i,1,q) cout << res[i] << "\n";
    return 0;
}
