/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: Do as problem requirement
*/

#include <bits/stdc++.h>
#define ll long long
#define X first
#define Y second
#define pb push_back
#define MAXN 100010
#define Scan(a) scanf("%I64d", &a)
#define CLR(a) memset(a,0,sizeof(a))
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORE(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
 
using namespace std;
 
typedef pair<int, int> II;
typedef vector<II> vi;
 
int n, k;
set<int> s;
 
int main()
{
    ios::sync_with_stdio(0);
    //freopen("inp.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    cin >> n;
    int now = n;
    FOR(i,1,n) {
        cin >> k;
        s.insert(k);
        while (s.count(now)) {
            cout << now << " ";
            s.erase(now);
            now--;
        }
        cout << endl;
    }
    return 0;
}