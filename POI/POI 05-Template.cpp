/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/POI/official/2005/editrial/sza.pdf
        - We have some following observations:
            + The template string must be suffix and prefix of the initial string (we can call it prefix-suffix string)
            + The lengths of template strings can be produce by linear-time algorithm KMP 
            (b[i] = length of the longest prefix-suffix string of string s[0..i], b[i] < i+1)
            + For each string in the candidate set S, we can use KMP to find appearance of it in the initial string,
            and check if the appearances can produce the initial string again or not.
            + Let y1, y2, ..., yk be elements of the set S listed in this order, that |y1| > |y2| > ... > |yk|. 
            Then, if for some 1 <= i < k there is an inequality |yi| / 2 <= |y(i+1)|, yi is not the shortest template
            => We can start from the shortest candidate yi, if the candidate is not the result, we move to the nearest candidate yj
            that |yj| > |yi| * 2, because if there exists an yk between yi and yj and yk is the result, then yi is also a result and
            it's shorter that yk
            => Complexity O(nlogn)
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
typedef pair<ll, ll> II;
typedef pair<int, II> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;
 
const ll MODBASE = 1000000007LL;
const int MAXN = 500010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

string s;
int b[MAXN];
vector<int> a;

void kmpPreprocess() {
    b[0] = 0;
    FOR(i,1,SZ(s)-1) {
        int k = b[i-1];
        while (k > 0 && s[k] != s[i]) k = b[k-1];
        if (s[k] == s[i]) b[i] = k+1;
        else k = 0;
    }
}

bool kmpSearch(int m) {
    int j = 0;
    int now = 0;
    FOR(i,0,SZ(s)-1) {
        while (j > 0 && s[i] != s[j]) j = b[j-1];
        if (s[i] == s[j]) j++;
        else j = 0;
        if (j == m) {
            int pos = i-m+1;
            if (pos > now+1) return false;
            now = max(now, pos + m - 1);
            j = b[j-1];
        }
    }
    return now == SZ(s)-1;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> s;
    kmpPreprocess();
    int now = SZ(s);
    while (now) {
        a.emplace_back(now);
        now--;
        now = b[now];
    }
    now = SZ(a)-1;
    while (now >= 0) {
        if (kmpSearch(a[now])) {
            cout << a[now];
            return 0;
        }
        int k = a[now];
        now--;
        while (now >= 0) {
            if (a[now] > k * 2) break;
            now--;
        }
    }
    return 0;
}
