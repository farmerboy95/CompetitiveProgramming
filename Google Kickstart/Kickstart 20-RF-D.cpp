/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: Same as https://codingcompetitions.withgoogle.com/kickstart/round/000000000019ff48/00000000003f4dea#analysis
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
typedef pair<ld, int> II;
typedef pair<II, int> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;

const ll MODBASE = 1000000007LL;
const int MAXN = 110;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

vector<int> need;
int n, m, k;
map<vector<int>, ld> ma;

void init() {
    cin >> n >> m >> k;
    need.clear();
    ma.clear();
    FOR(i,1,k) {
        int x;
        cin >> x;
        need.push_back(x);
    }
}

// check if we can reach "need" (winning) state from "a" state
// very simple, just check if all elements of "a" is smaller or equal than that number of elements of winning state
bool isChild(vector<int> a) {
    if (SZ(a) > SZ(need)) return false;
    int ptr = SZ(need) - SZ(a);
    FOR(i,0,SZ(a)-1) {
        if (ptr == SZ(need)) return true;
        if (a[i] <= need[ptr]) ptr++;
    }
    return ptr == SZ(need);
}

ld handle(vector<int> a, int sum) {
    // a state is a sorted array without zeroes
    sort(ALL(a));
    if (!isChild(a)) return 1e18;
    if (ma.count(a)) return ma[a];
    // if we reach here and the number of dice is n, we surely reach the winning state
    if (sum == n) return 0;
    // so there are m possibilities here, to add one die into "a"
    // or to add new element 1 to "a"
    vector<II> go; // (expected number of moves to reach winning state from next state, probability to reach next state from current state)
    FOR(i,0,SZ(a)-1) {
        a[i]++;
        ld ev = handle(a, sum+1);
        go.push_back(II(ev, 1)); // prob = 1/m, we store 1
        a[i]--;
    }
    if (SZ(a) != m) {
        auto b = a;
        b.push_back(1);
        go.push_back(II(handle(b, sum+1), m - SZ(a))); // prob = (m - SZ(a)) / m
    }
    
    // let's sort the array "go" based on ev from lowest to highest
    // use the formula X = (1 + sum(p[i] * e[i])) / sum(p[i])
    // get the mininum ev from here
    sort(ALL(go));
    ld nume = 1, denom = 0;
    ld Min = 1e18;
    for (II x : go) {
        nume += x.FI * x.SE / m;
        denom += (ld) x.SE / m;
        Min = min(Min, nume / denom);
    }

    return ma[a] = Min;
}

void solve() {
    sort(ALL(need));
    // we move from nothing
    vector<int> go;
    cout << fixed << setprecision(9) << handle(go, 0) << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int te;
    cin >> te;
    FOR(o,1,te) {
        cout << "Case #" << o << ": ";
        init();
        solve();
    }
    return 0;
}
