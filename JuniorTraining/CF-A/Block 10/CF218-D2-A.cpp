/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
*/

#include <bits/stdc++.h>
#define base 1000000007LL
#define ll long long
#define X first
#define Y second
#define mp make_pair
#define pb push_back
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORE(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)

using namespace std;

typedef pair<int, int> II;
typedef vector<II> vi;

int n, k, a[210];

int main()
{
    ios::sync_with_stdio(0);
    //freopen("inp.txt", "r", stdin);
    cin >> n >> k;
    FOR(i,1,2*n+1) cin >> a[i];
    for (int i = 2; i <= 2*n+1; i+=2)
        if (a[i]-1 > a[i-1] && a[i]-1 > a[i+1] && k) {
            a[i]--;
            k--;
        }
    FOR(i,1,2*n+1) cout << a[i] << " ";
    return 0;
}