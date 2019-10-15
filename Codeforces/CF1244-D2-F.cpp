/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Divide the circular array into parts, each part has elements that have the same color.
        - Notice that parts with 2 or more elements will not change color after iterations.
        - What about parts with 1 element? (Denote white color as 0, black color as 1 in below examples)
        - Let the length of consecutive 1-element parts is "cnt"
            + 0000[10101]000 -> 0000[01010]000 -> 0000[00100]000 -> 0000[00000]000 (result will not change after (cnt / 2 + 1) iterations)
            + 0000[1010]1111 -> 0000[0101]1111 -> 0000[0011]1111 (result will not change after (cnt / 2) iterations)
        - Simply divide initial array into parts and merge consecutive 1-element parts into one and get the result.
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
const int MAXM = 1010;
const int MAXK = 110;
const int MAXQ = 200010;

struct Data {
    int type; // 0: full W - 1: full B - 2: inter
    int l, r;
    Data(int type, int l, int r) : type(type), l(l), r(r) {}
};

int n, k;
string s;
vector<int> a;
vector<II> b;
vector<Data> c;

bool isFull() {
    FOR(i,0,n-1)
        if (s[i] != s[0]) return false;
    return true;
}

bool isInter() {
    FOR(i,1,n-1)
        if (s[i] == s[i-1]) return false;
    if (s[0] == s[n-1]) return false;
    return true;
}

void getGroups(int lef) {
    int l = lef, r = 0;
    while (1) {
        if (a[r] == a[l]) {
            r = (r + 1) % n;
            if (r == lef) {
                r = (r - 1 + n) % n;
                b.emplace_back(II(l, r));
                break;
            }
        }
        else {
            b.emplace_back(II(l, (r - 1 + n) % n));
            l = r;
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> k;
    cin >> s;

    // check if the initial array is full of W or B
    if (isFull()) {
        cout << s;
        return 0;
    }

    // check if the initial array is WBWB.... or BWBW...
    if (isInter()) {
        if (k % 2 == 0) cout << s;
        else {
            FOR(i,0,n-1)
                if (s[i] == 'W') s[i] = 'B';
                else s[i] = 'W';
            cout << s;
        }
        return 0;
    }

    // denote W as 0, B as 1
    FOR(i,0,n-1)
        if (s[i] == 'W') a.emplace_back(0);
        else a.emplace_back(1);
    
    // start to divide, but first, we need to get the number of consecutive elements from n-1 backward 
    // that have the same color as a[0]
    int lef = 0;
    while (1) {
        lef = (lef - 1 + n) % n;
        if (a[lef] != a[0]) {
            lef = (lef + 1) % n;
            break;
        }
    }

    // divide
    getGroups(lef);

    // merge consecutive 1-element parts, here we get the first non 1-element and start to iterate from it
    int start = -1;
    FOR(i,0,SZ(b)-1)
        if (b[i].FI != b[i].SE) {
            start = i;
            break;
        }

    int z = start;
    while (1) {
        int i = z;
        if (b[i].FI == b[i].SE) {
            if (c.empty()) c.push_back(Data(2, b[i].FI, b[i].SE));
            else if (c[SZ(c)-1].type == 2) c[SZ(c)-1].r = b[i].SE;
            else c.push_back(Data(2, b[i].FI, b[i].SE));
        }
        else {
            if (a[b[i].FI] == 0) {
                c.push_back(Data(0, b[i].FI, b[i].SE));
            }
            else {
                c.push_back(Data(1, b[i].FI, b[i].SE));
            }
        }
        z = (z + 1) % SZ(b);
        if (z == start) break;
    }

    // get the result
    FOR(i,0,SZ(c)-1)
        if (c[i].type == 2) {
            int l = c[i].l, r = c[i].r;
            int L = a[c[(i - 1 + SZ(c)) % SZ(c)].l];
            int cnt = 1;
            while (l != r) {
                l = (l + 1) % n;
                cnt++;
            }
            l = c[i].l;
            // 2 cases for odd cnt and even cnt
            if (cnt % 2) {
                int d = cnt / 2;
                if (k < d+1) {
                    FOR(i,1,k) {
                        a[l] = L;
                        l = (l+1) % n;
                    }
                    FOR(i,1,k) {
                        a[r] = L;
                        r = (r - 1 + n) % n;
                    }
                    while (l != r) {
                        L = 1-L;
                        a[l] = L;
                        l = (l+1) % n;
                    }
                    L = 1-L;
                    a[l] = L;
                }
                else {
                    FOR(i,1,cnt) {
                        a[l] = L;
                        l = (l+1) % n;
                    }
                }
            }
            else {
                int d = cnt / 2;
                if (k < d) {
                    FOR(i,1,k) {
                        a[l] = L;
                        l = (l+1) % n;
                    }
                    FOR(i,1,k) {
                        a[r] = 1-L;
                        r = (r - 1 + n) % n;
                    }
                    while (l != r) {
                        L = 1-L;
                        a[l] = L;
                        l = (l+1) % n;
                    }
                    L = 1-L;
                    a[l] = L;
                }
                else {
                    FOR(i,1,d) {
                        a[l] = L;
                        l = (l+1) % n;
                    }
                    L = 1-L;
                    FOR(i,1,d) {
                        a[l] = L;
                        l = (l+1) % n;
                    }
                }
            }
        }

    FOR(i,0,n-1)
        if (a[i]) cout << 'B';
        else cout << 'W';
    return 0;
}
