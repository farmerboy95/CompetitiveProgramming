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
#define modul int(1e9+7)
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORE(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
 
using namespace std;
 
typedef pair<int, int> II;
typedef vector<II> vi;
typedef long long ll;
 
int n, a[110], s1, s, cnt;
 
int main()
{
    ios::sync_with_stdio(0);
    //freopen("inp.txt", "r", stdin);
    cin >> n;
    FOR(i,1,n) {
        cin >> a[i];
        s += a[i];
    }
    sort(a+1, a+n+1);
    FORE(i,n,1) {
        s1 += a[i];
        s -= a[i];
        cnt++;
        if (s1 > s) {
            cout << cnt;
            return 0;
        }
    }
    return 0;
}