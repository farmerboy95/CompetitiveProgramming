/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea: Simply (a^b) % 10
*/

#include <bits/stdc++.h>
#define FOR(i,a,b) for (int i = (a); i <= (b); i++)

using namespace std;
using ll = long long;

ll binPowMod(ll a, ll b, ll m) {
    a %= m;
    ll res = 1;
    while (b > 0) {
        if (b & 1LL) res = res * a % m;
        a = a * a % m;
        b >>= 1LL;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int a, b;
        cin >> a >> b;
        cout << binPowMod(a, b, 10) << "\n";
    }
    return 0;
}
