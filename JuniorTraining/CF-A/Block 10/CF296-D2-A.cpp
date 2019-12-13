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

int n, p, f[1010];

int main()
{
    ios::sync_with_stdio(0);
    //freopen("inp.txt", "r", stdin);
    cin >> n;
    int k = n/2 + (n%2);
    FOR(i,1,n) {
        cin >> p;
        f[p]++;
    }
    FOR(i,1,1000)
        if (f[i] > k) {
            cout << "NO";
            return 0;
        }
    cout << "YES";
    return 0;
}