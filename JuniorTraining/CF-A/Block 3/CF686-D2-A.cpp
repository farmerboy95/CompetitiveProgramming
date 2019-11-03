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
#define mp make_pair
#define pb push_back
#define FOR(i,a,b) for(ll i=(a),_b=(b); i<=_b; i++)
#define FORE(i,a,b) for(ll i=(a),_b=(b); i>=_b; i--)

using namespace std;

typedef pair<int, int> II;
typedef vector<II> vi;

ll n, m, k, res;
char ch;

int main()
{
    ios::sync_with_stdio(0);
    //freopen("inp.txt", "r", stdin);
    cin >> n >> m;
    FOR(i,1,n) {
        cin >> ch >> k;
        if (ch == '+') m += k;
        else {
            if (m >= k) m-=k;
            else res++;
        }
    }
    cout << m << " " << res;
    return 0;
}