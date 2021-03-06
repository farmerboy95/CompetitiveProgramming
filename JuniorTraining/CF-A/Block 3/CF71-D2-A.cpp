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
 
int n, m;
string s;
 
int main()
{
    ios::sync_with_stdio(0);
    //freopen("inp.txt", "r", stdin);
    cin >> n;
    FOR(i,1,n) {
        cin >> s;
        if (s.length() > 10) {
            m = s.length()-2;
            cout << s[0] << m << s[s.length()-1] << endl;
        }
        else cout << s << endl;
    }
    return 0;
}