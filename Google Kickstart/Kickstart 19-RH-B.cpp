/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - As this problem require diagonal handling, we transform the 2d array into diamond shape
        - (x, y) -> (x+y-1, x-y+n)
        - So left diagonal operations and right diagonal operations become horizontal and vertical operations.

        - One node is affected by one horizontal and one vertical operation, so the order of operation does not matter.
        - We just need to consider horizontal operations, then calculate the number of vertical operations needed

        - For example: 1 1 0
                       0 1 0
                       0 1 1
                       (n = 3)
        => Transform
         |1 2 3 4 5
        -|---------
        1|    0
        2|  1   0
        3|1   0   1
        4|  0   1
        5|    0

        - Consider row n (in this example is 3), we can easily see that rows from n-2, n-4.... must have the form of row n
        - Example: row n: 1 0 0 1 0 0 1
                 row n-4:     0 1 0
                 row n-4:     1 0 1 (must use horizontal operation to have the form of row n)
        - It means: row x after before or after horizontal operation must be equal to subarray of row n from the middle to 2 sides.
        - So each row n-2, n-4,..., n+2, n+4,... depend on row n
        - And each row n-1, n-3,..., n+1, n+3,... depend on row n-1, these 2 groups are independent.

        - So we can calculate the number of horizontal operation needed when we don't use operation on row n and when we use it
        - Similarly calculate the number of horizontal operation needed when we don't use operation on row n-1 and when we use it

        - Simutaneously, we can calculate the number of vertical operation needed, it is the number of 0 in the row that we are considering.

        - Result = min(useOpRowN, notUseOpRowN) + min(useOpRowNMinus1, notUseOpRowNMinus1)
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
typedef pair<int, II> III;
typedef complex<ld> cd;
typedef vector<cd> vcd;
 
const ll MODBASE = 1000000007LL;
const int MAXN = 210;
const int MAXM = 100010;
const int MAXK = 110;
const int MAXQ = 200010;

int n;
int a[MAXN][MAXN];

void swapArr(int i) {
    int st = abs(n-i) + 1;
    int en = n+n-1 - abs(n-i);
    for (int j = st; j <= en; j += 2) a[i][j] = 1-a[i][j];
}

void calcOdd(int &needOdd) {
    for (int i = 1; i <= n+n-1; i += 2) {
        int st = abs(n-i) + 1;
        int en = n+n-1 - abs(n-i);
        if (n % 2) {
            needOdd += (a[i][st] != a[n][st]);
            if (i == n) 
                for (int j = st; j <= en; j += 2) needOdd += (a[i][j] == 0);
        }
        else {
            needOdd += (a[i][st] != a[n-1][st]);
            if (i == n-1) 
                for (int j = st; j <= en; j += 2) needOdd += (a[i][j] == 0);
        }
    }
}

void calcEven(int &needEven) {
    for (int i = 2; i <= n+n-1; i += 2) {
        int st = abs(n-i) + 1;
        int en = n+n-1 - abs(n-i);
        if (n % 2) {
            needEven += (a[i][st] != a[n-1][st]);
            if (i == n-1)
                for (int j = st; j <= en; j += 2) needEven += (a[i][j] == 0);
        }
        else {
            needEven += (a[i][st] != a[n][st]);
            if (i == n)
                for (int j = st; j <= en; j += 2) needEven += (a[i][j] == 0);
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int t;
    cin >> t;
    FOR(o,1,t) {
        cout << "Case #" << o << ": ";
        cin >> n;
        FOR(i,1,n)
            FOR(j,1,n) {
                char ch;
                cin >> ch;
                if (ch == '#') a[i+j-1][i-j+n] = 1;
                else a[i+j-1][i-j+n] = 0;
            }
        
        int needOdd = 0, needEven = 0;
        calcOdd(needOdd);
        calcEven(needEven); 

        swapArr(n);
        int needOdd2 = 1;
        swapArr(n-1);
        int needEven2 = 1;

        calcOdd(needOdd2);
        calcEven(needEven2);

        cout << min(needOdd, needOdd2) + min(needEven, needEven2) << "\n";
    }
    return 0;
}
