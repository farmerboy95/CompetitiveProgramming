#include <bits/stdc++.h>
#define FI first
#define SE second
#define EPS 1e-9
#define ALL(a) a.begin(),a.end()
#define SZ(a) int((a).size())
#define MS(s, n) memset(s, n, sizeof(s))
#define FOR(i,a,b) for (int i = (a); i <= (b); i++)
#define FORE(i,a,b) for (int i = (a); i >= (b); i--)
#define FORALL(it, a) for (__typeof((a).begin()) it = (a).begin(); it != (a).end(); it++)
#define WHATIS(x) cout << #x << " is " << x << endl;
#define ERROR(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
//__builtin_ffs(x) return 1 + index of least significant 1-bit of x
//__builtin_clz(x) return number of leading zeros of x
//__builtin_ctz(x) return number of trailing zeros of x

using namespace std;
using ll = long long;
using ld = double;
typedef pair<ll, ll> II;
typedef pair<II, ll> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;

void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
    cout << *it << " = " << a << endl;
    err(++it, args...);
}

const ll MODBASE = 1000000007LL;
const int MAXN = 110;
const int MAXM = 35;
const int MAXK = 510;
const int MAXQ = 200010;

class AddPeriodic {
    public:
    ll gcd(ll a, ll b) {
        if (b == 0) return a;
        return gcd(b, a % b);
    }

    II fromPeriodicToFraction(string s) {
        int vt = -1;
        ll ng = 0;
        FOR(i,0,SZ(s)-1)
            if (s[i] == '.') {
                vt = i;
                break;
            }
            else ng = ng * 10 + s[i] - '0';
        if (vt == -1) return II(ng, 1);

        II bt = II(0,1);
        int vtt = -1;
        FOR(i,vt+1,SZ(s)-1)
            if (s[i] != '(') {
                bt.FI = bt.FI * 10 + s[i]-'0';
                bt.SE *= 10;
            }
            else {
                vtt = i;
                break;
            }
        ll mau = bt.SE;
        ng = ng * bt.SE;
        bt.FI += ng;
        ll g = gcd(bt.FI, bt.SE);
        bt.FI /= g;
        bt.SE /= g;
        if (vtt == -1) return bt;

        II r = II(0, mau);
        ll k = 1;
        FOR(i,vtt+1,SZ(s)-2) {
            if (s[i] == ')') break;
            r.FI = r.FI * 10 + s[i]-'0';
            r.SE *= 10;
            k *= 10;
        }
        if (k > 1) {
            r.SE /= k;
            r.SE *= (k-1);
            g = gcd(r.FI, r.SE);
            r.FI /= g;
            r.SE /= g;
        }

        bt.FI = bt.FI * r.SE + bt.SE * r.FI;
        bt.SE *= r.SE;
        g = gcd(bt.FI, bt.SE);
        bt.FI /= g;
        bt.SE /= g;
        return bt;
    }

    string fromFractionToPeriodic(II n) {
        ll g = n.FI;
        ll h = n.SE;
        //cout << g << ' ' << h << endl;
        string res;
        map <ll, ll> mp; 
        mp.clear(); 
  
        ll rem = g % h;
        ll ng = g / h;
        while (rem != 0 && (mp.find(rem) == mp.end())) { 
            mp[rem] = SZ(res);
            rem = rem * 10; 
    
            ll resPart = rem / h; 
            res += to_string(resPart); 
    
            rem = rem % h; 
        } 
        string strNG = to_string(ng);
        res = strNG + "." + res;
        //cout << res << endl;
    
        return (rem == 0) ? res + "(0)" : res.substr(0, mp[rem] + SZ(strNG) + 1) + "(" + res.substr(mp[rem] + SZ(strNG) + 1) + ")"; 
    }

    string add(string A, string B) {
        II a = fromPeriodicToFraction(A);
        II b = fromPeriodicToFraction(B);

        II res = II(a.FI * b.SE + a.SE * b.FI, a.SE * b.SE);
        ll g = gcd(res.FI, res.SE);

        res.FI /= g;
        res.SE /= g;

        return fromFractionToPeriodic(res);
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    AddPeriodic ap;
    cout << ap.add("0.33(333)", "0.(66)") << endl;
    cout << ap.add("2.41(5)", "5.36(22)") << endl;
    cout << ap.add("685.4(757)", "45.356(43)") << endl;
    cout << ap.add("0.(101)", "0.(23)") << endl;
    cout << ap.add("0.0(999999)", "1.5(00000)") << endl;
    return 0;
}