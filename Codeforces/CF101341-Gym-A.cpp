/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - I'll call the total balance the sum of 1 for every opening bracket and -1 for every 
        closing bracket, and the minimum balance — the minimum of total balances of every prefix 
        (minimal balance cannot be positive).
        - Divide the bracket sequences by two groups — with the positive total balance and with 
        the negative total balance (the sequences with the zero total balance may be attached to 
        any of these two). These two groups are symmetric, so consider only one of them — to deal 
        with the other one you may just reverse the sequences and apply the same thoughts. So, we 
        have a group of bracket sequences, all of which have non-negative total balance. How to order 
        them properly? It is now obvious that they should be sorted by minimum balance, started from 
        the minimum balance 0, so that the first sequences don't ruin everything.
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

struct Data {
    int d, s, pos;
    Data(int d = 0, int s = 0, int pos = 0) : d(d), s(s), pos(pos) {}
};

bool operator< (Data a, Data b) {
    if (a.d == b.d) return a.s > b.s;
    return a.d < b.d;
}

int n;
string s;
vector<Data> a, b;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    int e = 0;
    FOR(i,1,n) {
        cin >> s;
        int deep = 0, sum = 0;
        FOR(j,0,SZ(s)-1) {
            if (s[j] == '(') sum++;
            else sum--;
            deep = min(deep, sum);
        }
        if (sum >= 0) a.push_back(Data(-deep, sum, i));
        else b.push_back(Data(sum-deep, -sum, i));
        e += sum;
    }
    if (e) {
        cout << "NO";
        return 0;
    }
    sort(ALL(a));
    int sum = 0;
    for (Data x : a) {
        if (abs(x.d) > sum) {
            cout << "NO";
            return 0;
        }
        sum += x.s;
    }
    sort(ALL(b));
    sum = 0;
    for (Data x : b) {
        if (abs(x.d) > sum) {
            cout << "NO";
            return 0;
        }
        sum += x.s;
    }
    cout << "YES\n";
    for (Data x : a) cout << x.pos << ' ';
    reverse(ALL(b));
    for (Data x : b) cout << x.pos << ' ';
    return 0;
}
