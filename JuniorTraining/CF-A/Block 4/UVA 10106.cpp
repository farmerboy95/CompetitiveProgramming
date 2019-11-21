/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: Do as problem requirement
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
const int MAXN = 260;
const int MAXM = 30010;
const int MAXK = 16;
const int MAXQ = 200010;

string x, y;
int a[510], res[510], m[510], lef;

void mul2(int u, int pos) {
    int nho = 0;
    FORE(i,500,lef) {
        int k = a[i] * u + nho;
        m[pos] = k % 10;
        nho = k / 10;
        pos--;
    }
    while (nho) {
        m[pos] = nho % 10;
        nho /= 10;
        pos--;
    }
}

void add() {
    int nho = 0;
    FORE(i,500,1) {
        int k = res[i] + m[i] + nho;
        res[i] = k % 10;
        nho = k / 10;
    }
    if (nho) res[0] = nho;
}

void mul(int u, int kc) {
    FOR(i,0,500) m[i] = 0;
    int now = 501;
    while (kc) {
        kc--;
        now--;
    }
    now--;
    mul2(u, now);
    add();
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    while (cin >> x >> y) {
        MS(a, 0);
        MS(res, 0);
        MS(m, 0);
        lef = 501;
        FORE(i,SZ(x)-1,0) {
            lef--;
            a[lef] = x[i] - '0';
        }
        
        FORE(i,SZ(y)-1,0) {
            int g = y[i] - '0';
            mul(g, SZ(y)-1-i);
        }

        int vt = -1;
        FOR(i,0,500) 
            if (res[i]) {
                vt = i;
                break;
            }
        if (vt == -1) cout << "0\n";
        else {
            FOR(i,vt,500) cout << res[i];
            cout << "\n";
        }

    }
    return 0;
}
