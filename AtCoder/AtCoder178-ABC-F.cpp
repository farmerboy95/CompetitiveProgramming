/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Let's define cntA[i] contains all the positions x where a[x] = i, cntB[i] contains all 
        the positions x where a[x] = i.
        - Then put all pairs (cntA[i], i) into a set A, (cntB[i], i) that i has at least one appearance
        in A into a set BinA, otherwise put them into a set B.
        - One corner case: if cntA[i] + cntB[i] > n => NO (obviously), otherwise it should have one solution
        - Now we do like this: We try to fill unpaired element in A from the largest group to the smallest.
        How do we fill? For example, if we get number "num" from set A which is in the largest unpaired group
        we should find a number "num2" from BinA which is not equal to "num", if not having one, we can find
        one in set B to pair with num. In this way, we can minimize the size of BinA and reduce the size of
        the largest unpaired group in A.
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
const int MAXN = 200010;
const int MAXM = 1000;
const int MAXK = 16;
const int MAXQ = 200010;

int a[MAXN], b[MAXN], n, res[MAXN];
vector<int> cntA[MAXN], cntB[MAXN];
set<II> A, BinA, B;

void sayNo() {
    cout << "No";
    exit(0);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    FOR(i,1,n) cin >> a[i];
    FOR(i,1,n) cin >> b[i];
    FOR(i,1,n) cntA[a[i]].push_back(i);
    FOR(i,1,n) cntB[b[i]].push_back(i);
    FOR(i,1,n)
        if (SZ(cntA[i]) + SZ(cntB[i]) > n) sayNo();

    FOR(i,1,n) 
        if (SZ(cntA[i])) A.insert(II(SZ(cntA[i]), i));
    
    FOR(i,1,n)
        if (SZ(cntB[i])) {
            if (SZ(cntA[i])) BinA.insert(II(SZ(cntB[i]), i));
            else B.insert(II(SZ(cntB[i]), i));
        }

    while (SZ(A)) {
        auto it = A.end();
        it--;
        A.erase(it);
        int num = it->SE, num2 = -1, num3 = -1;
        if (SZ(BinA)) {
            auto it2 = BinA.end();
            it2--;
            if (it2->SE == num) {
                if (SZ(BinA) > 1) {
                    it2--;
                    num2 = it2->SE;
                    BinA.erase(it2);
                } else {
                    auto it3 = B.end();
                    it3--;
                    num3 = it3->SE;
                    B.erase(it3);
                }
            } else {
                num2 = it2->SE;
                BinA.erase(it2);
            }
        } else {
            auto it3 = B.end();
            it3--;
            num3 = it3->SE;
            B.erase(it3);
        }

        if (num2 != -1) {
            // found an element in BinA
            int pos = cntA[num].back();
            cntA[num].pop_back();
            int pos2 = cntB[num2].back();
            cntB[num2].pop_back();
            res[pos] = b[pos2];
            if (SZ(cntA[num])) A.insert(II(SZ(cntA[num]), num));
            else {
                if (SZ(cntB[num])) {
                    BinA.erase(BinA.find(II(SZ(cntB[num]), num)));
                    B.insert(II(SZ(cntB[num]), num));
                }
            }
            if (SZ(cntB[num2])) BinA.insert(II(SZ(cntB[num2]), num2));
        } else {
            // found an element in B
            int pos = cntA[num].back();
            cntA[num].pop_back();
            int pos3 = cntB[num3].back();
            cntB[num3].pop_back();
            res[pos] = b[pos3];
            if (SZ(cntA[num])) A.insert(II(SZ(cntA[num]), num));
            else {
                if (SZ(cntB[num])) {
                    BinA.erase(BinA.find(II(SZ(cntB[num]), num)));
                    B.insert(II(SZ(cntB[num]), num));
                }
            }
            if (SZ(cntB[num3])) B.insert(II(SZ(cntB[num3]), num3));
        }
    }
    
    cout << "Yes\n";
    FOR(i,1,n) cout << res[i] << ' ';
    
    return 0;
}
