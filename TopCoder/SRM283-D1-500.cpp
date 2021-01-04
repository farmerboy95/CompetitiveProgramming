/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - We need to calculate F = a1! ^ a2! ^ a3! ^ ... % m
        - F = a1! ^ (a2! ^ a3! ^ ...) % m
        - So first thing first, we need to calculate a1! % m
        - If a1 >= m, so a1 % m = 0, otherwise, we can find the cycle of a1 ^ 1, a1 ^ 2, a1 ^ 3, ...
        we don't consider a1^0 as 0! = 1 => all exp would be larger than 0. There would be 2 parts:
        the remainder and the cycle length.
        - If remainder = 0 => a1 ^ 1 is in the cycle, we can solve the problem recursively with 
        the next number (a2) and m = cycle length.
        - Now we have some remainders, there are 2 cases here:
            + Exp > remainder: it's in the cycle, so we can solve the problem with next number 
            and m = cycle length, then remove the reminder and find the appropriate exp for a1
            + Exp <= remainder: just get a1! ^ exp
        - How to check the above condition? We need some if-else here. Check the code for more info.
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
const int MAXN = 110;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

class FactorialTower {
    public:
    vector<int> arr;
    int n;

    int calcFacMod(int w, int m) {
        if (w >= m) return 0;
        int res = 1;
        FOR(i,1,w) {
            res = res * i % m;
        }
        return res;
    }

    int solve(int idx, int m) {
        // x = a[i]! % m
        int x = calcFacMod(arr[idx], m);

        // some corner cases
        if (x == 0) {
            return 0;
        }

        if (x == 1) {
            return 1 % m;
        }

        if (idx == n-1) {
            return x;
        }

        // get remainder and cycle
        int y = x;
        int cnt = 1;
        map<int, int> ma;
        ma[x] = 1;
        int cycle = 0, remain = 0;
        while (1) {
            y = y * x % m;
            cnt++;
            if (ma.count(y)) {
                int pos = ma[y];
                cycle = cnt - pos;
                remain = pos - 1;
                break;
            }
            ma[y] = cnt;
        }

        if (remain == 0) {
            // already in the cycle
            int q = solve(idx+1, cycle);
            if (q == 0) q = cycle;
            int res = x;
            FOR(i,1,q-1) {
                res = res * x % m;
            }
            return res;
        }

        int l = idx+1, r = 0;
        FOR(i,idx+1,n) {
            if (arr[i] <= 1) {
                r = i-1;
                break;
            }
        }

        bool largerThanRemain = false;
        int p = 0;
        if (r - l + 1 >= 4) {
            largerThanRemain = true;
        } else if (r - l + 1 == 1) {
            int x = arr[l];
            if (x > 7) {
                largerThanRemain = true;
            } else {
                FOR(i,1,arr[l]-1) x *= i;
                largerThanRemain |= (x > remain);
                p = x;
            }
        } else if (r - l + 1 == 2) {
            int x = arr[l], y = arr[l+1];
            if (x > 5 || y > 5) {
                largerThanRemain = true;
            } else {
                FOR(i,1,arr[l]-1) {
                    x *= i;
                }
                FOR(i,1,arr[l+1]-1) {
                    y *= i;
                }
                p = 1;
                FOR(i,1,y) {
                    p *= x;
                    if (p > remain) {
                        largerThanRemain = true;
                        break;
                    }
                }
            }
        } else if (r - l + 1 == 3) {
            int x = arr[l], y = arr[l+1], z = arr[l+2];
            if (x > 3 || y > 3 || z > 3) {
                largerThanRemain = true;
            } else {
                FOR(i,1,arr[l]-1) {
                    x *= i;
                }
                FOR(i,1,arr[l+1]-1) {
                    y *= i;
                }
                FOR(i,1,arr[l+2]-1) {
                    z *= i;
                }
                p = 1;
                FOR(i,1,z) {
                    p *= y;
                    if (p > remain) {
                        largerThanRemain = true;
                        break;
                    }
                }
                if (!largerThanRemain) {
                    y = p;
                    p = 1;
                    FOR(i,1,y) {
                        p *= x;
                        if (p > remain) {
                            largerThanRemain = true;
                            break;
                        }
                    }
                }
            }
        } else {
            return x;
        }

        if (!largerThanRemain) {
            int res = x;
            FOR(i,1,p-1) {
                res = res * x % m;
            }
            return res;
        }

        // else
        int q = solve(idx+1, cycle);
        q = q - remain;
        while (q < 0) q += cycle;
        q %= cycle;
        if (q == 0) q = cycle;
        q += remain;
        int res = x;
        FOR(i,1,q-1) {
            res = res * x % m;
        }
        return res;
    }

    int exprValue(vector<int> &a, int m) {
        arr = a;
        n = SZ(a);
        arr.push_back(1);
        return solve(0, m);
    }

    int exprValue2(vector<int> a, int m) {
        return exprValue(a, m);
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    FactorialTower s;
    cout << s.exprValue2({2,2,2,2}, 10) << "\n";
    cout << s.exprValue2({3,8}, 100) << "\n";
    cout << s.exprValue2({775,967,1,1,1}, 39877) << "\n";
    cout << s.exprValue2({0}, 40000) << "\n";
    cout << s.exprValue2({5,4,123456789,987654321,687955994,1162330089,195458992,1687386387,
1092101949,1086091397,902287014,341660341,1600834655,131565486,1494304912,
384585199,1883009662,916903507,1895924341,397197724,1883021244,1616061080,
1437763283,621297237,1883141487,282508826,285957625,1249530903,1484124572,
1822993209,1668351723,174237628,1589170712,992959839,1281777023,1158939002,
1488964134,1806511164,1519656093,159671689,542573000,1571768398,1203500608,
1053387535,793607740,1535801392,1798307613,552983945,901802936,1023595016}, 40000) << "\n";
    cout << s.exprValue2({2,3,2}, 36864) << "\n";
    cout << s.exprValue2({2, 1, 500, 600}, 34816) << "\n";
    cout << s.exprValue2({3, 9999}, 32768) << "\n";
    return 0;
}