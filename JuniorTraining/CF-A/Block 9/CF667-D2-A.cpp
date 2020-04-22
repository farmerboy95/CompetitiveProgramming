/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: Transform e into the amount of water and simply compare it with v
*/

#include <bits/stdc++.h>
#define base 1000000007LL
#define ll long long
#define X first
#define PI 3.14159265359
#define Y second
#define mp make_pair
#define pb push_back
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORE(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)

using namespace std;

typedef pair<int, int> II;
typedef vector<II> vi;

double d, h, v, e, u;

int main()
{
    ios::sync_with_stdio(0);
    //freopen("inp.txt", "r", stdin);
    cin >> d >> h >> v >> e;
    double thetich = (d / 2) * (d / 2) * PI * h;
    double dientich = (d / 2) * (d / 2) * PI;
    u = dientich*e;
    if (v - u <= 0) cout << "NO";
    else {
        cout << "YES\n";
        cout << fixed << setprecision(7) << thetich / (v-u);
    }
    return 0;
}