/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - For each number x of splitters, we can get a number of pipes in a specific segment.
        - Binary search x and print result.
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

bool check(ll u, ll k, ll n)
{
    ll p = k*(k+1)/2 - (k-u)*(k-u+1)/2;
    return p+1 >= n;
}

int main()
{
    ios::sync_with_stdio(0);
    //freopen("inp.txt", "r", stdin);
    ll n, k;
    cin >> n >> k;
    if (n == 1) cout << 0;
    else if (n <= k) cout << 1;
    else if (k*(k+1)/2 - (k-1) < n) cout << -1;
    else {
        k--;
        ll dau = 1;
        ll cuoi = k;
        while (dau <= cuoi) {
            ll mid = (dau + cuoi) >> 1;
            if (check(mid, k, n)) cuoi = mid-1;
            else dau = mid+1;
        }
        if (n >= dau*(dau+1)/2) cout << dau;
        else cout << -1;
    }
    return 0;
}