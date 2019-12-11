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

int main()
{
    int n, t;
    ios::sync_with_stdio(0);
    //freopen("inp.txt", "r", stdin);
    cin >> n >> t;
    if (t == 10) {
        if (n == 1) cout << -1;
        else {
            cout << 1;
            FOR(i,1,n-1) cout << 0;
        }
    }
    else {
        cout << t;
        FOR(i,1,n-1) cout << 0;
    }
    return 0;
}