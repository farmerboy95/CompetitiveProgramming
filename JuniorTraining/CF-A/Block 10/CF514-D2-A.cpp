/*
    Author: Nguyen Tan Bao
    Status:
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
#define md int(1e7+100)
#define modul int(1e9+7)
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define DOW(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)

using namespace std;

typedef pair<int, int> II;
typedef vector<II> vi;
string s;
int n;

int main()
{
    //freopen("inp.txt", "r", stdin);
    cin >> s;
    n = s.length();
    if (s[0] != '9') {
        if (s[0]-48 >= 5) cout << int(9-s[0]+48);
        else cout << int(s[0]-48);
    }
    else cout << 9;
    FOR(i,1,n-1) {
        if (s[i]-48 >= 5) cout << int(9-s[i]+48);
        else cout << int(s[i]-48);
    }
    return 0;
}