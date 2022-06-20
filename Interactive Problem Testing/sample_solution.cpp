// problem link: https://www.codechef.com/LTIME109A/problems/XORDETECTIVE

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e9+7;
const ll MOD = 998244353;
typedef pair<ll,ll> Ii;
#define iii pair<ll,ii>
#define ull unsigned ll
#define f(i,a,b) for(ll i = a;i < b;i++)
#define pb push_back
#define vll vector<ll>
#define F first
#define S second
#define all(x) (x).begin(), (x).end()
ll ask(ll x){
    cout<<"? "<<x<<endl;
    cin>>x;
    return x;
}
int main(void){
    ll t;
    cin>>t;
    while(t--){
        ll q;
        cin>>q;
        ll sum = ask(0);
        ll A = 0,B = 0;
        ll f;
        for(ll j = 29;j >= 0;j--){
            if(sum & (1LL<<j)){
                f = j;
                B += (1LL<<j);
                break;
            }
        }
        ll num = 0;
        ll last = 0;
        f(j,f+1,30){
            ll x = ask((1LL<<f) + num);
            x = (x>>j);
            if(x == 1){
                num += (1LL<<j);
            }
            else{
                A += (1LL<<j);
                B += (1LL<<j);
            }
        }
        ll pos = f;
        for(ll j = f-1;j >= 0;j--){
            if(sum & (1LL<<j)){
                ll x = ask(num + (1LL<<j));
                bool ok = 0;
                f(u,pos+1,30){
                    if((x & (1LL<<u)) != (sum & (1LL<<u))){
                        ok = 1;
                        break;
                    }
                }
                if(!ok){
                    last ^= 1;
                }
                A += last * (1LL<<j);
                B += (last ^ 1) * (1LL<<j);
                pos = j;
            }
            else{
                ll x = ask(num + (1LL<<j));
                if(x == sum){
                    num += (1LL<<j);
                }
                else{
                    A += (1LL<<j);
                    B += (1LL<<j);
                }
            }
        }
        cout<<"! "<<A<<" "<<B<<endl;
    }
}
