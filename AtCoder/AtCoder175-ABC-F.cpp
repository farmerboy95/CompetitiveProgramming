/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - We will be constructing left and right half of our palindrome in parallel.
        - We can store current state as two strings a=S(i1)S(i2)...S(ik) and b=S(jl)(Sjl-1)...S(j1) 
        for some indices i1,i2,...,ik and j1,j2...jl. To have any chances of constructing a palindrome 
        we need to have strings a, b such that min(|a|,|b|) first characters of a exactly match last 
        characters of b. Moreover if they do we only care about characters left after we remove 
        matching prefix of a and suffix of b. The characters left will be on one side only
        - Now we can just run Dijkstra algorithm, where state is:
            + The side where the characters are on (left: 0, right: 1)
            + Index of the string which the characters belong to (from 1 to n)
            + Position j of one end of the string left (if it's left side, our string would be s[j...m],
            otherwise, our string would be s[1...j])
        - The number of state would be 2 * N * max(|Si|)
        - First we try to put one string on one side and put the state into heap, then run Dijkstra
        normally. When we get one state out of the heap, check to see the string left can be a palindrome,
        we can update the result right at that moment. The same thing should be done when choosing the
        next string to add to the opposite side, to make sure that we don't have invalid state in the
        next steps.
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
const int MAXN = 55;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

struct Node {
    ll minCost;
    int dir, idx, j;
    Node(ll minCost = 0, int dir = 0, int idx = 0, int j = 0) : minCost(minCost), dir(dir), idx(idx), j(j) {}
    bool friend operator< (Node a, Node b) {
        return a.minCost > b.minCost;
    }
};

int n, sz[MAXN];
ll dp[2][MAXN][MAXN], c[MAXN];
string s[MAXN];
priority_queue<Node> h;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n) {
        cin >> s[i] >> c[i];
        sz[i] = SZ(s[i]);
        s[i] = " " + s[i];
    }
    FOR(i,1,n)
        FOR(j,1,sz[i])
            FOR(k,0,1) dp[k][i][j] = 1e18;
    FOR(i,1,n) {
        dp[0][i][1] = c[i];
        h.push(Node(dp[0][i][1], 0, i, 1));
        dp[1][i][sz[i]] = c[i];
        h.push(Node(dp[1][i][sz[i]], 1, i, sz[i]));
    }
    ll res = 1e18;
    while (1) {
        while (!h.empty()) {
            Node x = h.top();
            if (x.minCost == dp[x.dir][x.idx][x.j]) break;
            h.pop();
        }
        if (h.empty()) break;
        Node x = h.top();
        h.pop();
        int l, r;
        bool co = true;
        if (x.dir == 0) {
            // left
            l = x.j; r = sz[x.idx];
        } else {
            // right
            l = 1; r = x.j;
        }
        // check if the current state is ok to be a palindrome
        while (l <= r) {
            if (s[x.idx][l] == s[x.idx][r]) {
                l++;
                r--;
                continue;
            }
            co = false;
            break;
        }
        if (co) res = min(res, x.minCost);
        FOR(i,1,n) {
            int L, R, lefIdx, rigIdx;
            if (x.dir == 0) {
                l = x.j; r = sz[x.idx];
                lefIdx = x.idx;
                L = 1; R = sz[i];
                rigIdx = i;
            }
            else {
                l = 1; r = sz[i];
                lefIdx = i;
                L = 1; R = x.j;
                rigIdx = x.idx;
            }

            while (l <= r && L <= R && s[lefIdx][l] == s[rigIdx][R]) {
                l++;
                R--;
            }
            if (l <= r && L <= R) continue;
            // update result right here when there is no characters left
            if (l > r && L > R) res = min(res, x.minCost + c[i]);
            else {
                if (l <= r) {
                    if (dp[0][lefIdx][l] > x.minCost + c[i]) {
                        dp[0][lefIdx][l] = x.minCost + c[i];
                        h.push(Node(dp[0][lefIdx][l], 0, lefIdx, l));
                    }
                } else {
                    if (dp[1][rigIdx][R] > x.minCost + c[i]) {
                        dp[1][rigIdx][R] = x.minCost + c[i];
                        h.push(Node(dp[1][rigIdx][R], 1, rigIdx, R));
                    }
                }
            }
        }

    }
    if (res == 1e18) res = -1;
    cout << res;
    return 0;
}
