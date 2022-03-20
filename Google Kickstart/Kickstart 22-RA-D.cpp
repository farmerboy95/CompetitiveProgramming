/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - DP digits
        - Comments in code
*/

#include <bits/stdc++.h>
#define FI first
#define SE second
#define ALL(a) a.begin(), a.end()
#define SZ(a) int((a).size())
#define MS(s, n) memset(s, n, sizeof(s))
#define FOR(i,a,b) for (int i = (a); i <= (b); i++)
#define FORE(i,a,b) for (int i = (a); i >= (b); i--)
#define FORALL(it, a) for (__typeof((a).begin()) it = (a).begin(); it != (a).end(); it++)
#define TRAV(x, a) for (auto &x : a)

using namespace std;
using ll = long long; using ld = double; 
using pi = pair<int, int>; using pl = pair<ll, ll>; using pd = pair<ld, ld>;
using cd = complex<ld>; using vcd = vector<cd>;

using vi = vector<int>; using vl = vector<ll>;
using vd = vector<ld>; using vs = vector<string>;
using vpi = vector<pi>; using vpl = vector<pl>; using vpd = vector<pd>; // vector<pair>

template<class T> using min_pq = priority_queue<T, vector<T>, greater<T> >;
template<class T> inline int ckmin(T& a, const T& val) { return val < a ? a = val, 1 : 0; }
template<class T> inline int ckmax(T& a, const T& val) { return a < val ? a = val, 1 : 0; }
template<class T> void remDup(vector<T>& v) { sort(ALL(v)); v.erase(unique(ALL(v)), end(v)); }

constexpr int pct(int x) { return __builtin_popcount(x); } // # of bits set
constexpr int bits(int x) { return x == 0 ? 0 : 31-__builtin_clz(x); } // floor(log2(x)) 
constexpr int p2(int x) { return 1<<x; }
constexpr int msk2(int x) { return p2(x)-1; }

ll ceilDiv(ll a, ll b) { return a / b + ((a ^ b) > 0 && a % b); } // divide a by b rounded up
ll floorDiv(ll a, ll b) { return a / b - ((a ^ b) < 0 && a % b); } // divide a by b rounded down
void setPrec(int x) { cout << fixed << setprecision(x); }

// TO_STRING
#define ts to_string
string ts(char c) { return string(1, c); }
string ts(const char* s) { return (string) s; }
string ts(string s) { return s; }
string ts(bool b) { return ts((int)b); }
template<class T> string ts(complex<T> c) { stringstream ss; ss << c; return ss.str(); }
template<class T> using V = vector<T>;
string ts(V<bool> v) {string res = "{"; FOR(i,0,SZ(v)-1) res += char('0'+v[i]); res += "}"; return res; }
template<size_t sz> string ts(bitset<sz> b) { string res = ""; FOR(i,0,SZ(b)-1) res += char('0'+b[i]); return res; }
template<class T, class U> string ts(pair<T,U> p);
template<class T> string ts(T v) { // containers with begin(), end()
    bool fst = 1; string res = "";
    for (const auto& x: v) { if (!fst) res += " "; fst = 0; res += ts(x); }
    return res;
}
template<class T, class U> string ts(pair<T,U> p) { return "("+ts(p.FI)+", "+ts(p.SE)+")"; }

// OUTPUT
template<class T> void pr(T x) { cout << ts(x); }
template<class T, class ...U> void pr(const T& t, const U&... u) { pr(t); pr(u...); }
void ps() { pr("\n"); } // print w/ spaces
template<class T, class ...U> void ps(const T& t, const U&... u) { pr(t); if (sizeof...(u)) pr(" "); ps(u...); }

// DEBUG
void DBG() { cerr << "]" << endl; }
template<class T, class ...U> void DBG(const T& t, const U&... u) { cerr << ts(t); if (sizeof...(u)) cerr << ", "; DBG(u...); }
#define dbg(...) cerr << "Line(" << __LINE__ << ") -> [" << #__VA_ARGS__ << "]: [", DBG(__VA_ARGS__)
#define chk(...) if (!(__VA_ARGS__)) cerr << "Line(" << __LINE__ << ") -> function(" \
        << __FUNCTION__  << ") -> CHK FAILED: (" << #__VA_ARGS__ << ")" << "\n", exit(0);

const ld PI = acos(-1.0);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
const ld EPS = 1e-9;
const ll MODBASE = 1000000007LL;
const int INF = 0x3f3f3f3f;

const int MAXN = 110;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

ll prod[7][5][3][3];
ll dp[15][7][5][3][3][2][2][2][110];

ll get(ll n) {
    if (n == 0) {
        return 0;
    }

    ll N = n;
    vi a;
    while (N) {
        a.push_back(N % 10);
        N /= 10;
    }
    int sz = SZ(a);
    a.push_back(0);
    reverse(ALL(a));

    // dbg(a);

    ll res = 0;

    FOR(i,0,sz) {
        FOR(j,0,6) {
            FOR(k,0,4) {
                FOR(l,0,2) {
                    FOR(m,0,2) {
                        FOR(x,0,1) {
                            FOR(y,0,1) {
                                FOR(z,0,1) {
                                    FOR(sum,0,108) {
                                        dp[i][j][k][l][m][x][y][z][sum] = 0;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    dp[0][0][0][0][0][1][0][0][0] = 1;
    // dp[i][x][y][z][t][0/1][0/1][sum] = num of numbers in which prod has 2^x * 3^y * 5^z * 7^t
    // whether it is equal to n, whether it has a non-zero number before,
    // whether there is a 0 in the prod and sum of digits = sum
    
    FOR(i,0,sz-1) {
        FOR(j,0,6) FOR(k,0,4) FOR(l,0,2) FOR(m,0,2) {
            FOR(x,0,1) FOR(y,0,1) FOR(z,0,1) {
                FOR(sum,0,108) {
                    if (!dp[i][j][k][l][m][x][y][z][sum]) {
                        continue;
                    }
                    // dbg(i, j, k, l, m, x, y, z, sum);
                    int num = a[i+1];
                    if (x == 0) {
                        FOR(d,0,9) {
                            if (d > 0) {
                                int newJ = j, newK = k, newL = l, newM = m;
                                int newSum = sum + d, newX = 0, newY = 1, newZ = z;
                                int g = d;
                                while (g > 1) {
                                    while (g % 2 == 0) {
                                        g /= 2;
                                        newJ++;
                                        if (newJ > 6) newJ = 6;
                                    }
                                    while (g % 3 == 0) {
                                        g /= 3;
                                        newK++;
                                        if (newK > 4) newK = 4;
                                    }
                                    while (g % 5 == 0) {
                                        g /= 5;
                                        newL++;
                                        if (newL > 2) newL = 2;
                                    }
                                    while (g % 7 == 0) {
                                        g /= 7;
                                        newM++;
                                        if (newM > 2) newM = 2;
                                    }
                                }
                                // dbg(i+1, newJ, newK, newL, newM, newX, newY, newZ, newSum);
                                dp[i+1][newJ][newK][newL][newM][newX][newY][newZ][newSum] += dp[i][j][k][l][m][x][y][z][sum];
                            } else {
                                if (y) {
                                    int newJ = 6, newK = 4, newL = 2, newM = 2;
                                    int newSum = sum, newX = 0, newY = 1, newZ = 1;
                                    // dbg(i+1, newJ, newK, newL, newM, newX, newY, newZ, newSum);
                                    dp[i+1][newJ][newK][newL][newM][newX][newY][newZ][newSum] += dp[i][j][k][l][m][x][y][z][sum];
                                } else {
                                    int newJ = j, newK = k, newL = l, newM = m;
                                    int newSum = sum, newX = 0, newY = 0, newZ = z;
                                    // dbg(i+1, newJ, newK, newL, newM, newX, newY, newZ, newSum);
                                    dp[i+1][newJ][newK][newL][newM][newX][newY][newZ][newSum] += dp[i][j][k][l][m][x][y][z][sum];
                                }
                            }
                        }
                    } else {
                        // case lower
                        FOR(d,0,num-1) {
                            if (d > 0) {
                                int newJ = j, newK = k, newL = l, newM = m;
                                int newSum = sum + d, newX = 0, newY = 1, newZ = z;
                                int g = d;
                                while (g > 1) {
                                    while (g % 2 == 0) {
                                        g /= 2;
                                        newJ++;
                                        if (newJ > 6) newJ = 6;
                                    }
                                    while (g % 3 == 0) {
                                        g /= 3;
                                        newK++;
                                        if (newK > 4) newK = 4;
                                    }
                                    while (g % 5 == 0) {
                                        g /= 5;
                                        newL++;
                                        if (newL > 2) newL = 2;
                                    }
                                    while (g % 7 == 0) {
                                        g /= 7;
                                        newM++;
                                        if (newM > 2) newM = 2;
                                    }
                                }
                                // dbg(i+1, newJ, newK, newL, newM, newX, newY, newZ, newSum);
                                dp[i+1][newJ][newK][newL][newM][newX][newY][newZ][newSum] += dp[i][j][k][l][m][x][y][z][sum];
                            } else {
                                if (y) {
                                    int newJ = 6, newK = 4, newL = 2, newM = 2;
                                    int newSum = sum, newX = 0, newY = 1, newZ = 1;
                                    // dbg(i+1, newJ, newK, newL, newM, newX, newY, newZ, newSum);
                                    dp[i+1][newJ][newK][newL][newM][newX][newY][newZ][newSum] += dp[i][j][k][l][m][x][y][z][sum];
                                } else {
                                    int newJ = j, newK = k, newL = l, newM = m;
                                    int newSum = sum, newX = 0, newY = 0, newZ = z;
                                    // dbg(i+1, newJ, newK, newL, newM, newX, newY, newZ, newSum);
                                    dp[i+1][newJ][newK][newL][newM][newX][newY][newZ][newSum] += dp[i][j][k][l][m][x][y][z][sum];
                                }
                            }
                        }

                        // case equal
                        if (num) {
                            int newJ = j, newK = k, newL = l, newM = m;
                            int newSum = sum + num, newX = 1, newY = 1, newZ = z;
                            int g = num;
                            while (g > 1) {
                                while (g % 2 == 0) {
                                    g /= 2;
                                    newJ++;
                                    if (newJ > 6) newJ = 6;
                                }
                                while (g % 3 == 0) {
                                    g /= 3;
                                    newK++;
                                    if (newK > 4) newK = 4;
                                }
                                while (g % 5 == 0) {
                                    g /= 5;
                                    newL++;
                                    if (newL > 2) newL = 2;
                                }
                                while (g % 7 == 0) {
                                    g /= 7;
                                    newM++;
                                    if (newM > 2) newM = 2;
                                }
                            }
                            // dbg(i+1, newJ, newK, newL, newM, newX, newY, newZ, newSum);
                            dp[i+1][newJ][newK][newL][newM][newX][newY][newZ][newSum] += dp[i][j][k][l][m][x][y][z][sum];
                        } else {
                            int newJ = 6, newK = 4, newL = 2, newM = 2;
                            int newSum = sum, newX = 1, newY = 1, newZ = 1;
                            // dbg(i+1, newJ, newK, newL, newM, newX, newY, newZ, newSum);
                            dp[i+1][newJ][newK][newL][newM][newX][newY][newZ][newSum] += dp[i][j][k][l][m][x][y][z][sum];
                        }
                    }
                }
            }
        }
    }

    FOR(j,0,6) {
        FOR(k,0,4) {
            FOR(l,0,2) {
                FOR(m,0,2) {
                    FOR(x,0,1) {
                        FOR(y,1,1) {
                            FOR(z,0,1) {
                                FOR(sum,1,108) {
                                    if (z || prod[j][k][l][m] % sum == 0) {
                                        res += dp[sz][j][k][l][m][x][y][z][sum];
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return res;
}

bool ok(int x) {
    int prod = 1;
    int sum = 0;
    while (x) {
        int g = x % 10;
        prod *= g;
        sum += g;
        x /= 10;
    }
    return prod % sum == 0;
}

int getTrau(int x) {
    int res = 0;
    FOR(i,1,x) {
        // if (ok(i)) cout << i << "\n";
        res += ok(i);
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int te;
    cin >> te;

    // 2 3 5 7
    // 6 4 2 2

    FOR(j,0,6) {
        FOR(k,0,4) {
            FOR(l,0,2) {
                FOR(m,0,2) {
                    if (j + k + l + m == 0) {
                        prod[j][k][l][m] = 1;
                    } else if (j) {
                        prod[j][k][l][m] = prod[j-1][k][l][m] * 2;
                    } else if (k) {
                        prod[j][k][l][m] = prod[j][k-1][l][m] * 3;
                    } else if (l) {
                        prod[j][k][l][m] = prod[j][k][l-1][m] * 5;
                    } else {
                        prod[j][k][l][m] = prod[j][k][l][m-1] * 7;
                    }
                }
            }
        }
    }

    // FOR(i,1,501) {
    //     if (getTrau(i) != get(i)) {
    //         cout << i <<endl;
    //         break;
    //     }
    // }
    // cout << getTrau(209) << ' ' << get(209);
    // return 0;
    FOR(o,1,te) {
        cout << "Case #" << o << ": ";
        ll l, r;
        cin >> l >> r;
        cout << get(r) - get(l-1) << "\n";
    }
    return 0;
}
