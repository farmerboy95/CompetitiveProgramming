/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - There are at most O(nm) rounds
        - At each round, we have to check if a dancer satisfies the condition and he / she would stay
        in the competition. It may take O(nm) more. But at each round, if the number of neighbors of
        a dancer who still stays in the competition does not change, the dancer would still stay. So
        we would check the dancers who have the number of neighbors changing after each round only.
        - To get the neighbors quickly, we maintain something like a linked list, after removing a dancer
        get the immediate left, right, up, down dancers of him / her and remove the dancer from the linked
        list. Simutaneously, we update the linked list to go to the next round. O(nm) overall
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
const int MAXN = 110;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int dx[4] = {-1,0,0,1};
int dy[4] = {0,-1,1,0};

int n, m;
vector<vector<int> > a;
vector<vector<bool> > avail;
vector<vector<II> > A[4];
vector<II> elim, change;

bool isInside(int u, int v) {
    return u > 0 && u <= n && v > 0 && v <= m;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int t;
    cin >> t;
    FOR(o,1,t) {
        cout << "Case #" << o << ": ";
        cin >> n >> m;

        a.clear();
        FOR(j,0,3) A[j].clear();
        avail.clear();

        FOR(i,0,n+1) {
            vector<int> b(m+2, -1);
            vector<bool> av(m+2, false);
            a.push_back(b);
            avail.push_back(av);
            FOR(j,0,3) {
                vector<II> c(m+2);
                A[j].push_back(c);
            }
        }
        
        FOR(i,1,n) FOR(j,1,m) {
            cin >> a[i][j];
            avail[i][j] = true;
        }

        FOR(i,0,n+1) FOR(j,0,m+1) {
            FOR(k,0,3) {
                int u = i + dx[k], v = j + dy[k];
                A[k][i][j] = II(u, v);
            }
        }

        ll res = 0, interest = 0;

        change.clear();
        FOR(i,1,n) FOR(j,1,m) {
            interest += a[i][j];
            change.push_back(II(i, j));
        }

        while (1) {
            res += interest;
            elim.clear();

            for (auto x : change) {
                int cnt = 0, sum = 0;
                int i = x.FI, j = x.SE;
                if (!avail[i][j]) continue;
                FOR(k,0,3) {
                    II r = A[k][i][j];
                    if (isInside(r.FI, r.SE)) {
                        cnt++;
                        sum += a[r.FI][r.SE];
                    }
                }
                if (a[i][j] * cnt < sum) {
                    elim.push_back(II(i, j));
                    avail[i][j] = false;
                }
            }

            if (SZ(elim) == 0) break;
            change.clear();
            for (auto r : elim) {
                interest -= a[r.FI][r.SE];
                II up = A[0][r.FI][r.SE], down = A[3][r.FI][r.SE];
                A[3][up.FI][up.SE] = down;
                A[0][down.FI][down.SE] = up;

                II lef = A[1][r.FI][r.SE], rig = A[2][r.FI][r.SE];
                A[2][lef.FI][lef.SE] = rig;
                A[1][rig.FI][rig.SE] = lef;

                if (avail[up.FI][up.SE]) change.push_back(up);
                if (avail[down.FI][down.SE]) change.push_back(down);
                if (avail[lef.FI][lef.SE]) change.push_back(lef);
                if (avail[rig.FI][rig.SE]) change.push_back(rig);
            }

        }

        cout << res << "\n";
    }
    return 0;
}
