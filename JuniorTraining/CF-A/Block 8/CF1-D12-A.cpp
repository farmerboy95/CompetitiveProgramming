/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
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

ll n, m, a, p, q;

int main()
{
    ios::sync_with_stdio(0);
    //freopen("inp.txt", "r", stdin);
    cin >> n >> m >> a;
    if (n % a == 0) p = n / a;
    else p = n/a+1;
    if (m % a == 0) q = m / a;
    else q = m/a+1;
    cout << p*q;
    return 0;
}