/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
*/

#include <bits/stdc++.h>
#define base 1000000007LL
#define md int(1e7+100)
#define modul int(1e9+7)
#define ll long long
#define X first
#define Y second
#define mp make_pair
#define pb push_back
#define EL printf("\n")
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)

using namespace std;

typedef pair<int, int> II;
typedef vector<II> vi;

int n, m;
bool co;

int main()
{
    ios::sync_with_stdio(0);
    //freopen("inp.txt", "r", stdin);
    cin >> n >> m;
    while (1) {
        n++;
        co = true;
        FOR(i,2,int(sqrt(n)))
            if (n % i == 0) {
                co = false;
                break;
            }
        if (co) break;
    }
    if (n == m) cout << "YES";
    else cout << "NO";
    return 0;
}