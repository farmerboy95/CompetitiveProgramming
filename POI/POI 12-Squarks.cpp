/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Sort all input numbers, let's assume that our 3 first numbers of the result are
        x, y, z. So the first number in input after sorted is x + y, second one is x + z,
        third one may be y + z, nevermind, we only care about x + y and x + z. Their sum
        is 2x + y + z. One observation here is that y + z lies in one of the first n numbers 
        in input. So that we can iterate through those numbers to get y + z. Then we can get
        x.
        - Now we have the first number in result, what do we do next? We find the list of numbers
        one by one, in ascending order. Let one result array is r. We find r[i]. Assume that we
        can find r[i], we must eliminate all r[i] + r[j] (j < i) from the list of input numbers.
        Then we find r[i+1]. So at this point what is the smallest number in the list of input
        numbers? Must be r[1] + r[i+1] as when we found each r[i], we removed all r[i] + r[j].
        So we can find the whole array r with only one initial number x, and the array is unique.
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
typedef pair<II, int> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;
 
const ll MODBASE = 1000000007LL;
const int MAXN = 100010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int n, a[MAXN];
vector<vector<int> > res;

// O(n^2)
void solve(int x) {
    multiset<int> nums;
    FOR(i,1,n*(n-1)/2) nums.insert(a[i]);
    vector<int> b = {x};
    while (SZ(nums)) {
        int nextNum = *nums.begin() - x;
        // remove all r[i] + r[j]
        FOR(i,0,SZ(b)-1) {
            auto it = nums.find(b[i] + nextNum);
            if (it == nums.end()) return;
            nums.erase(it);
        }
        b.push_back(nextNum);
    }
    res.push_back(b);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n*(n-1)/2) cin >> a[i];
    sort(a+1, a+n*(n-1)/2+1);
    int s = a[1] + a[2]; // 2x + y + z as a[1] = x + y and a[2] = y + z
    set<int> seen;
    // now choose y + z to get x
    FOR(i,1,n) {
        int x2 = s - a[i];
        if (x2 <= 0 || x2 % 2) continue;
        int x = x2 / 2;
        if (seen.count(x)) continue;
        seen.insert(x);
        solve(x);
    }
    cout << SZ(res) << "\n";
    FOR(i,0,SZ(res)-1) {
        FOR(j,0,SZ(res[i])-1) cout << res[i][j] << ' ';
        cout << "\n";
    }
    return 0;
}
