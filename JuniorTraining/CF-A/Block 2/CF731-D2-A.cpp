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
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORE(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
 
using namespace std;
 
typedef pair<int, int> II;
typedef vector<II> vi;
 
string s;
int res;
 
int main()
{
    ios::sync_with_stdio(0);
    //freopen("inp.txt", "r", stdin);
    cin >> s;
    char now = 'a';
    res = 0;
    FOR(i,0,s.length()-1) {
        if (s[i] >= now) res += min(s[i]-now, now-'a'+1+'z'-s[i]);
        else res += min(now-s[i], s[i]-'a'+1+'z'-now);
        now = s[i];
    }
    cout << res;
    return 0;
}