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
#define FOR(i,a,b) for(long long i=(a),_b=(b); i<=_b; i++)
#define FORE(i,a,b) for(long long i=(a),_b=(b); i>=_b; i--)

using namespace std;

typedef pair<int, int> II;
typedef vector<II> vi;
typedef long long ll;

void init(void);
ll getHashS(ll i, ll j);
ll getHashT(ll i, ll j);
bool check(ll l1, ll r1, ll l2, ll r2);

string s, t;
ll mod, Pow[200010], hashS[200010], hashT[200010], n;

int main()
{
    ios::sync_with_stdio(0);
    //freopen("inp.txt", "r", stdin);
    cin >> s;
    cin >> t;
    mod = 1000000007;
    init();
    if (n % 2) {
        if (getHashS(1,n) == getHashT(1,n)) cout << "YES";
        else cout << "NO";
        return 0;
    }
    if (getHashS(1,n) == getHashT(1,n)) {
        cout << "YES";
        return 0;
    }
    if (check(1,n/2,1,n/2) && check(n/2+1,n,n/2+1,n)) cout << "YES";
    else if (check(1,n/2,n/2+1,n) && check(n/2+1,n,1,n/2)) cout << "YES";
    else cout << "NO";
    return 0;
}

bool check(ll l1, ll r1, ll l2, ll r2)
{
    if ((r1 - l1 + 1) % 2) {
        if (getHashS(l1,r1) == getHashT(l2,r2)) return true;
        return false;
    }
    ll p = (l1+r1)>>1;
    ll q = (l2+r2)>>1;
    if (getHashS(l1,r1) == getHashT(l2,r2)) return true;
    else if (check(l1,p,q+1,r2) && check(p+1,r1,l2,q)) return true;
    else if (check(l1,p,l2,q) && check(p+1,r1,q+1,r2)) return true;
    return false;
}

void init(void)
{
    n = s.length();
    s = " " + s;
    t = " " + t;
    Pow[0] = 1;
    FOR(i,1,200000) Pow[i] = (Pow[i-1] * 26) % mod;
    FOR(i,1,n) {
        hashS[i] = (hashS[i-1] * 26 + s[i] - 'a') % mod;
        hashT[i] = (hashT[i-1] * 26 + t[i] - 'a') % mod;
    }
}

ll getHashS(ll i, ll j)
{
    return (hashS[j]-hashS[i-1]*Pow[j-i+1]+mod*mod)%mod;
}

ll getHashT(ll i, ll j)
{
    return (hashT[j]-hashT[i-1]*Pow[j-i+1]+mod*mod)%mod;
}