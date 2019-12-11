/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
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
 
int n, m;
char k;
 
int main()
{
    ios::sync_with_stdio(0);
    //freopen("inp.txt", "r", stdin);
    cin >> n >> m;
    bool co = true;
    FOR(i,1,n)
        FOR(j,1,m) {
            cin >> k;
            if (k == 'C' || k == 'M' || k == 'Y') co = false;
        }
    if (co) cout << "#Black&White";
    else cout << "#Color";
    return 0;
}