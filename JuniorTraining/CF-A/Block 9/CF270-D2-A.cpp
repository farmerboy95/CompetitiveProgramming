/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: 180 * (n-2) / n = a => n = 360 / (180 - a)
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

int main()
{
    ios::sync_with_stdio(0);
    //freopen("inp.txt", "r", stdin);
    int t, a;
    cin >> t;
    while (t--) {
        cin >> a;
        a = 180-a;
        if (360 % a == 0) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}