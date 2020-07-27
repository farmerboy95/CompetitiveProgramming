/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Use interval tree.
        - For query 1 and 3, we just do like typical interval tree problem.
        - For query 2, we find the largest value k of the segment (k >= x), replace it with k % x, and
        do it again until we don't find any largest value k >= x in the segment anymore.
        - The reason which allows us to do the above thing is that, let's consider a number k,
        for a modulo m (m <= k), k % m < k, clearly. But we can easily see that the largest k % m
        would be around k / 2. So each number will be reduced maximum logk times.
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
typedef pair<ll, int> II;
typedef pair<II, int> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;

const ll MODBASE = 1000000007LL;
const int MAXN = 100010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, m, a[MAXN];
ll t[MAXN*4];
int p[MAXN*4];
 
void build(int k, int l, int r)
{
    if (l > r) return;
    if (l == r) {
        t[k] = a[l];
        p[k] = l;
        return;
    }
    int m = (l+r) >> 1;
    build(k*2,l,m);
    build(k*2+1,m+1,r);
    t[k] = t[k*2] + t[k*2+1];
    if (a[p[k*2]] > a[p[k*2+1]]) p[k] = p[k*2];
    else p[k] = p[k*2+1];
}
 
void update(int k, int l, int r, int u, int gt)
{
    if (l > r || r < u || u < l) return;
    if (l == r) {
        t[k] = gt;
        p[k] = l;
        return;
    }
    int m = (l+r) >> 1;
    update(k*2,l,m,u,gt);
    update(k*2+1,m+1,r,u,gt);
    t[k] = t[k*2] + t[k*2+1];
    if (a[p[k*2]] > a[p[k*2+1]]) p[k] = p[k*2];
    else p[k] = p[k*2+1];
}
 
ll get(int k, int l, int r, int u, int v)
{
    if (l > r || r < u || v < l) return 0;
    if (u <= l && r <= v) return t[k];
    int m = (l+r) >> 1;
    return get(k*2,l,m,u,v) + get(k*2+1,m+1,r,u,v);
}
 
int getIDmax(int k, int l, int r, int u, int v)
{
    if (l > r || r < u || v < l) return -1;
    if (u <= l && r <= v) return p[k];
    int m = (l+r) >> 1;
    int g = getIDmax(k*2,l,m,u,v);
    int h = getIDmax(k*2+1,m+1,r,u,v);
    if (g == -1) return h;
    if (h == -1) return g;
    if (a[g] > a[h]) return g;
    return h;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> m;
    FOR(i,1,n) cin >> a[i];
    build(1,1,n);
    while (m--) {
        int ch, u, v, x;
        cin >> ch;
        if (ch == 1) {
            cin >> u >> v;
            cout << get(1,1,n,u,v) << "\n";
        }
        else if (ch == 2) {
            cin >> u >> v >> x;
            while (1) {
                int h = getIDmax(1,1,n,u,v);
                if (a[h] >= x) {
                    a[h] %= x;
                    update(1,1,n,h,a[h]);
                }
                else break;
            }
        }
        else {
            cin >> u >> x;
            a[u] = x;
            update(1,1,n,u,x);
        }
    }
    return 0;
}
