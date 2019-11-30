/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: 
        - Let f[i] = 1 if we meet '(' at i, f[i] = -1 if we meet ')' at i, f[i] = 0 for remaining cases
        - Condition of correct bracket sequence are:
            1. sum(f[1 -> n]) = 0
            2. There is no sum(f[1 -> i]) < 0
        - This leads us to the following solution:
            + Create a segment tree which stores Max and Min of z[i] = sum(f[1 -> i]) (l <= i <= r)
            + If we need to replace a normal character with ')' we increase z from current pos to n by 1
            + If we need to replace a normal character with '(' we increase z from current pos to n by 1
            + If we need to replace '(' with a normal character we decrease z from current pos to n by 1
            + If we need to replace ')' with a normal character we decrease z from current pos to n by 1
            + If we need to replace '(' with ')' we decrease z from current pos to n by 2
            + If we need to replace ')' with '(' we increase z from current pos to n by 2
            + The sum can be calculated separately
            + Get (Max, Min) of (1, n) sequence, if Min < 0 => -1, otherwise, print Max
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
const int MAXN = 1000010;
const int MAXM = 30010;
const int MAXK = 16;
const int MAXQ = 200010;

struct Node {
    int Max, Min;
    Node(int Max = 0, int Min = 0) : Max(Max), Min(Min) {}
};

int n, laz[MAXN * 8], sum;
string s;
Node tr[MAXN * 8];
char t[MAXN];

void lazyUpd(int k, int l, int r) {
    if (l > r) return;
    if (laz[k] == 0) return;
    tr[k].Max += laz[k];
    tr[k].Min += laz[k];
    if (l < r) {
        laz[k * 2] += laz[k];
        laz[k * 2 + 1] += laz[k];
    }
    laz[k] = 0;
}

void update(int k, int l, int r, int u, int gt) {
    lazyUpd(k, l, r);
    if (r < u || l > r) return;
    if (u <= l) {
        laz[k] += gt;
        lazyUpd(k, l, r);
        return;
    }
    int m = (l + r) >> 1;
    update(k * 2, l, m, u, gt);
    update(k * 2 + 1, m+1, r, u, gt);
    tr[k].Min = min(tr[k*2].Min, tr[k*2+1].Min);
    tr[k].Max = max(tr[k*2].Max, tr[k*2+1].Max);
}

Node get() {
    return tr[1];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    cin >> s;
    int now = 1;
    sum = 0;
    FOR(i,1,1000000) t[i] = ' ';
    FOR(i,0,SZ(s)-1) {
        if (s[i] == 'L') {
            now--;
            if (now == 0) now = 1;
        }
        else if (s[i] == 'R') {
            now++;
        }
        else if (s[i] == '(') {
            if (t[now] == ')') {
                update(1,1,n,now,2);
                sum += 2;
            }
            else if (t[now] == '(') {
                
            }
            else {
                update(1,1,n,now,1);
                sum += 1;
            }
            t[now] = s[i];
        }
        else if (s[i] == ')') {
            if (t[now] == ')') {

            }
            else if (t[now] == '(') {
                update(1,1,n,now,-2);
                sum -= 2;
            }
            else {
                update(1,1,n,now,-1);
                sum -= 1;
            }
            t[now] = s[i];
        }
        else {
            if (t[now] == ')') {
                update(1,1,n,now,1);
                sum += 1;
            }
            else if (t[now] == '(') {
                update(1,1,n,now,-1);
                sum -= 1;
            }
            else {
                
            }
            t[now] = s[i];
        }
        Node p = get();
        if (p.Min == 0 && sum == 0) cout << p.Max << ' ';
        else cout << "-1 ";
    }
    return 0;
}