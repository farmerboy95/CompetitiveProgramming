/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: Do as problem requirement
*/

#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
#include <map>
#define md int(1e7+100)
#define la 1000000000000000LL
#define modul int(1e9+7)
#define FOR(i,a,b) for(long long i=(a),_b=(b); i<=_b; i++)
#define FORE(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
 
using namespace std;
 
typedef pair<int, int> II;
typedef vector<II> vi;
typedef long long ll;
 
ll n, a[100010], p, q;
 
int main()
{
    ios::sync_with_stdio(0);
    //freopen("inp.txt", "r", stdin);
    cin >> n;
    FOR(i,1,n) cin >> a[i];
    a[0] = -la;
    a[n+1] = la;
    FOR(i,1,n) {
        p = min(a[i+1]-a[i], a[i]-a[i-1]);
        q = max(a[n]-a[i], a[i]-a[1]);
        cout << p << " " << q << endl;
    }
    return 0;
}