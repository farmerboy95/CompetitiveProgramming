/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
*/

#include <cstdio>
#include <bits/stdc++.h>
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
#define FOR(i,a,b) for(long long i=(a),_b=(b); i<=_b; i++)
#define FORE(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)

using namespace std;

typedef pair<int, int> II;
typedef vector<II> vi;
typedef long long ll;

ll ucln(ll y, ll x);

ll l, r;

int main()
{
    ios::sync_with_stdio(0);
    //freopen("inp.txt", "r", stdin);
    cin >> l >> r;
    FOR(i,l,r)
        FOR(j,i+1,r)
            FOR(k,j+1,r)
                if (ucln(i,j) == 1 && ucln(j,k) == 1 && ucln(i,k) != 1) {
                    cout << i << " " << j << " " << k;
                    return 0;
                }
    cout << -1;
    return 0;
}

ll ucln(ll y, ll x)
{
    ll t = y % x;
    while (t != 0) {
        t = x % y;
        x = y;
        y = t;
    }
    return x;
}