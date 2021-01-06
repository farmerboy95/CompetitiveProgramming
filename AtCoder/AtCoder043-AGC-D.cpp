/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let's consider a random final permutation. We can take a look at 2 adjacent values. 
        There are 2 cases here, call them x and y (x is on the left):
            + x > y: y and x come from the same sequence (1)
            + x < y: y and x can be in the same sequence or not.
        - We can broaden the condition (1) to this:
            + Given 3 numbers x, y, z continuously in a final permutation, if x > y,z, then 
            x, y, z come from the same sequence.
        - We can call such thing a block, so a block can have 1, 2 or 3 elements with the largest
        element comes first.
        - We initially have n sequences, and we can easily see that each of the 2-blocks and 3-blocks
        accounts for 1 sequence. So the number of 2-blocks and 3-blocks is at most n.
        - The blocks are arranged in a way that the first elements of blocks from left to right form
        an increasing sequence. For example: 2 5 3 1 6 4 has 3 groups 2, 5 3 1, 6 4, the first elements
        form 2 5 6 which is an increasing sequence.
        - So we can come up with the following solution. Let dp[i][j] = the number of final 
        permutations that use i numbers, with j (2-blocks+3blocks). In the implementation, I used
        a top-down solution that return dp[n][0]. We use the largest number in the i numbers as
        the first number in the group
            dp[i][j] = dp[i-1][j]                 (1-block)
                     + C(i, 1) * dp[i-2][j+1]     (2-block)
                     + C(i, 2) * 2 * dp[i-3][j+1] (3-block, here the 2 later elements can be swapped)
        - Complexity O(n^2)
*/

#include <bits/stdc++.h>
#define FI first
#define SE second
#define ALL(a) a.begin(),a.end()
#define SZ(a) int((a).size())
#define MS(s, n) memset(s, n, sizeof(s))
#define FOR(i,a,b) for (int i = (a); i <= (b); i++)
#define FORE(i,a,b) for (int i = (a); i >= (b); i--)
#define FORALL(it, a) for (__typeof((a).begin()) it = (a).begin(); it != (a).end(); it++)

using namespace std;
using ll = long long;
using ld = double;
using II = pair<int, int>;
using III = pair<II, int>;
using cd = complex<ld>;
using vcd = vector<cd>;

const ld EPS = 1e-9;
const ll MODBASE = 1000000007LL;
const int MAXN = 6010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

ll MOD;
int n;
ll dp[MAXN][MAXN / 2];

ll binPowMod(ll a, ll b) {
    a %= MOD;
    ll res = 1;
    while (b > 0) {
        if (b & 1LL) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1LL;
    }
    return res;
}

ll add(ll a, ll b) {
    return (a + b) % MOD;
}

ll sub(ll a, ll b) {
    return (a - b + MOD) % MOD;
}

ll mul(ll a, ll b) {
    return a * b % MOD;
}

ll C(int n, int k) {
    if (k < 0 || k > n) return 0;
    ll res = 1;
    FORE(i,n,n-k+1) res *= i;
    FOR(i,2,k) res /= i;
    return res % MOD;
}

ll solve(int num, int group) {
    if (num == 0) return 1;
    if (dp[num][group] != -1) return dp[num][group];
    ll res = 0;

    res = solve(num-1, group);
    if (group < n) {
        if (num >= 2) {
            res = add(res, mul(C(num-1, 1), solve(num-2, group+1)));
        }
        if (num >= 3) {
            res = add(res, mul(mul(2, C(num-1, 2)), solve(num-3, group+1)));
        }
    }

    return dp[num][group] = res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> MOD;
    MS(dp, -1);
    cout << solve(n*3, 0) << endl;
    return 0;
}

// this is brute force solution (s) to compare with my guess (s2)

// #include <bits/stdc++.h>
// #define FI first
// #define SE second
// #define ALL(a) a.begin(),a.end()
// #define SZ(a) int((a).size())
// #define MS(s, n) memset(s, n, sizeof(s))
// #define FOR(i,a,b) for (int i = (a); i <= (b); i++)
// #define FORE(i,a,b) for (int i = (a); i >= (b); i--)
// #define FORALL(it, a) for (__typeof((a).begin()) it = (a).begin(); it != (a).end(); it++)

// using namespace std;
// using ll = long long;
// using ld = double;
// using II = pair<int, int>;
// using III = pair<II, int>;
// using cd = complex<ld>;
// using vcd = vector<cd>;

// const ld EPS = 1e-9;
// const ll MODBASE = 1000000007LL;
// const int MAXN = 110;
// const int MAXM = 1000;
// const int MAXK = 16;
// const int MAXQ = 200010;

// set<int> s, s2;

// void solve(vector<int> &a, vector<int> &b, vector<int> &c) {
//     int res = 0;
//     while (SZ(a) + SZ(b) + SZ(c) > 0) {
//         int A = 1000000, B = 1000000, C = 1000000;
//         if (SZ(a)) A = a.back();
//         if (SZ(b)) B = b.back();
//         if (SZ(c)) C = c.back();
//         int chosen = min(A, min(B, C));
//         if (chosen == A) {
//             a.pop_back();
//         } else if (chosen == B) {
//             b.pop_back();
//         } else {
//             c.pop_back();
//         }
//         res = res * 10 + chosen;
//     }
//     s.insert(res);
// }

// int main() {
//     ios::sync_with_stdio(0);
//     cin.tie(nullptr);
//     int n = 3;
//     int z[n*3+1];
//     FOR(i,1,n*3) {
//         z[i] = i;
//     }
//     do {
//         vector<int> a, b, c;
//         FOR(i,1,3) a.push_back(z[i]);
//         FOR(i,4,6) b.push_back(z[i]);
//         FOR(i,7,9) c.push_back(z[i]);
//         solve(a, b, c);
//         int w = 0;
//         int co = true;
//         int groupNum = n;
//         FOR(i,1,n*3) w = w * 10 + z[i];
//         FOR(i,1,n*3) {
//             int cnt = 0;
//             FOR(j,i+1,n*3)
//                 if (z[j] < z[i]) {
//                     cnt++;
//                 } else {
//                     break;
//                 }
//             i = i + cnt;
//             if (cnt > 2) {
//                 co = false;
//             } else if (cnt == 2) {
//                 groupNum--;
//             } else if (cnt == 1) {
//                 groupNum--;
//             }
//             if (groupNum < 0) {
//                 co = false;
//             }
//         }
//         if (co) s2.insert(w);
//     } while (next_permutation(z+1, z+n*3+1));
//     cout << SZ(s) << " " << SZ(s2);
//     return 0;
// }
