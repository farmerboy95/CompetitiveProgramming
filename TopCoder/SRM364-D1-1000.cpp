/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - The last person can always choose his favorite gift. So that the second last person can choose 
        the gift that would not be chosen by the last person and has minimum unhappiness number.
        - So that we can easily get the last status of gifts after all swaps.
        - Then I realized that one never trade with a person who has the turn after him, 
        because that person can do swapping afterwards.
        - First status and last status turn out to form a graph (a group of swapping), for each person i, 
        I can use that graph to find a person j (j <= i) who I should trade gift.
*/

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
typedef pair<int, int> II;
typedef pair<II, int> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;

void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
    cout << *it << " = " << a << endl;
    err(++it, args...);
}

const ll MODBASE = 1000000007LL;
const int MAXN = 2010;
const int MAXM = 200010;
const int MAXK = 110;
const int MAXQ = 200010;

class YankeeSwap {
    public:
    string s, t;

    // get last status after all swaps, simply choose the most favorite gift that has not been chosen by the next one.
    string getLastStat(int n, vector<string> &preferences) {
        string s;
        s.resize(n);
        bool tmpUsed[26];
        FOR(i,0,n-1) tmpUsed[i] = false;
        FORE(i,n-1,0)
            FOR(j,0,SZ(preferences[i])-1) {
                char ch = preferences[i][j];
                if (!tmpUsed[ch-'A']) {
                    tmpUsed[ch - 'A'] = true;
                    s[i] = ch;
                    break;
                }
            }
        return s;
    }

    int findLower(int u) {
        int v = t[u] - 'A';
        while (v > u) v = t[v] - 'A';
        return v;
    }

    string sequenceOfSwaps(vector<string> preferences) {
        int n = SZ(preferences);
        s.clear();
        t.clear();
        s.resize(n);
        FOR(i,0,n-1) s[i] = char(i + 'A');
        t = getLastStat(n, preferences);
        string res = "";

        // find the partner to trade for each person
        FOR(i,0,n-1) {
            int v = findLower(s[i] - 'A');
            if (v == i) {
                res += "-";
                continue;
            }
            FOR(j,0,i)
                if (s[j] - 'A' == v) {
                    swap(s[j], s[i]);
                    res = res + char(j + 'a');
                    break;
                }
        }
        return res;
    }
};

void topcoder() {
    YankeeSwap a;
    cout << a.sequenceOfSwaps({"BAC","ACB","BCA"}) << endl;
    cout << a.sequenceOfSwaps({"ABC","BCA","CAB"}) << endl;
    cout << a.sequenceOfSwaps({"AECDBF","BAEDCF","DEBACF","BEDCAF","CEABDF","CBDEAF"}) << endl;
    cout << a.sequenceOfSwaps({"FDBHMAIELGKNJC","KGMDJBAFLECNHI","FKLJCADBEHNGIM","JMHNICABFKEGDL","IKFCDNJBLEGAMH","FDNLJGCKHMBIEA","MBKJAHDNIGECLF","KNADLFGBJIMHCE","AIFMGEBDHKJNCL","MCDALIJGNKBFHE","AJHMDLEIFKNCGB","IJLKBCMDGNHFEA","EAKFLJBDGMHCIN","JEMANBDFGICHKL"}) << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    topcoder();
    return 0;
}
