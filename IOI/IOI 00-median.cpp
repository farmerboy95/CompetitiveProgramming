/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Mainly from https://github.com/thecodingwizard/competitive-programming/blob/master/IOI/IOI%2000-median.cpp
*/

#include <bits/stdc++.h>
#include "device.h"
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

int n;

// randomly choose 2 different elements of array A, put others to newA
void randomAndFilter(vector<int> &A, int &a, int &b, int &N, vector<int> &newA) {
    N = SZ(A);
    a = rand() % N;
    b = rand() % N; 
    while (b == a) b = rand() % N;
    a = A[a]; b = A[b];
    for (int x : A)
        if (x != a && x != b) newA.push_back(x);
}

vector<int> solve(vector<int> A, int lPivot, int uPivot, int l, int r) {
    // we simply don't care about segments that do not cover the middle element
    // consider it already sorted
    if (l > n / 2 || r < n / 2) {
        vector<int> res = A;
        res.push_back(lPivot);
        res.push_back(uPivot);
        return res;
    }

    vector<int> lef, mid, rig;

    // now we split A into 3 parts, lef, mid and rig based one the median of the pivots and each element
    for (int x : A) {
        int m = Med3(lPivot,uPivot,x);
        if (m == lPivot) lef.push_back(x);
        else if (m == uPivot) rig.push_back(x);
        else mid.push_back(x);
    }

    // for each array, if there are more than 1 element in it, continue to choose 2 different elements
    // not positions, here we can sort those 2 elements and continue to solve.
    if (SZ(lef) >= 2) {
        int N, a, b; vector<int> newLef;
        randomAndFilter(lef, a, b, N, newLef);
        int med = Med3(a, b, lPivot);
        int lower = med == a ? b : a;
        // l + N means including the lower pivot
        lef = solve(newLef, lower, med, l, l + N);
    }

    if (SZ(mid) >= 2) {
        int N, a, b; vector<int> newMid;
        randomAndFilter(mid, a, b, N, newMid);
        int med = Med3(a, b, uPivot);
        int lower = med == a ? b : a;
        // l + SZ(lef) + 1 + N means including the upper pivot
        mid = solve(newMid, lower, med, l + SZ(lef) + 1, l + SZ(lef) + 1 + N);
    }

    if (SZ(rig) >= 2) {
        int N, a, b; vector<int> newRig;
        randomAndFilter(rig, a, b, N, newRig);
        int med = Med3(a, b, uPivot);
        int upper = med == a ? b : a;
        rig = solve(newRig, med, upper, l + SZ(lef) + 1 + SZ(mid) + 1, r);
    }

    // now just put everything sorted into one big array and return it
    vector<int> res;
    for (int x : lef) res.push_back(x);
    res.push_back(lPivot);
    for (int x : mid) res.push_back(x);
    res.push_back(uPivot);
    for (int x : rig) res.push_back(x);
    return res;
}

int Median(int N) {
    n = N;
    srand(time(NULL));

    // firstly, randomly choose 2 distinct position (1-indexed) in the initial list
    int a = rand() % n + 1, b = rand() % n + 1;
    while (b == a) b = rand() % n + 1;

    // put all other elements to a vector
    vector<int> A;
    FOR(i,1,n)
        if (i != a && i != b) A.push_back(i);

    // sort the array, don't worry too much about whether a < b or b < a
    // the array will still be sorted after all as the middle one would still be middle one
    // in both the ascending sorted and descending sorted versions
    A = solve(A, a, b, 0, n-1);
    return A[n/2];
}