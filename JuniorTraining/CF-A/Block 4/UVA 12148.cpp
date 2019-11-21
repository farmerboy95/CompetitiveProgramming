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
const int MAXN = 1010;
const int MAXM = 30010;
const int MAXK = 16;
const int MAXQ = 200010;

struct Data {
    int a, b, c, d;
    Data(int a = 0, int b = 0, int c = 0, int d = 0) : a(a), b(b), c(c), d(d) {}
};

int n;
Data a[MAXN];
int monthDays[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

bool isLeapYear(int y) {
    if (y % 100 == 0) return y % 400 == 0;
    return y % 4 == 0;
}

Data getNextDay(Data a) {
    a.a++;
    int monthDay = monthDays[a.b];
    if (isLeapYear(a.c) && a.b == 2) monthDay++;
    if (a.a > monthDay) {
        a.a = 1;
        a.b++;
        if (a.b > 12) {
            a.b = 1;
            a.c++;
        }
    }
    return a;
}

bool check(int u) {
    Data b = getNextDay(a[u]);
    return (b.a == a[u+1].a && b.b == a[u+1].b && b.c == a[u+1].c);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    while (cin >> n && n) {
        FOR(i,1,n) cin >> a[i].a >> a[i].b >> a[i].c >> a[i].d;
        int res = 0, sum = 0;
        FOR(i,1,n-1)
            if (check(i)) {
                res++;
                sum += a[i+1].d - a[i].d;
            }
        cout << res << ' ' << sum << "\n";
    }
    return 0;
}
