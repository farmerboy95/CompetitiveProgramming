/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: Change both strings to lowercase then compare as normal
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
 
string s, t;
 
int main()
{
    ios::sync_with_stdio(0);
    //freopen("inp.txt", "r", stdin);
    cin >> s;
    cin >> t;
    FOR(i,0,s.length()-1)
        if (s[i] >= 'A' && s[i] <= 'Z') s[i] += 32;
    FOR(i,0,t.length()-1)
        if (t[i] >= 'A' && t[i] <= 'Z') t[i] += 32;
    if (s == t) cout << 0;
    else if (s > t) cout << 1;
    else cout << -1;
    return 0;
}