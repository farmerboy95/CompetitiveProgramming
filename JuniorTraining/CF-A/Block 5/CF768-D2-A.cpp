/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: Do as problem requirement
*/

#include <bits/stdc++.h>
#define base 1000000007LL
#define ll long long
#define X first
#define Y second
#define pb push_back
#define MAXN 210010
#define Scan(a) scanf("%I64d", &a)
#define CLR(a) memset(a,0,sizeof(a))
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORE(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
 
using namespace std;
 
typedef pair<int, int> II;
typedef vector<II> vi;
 
int n, a[100010];
 
int main()
{
    ios::sync_with_stdio(0);
    //freopen("inp.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    cin >> n;
    FOR(i,1,n) cin >> a[i];
    sort(a+1, a+n+1);
    if (n <= 2) {
        cout << 0;
        return 0;
    }
    int vt = 0, vt2 = 0;
    FOR(i,2,n)
        if (a[i] != a[i-1]) { vt = i; break; }
    FORE(i,n-1,1)
        if (a[i] != a[i+1]) { vt2 = i; break; }
    if (vt == 0) cout << 0;
    else cout << max(0, vt2-vt+1);
    return 0;
}