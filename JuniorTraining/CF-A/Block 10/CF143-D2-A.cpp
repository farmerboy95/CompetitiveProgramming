/*
    Author: Nguyen Tan Bao
    Status:
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
    ios::sync_with_stdio(0);
    //freopen("inp.txt", "r", stdin);
    int r1, r2, c1, c2, d1, d2;
    cin >> r1 >> r2 >> c1 >> c2 >> d1 >> d2;
    FOR(i,1,9)
        FOR(j,1,9)
            FOR(k,1,9)
                FOR(l,1,9)
                    if (i+j == r1 && k+l == r2 && c1 == i+k && c2 == j+l && d1 == i+l && d2 == k+j && i!=j && i!=k && i!=l && j!=k && j!=l && k!=l) {
                        cout << i << " " << j << endl << k << " " << l;
                        return 0;
                    }
    cout << -1;
    return 0;
}