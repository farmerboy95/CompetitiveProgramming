/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
*/

#include <bits/stdc++.h>
#define base 1000000000000007LL
#define ll long long
#define X first
#define Y second
#define mp make_pair
#define pb push_back
#define FOR(i,a,b) for(ll i=(a),_b=(b); i<=_b; i++)
#define FORE(i,a,b) for(ll i=(a),_b=(b); i>=_b; i--)

using namespace std;

typedef pair<int, int> II;
typedef vector<II> vi;

ll n, a[200010], b[200010];
string s;

int main()
{
    ios::sync_with_stdio(0);
    //freopen("inp.txt", "r", stdin);
    cin >> n;
    cin >> s;
    s = " " + s;
    FOR(i,1,n) cin >> a[i];
    FOR(i,1,n)
        if (s[i] == 'L') b[i] = 1;
    ll res = base;
    FOR(i,1,n) {
        if (i > 1) {
            if (b[i] && !b[i-1]) res = min(res, a[i]-a[i-1]);
        }
        if (i < n) {
            if (!b[i] && b[i+1]) res = min(res, a[i+1]-a[i]);
        }
    }
    if (res == base) cout << -1;
    else cout << res/2;
    return 0;
}