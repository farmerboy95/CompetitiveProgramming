/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: Try to buy from 1 to 10 shovels, if the price modulo 10 == 0 or == r, that should be the result
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

int k, r;

int main()
{
    ios::sync_with_stdio(0);
    //freopen("inp.txt", "r", stdin);
    cin >> k >> r;
    int e = 1;
    while (1) {
        int p = k*e;
        if (p % 10 == 0 || p % 10 == r) {
            cout << e;
            return 0;
        }
        e++;
    }
    return 0;
}