/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        * C1:
        - Ask [1, n] and [2, n], sort strings in the answers and remove strings in the second answer from the first. 
        Then only one string of each length remains, and those strings are all the prefixes of our string. 
        By counting which character frequency increased from i-1th prefix to the ith, we find the ith character.
        * C2:
        - Use C1 to find the first half of the string, then query [1, n].
        - Let c[k][ch] be the total number of occurrences of character ch in substrings of length k in the last query. 
        Then the number of occurrences of character ch in the first k and last k characters of the string is 
        c[1][ch] − (c[k+1][ch] - c[k][ch]), as if the character at position i is ch, it adds min(i,n+1-i,k) to c[k][ch].
        - We know the first half of the string, now loop k from 1 to floor(n/2) and find how many times character ch occurs 
        in the first k and last k positions. We know all but one of the characters in the first k and last k positions, 
        so we can this way check if the kth last character is ch.
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
//__builtin_ffs(x) return 1 + index of least significant 1-bit of x
//__builtin_clz(x) return number of leading zeros of x
//__builtin_ctz(x) return number of trailing zeros of x
 
using namespace std;
using ll = long long;
using ld = double;
typedef pair<int, int> II;
typedef pair<II, ll> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;
 
const ll MODBASE = 1000000007LL;
const int MAXN = 110;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, tmp[26], cnt[26], c[MAXN][26];
char res[MAXN];
map<string, int> ma;

vector<string> query(int l, int r) {
    int len = r - l + 1;
    int num = len * (len+1) / 2;
    cout << "? " << l << ' ' << r << endl;
    vector<string> ret;
    FOR(i,1,num) {
        string s;
        cin >> s;
        sort(ALL(s));
        ret.emplace_back(s);
    }
    return ret;
}

void printResult() {
    cout << "! ";
    FOR(i,1,n) cout << res[i];
    cout << endl;
    exit(0);
}

bool cmp(string a, string b) {
    return SZ(a) < SZ(b);
}

void findFirstHalf() {
    int m = (n + 1) / 2;
    vector<string> a = query(1, m);
    vector<string> b = query(2, m);
    ma.clear();
    FOR(i,0,SZ(a)-1) ma[a[i]]++;
    FOR(i,0,SZ(b)-1) ma[b[i]]--;
    vector<string> c;
    FORALL(it, ma)
        FOR(i,1,it->SE) c.emplace_back(it->FI);
    sort(ALL(c), cmp);
    FOR(i,0,SZ(c)-1) {
        string w = c[i];
        FOR(j,0,SZ(w)-1) tmp[w[j]-'a']++;
        FOR(j,0,25)
            if (tmp[j] != cnt[j]) {
                res[i+1] = char(j + 'a');
                break;
            }
        FOR(j,0,25) {
            cnt[j] = tmp[j];
            tmp[j] = 0;
        }
    }
}

void calcArrayC() {
    vector<string> a = query(1, n);
    FOR(i,0,SZ(a)-1) {
        int len = SZ(a[i]);
        FOR(j,0,len-1) c[len][a[i][j] - 'a']++;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n) res[i] = ' ';
    if (n <= 3) {
        FOR(i,1,n) res[i] = query(i,i)[0][0];
        printResult();
    }
    findFirstHalf();
    calcArrayC();

    FOR(k,1,n/2) {
        FOR(ch,0,25) {
            int dem = c[1][ch] - (c[k+1][ch] - c[k][ch]);
            FOR(i,1,k)
                if (res[i] - 'a' == ch) dem--;
            FORE(i,n,n-k+2)
                if (res[i] - 'a' == ch) dem--;
            if (dem) {
                res[n-k+1] = char(ch + 'a');
                break;
            }
        }
    }
    printResult();
    return 0;
}
