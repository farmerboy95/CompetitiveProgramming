/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - If we know what prime factors x has, we can find x just using bruteforce.
        - To find the prime factors, we can just do (B, p) for every prime p in ascending order, 
        meanwhile calculate the numbers there supposed to be without x, if it differs with the 
        number the interactor gives, then x contains the prime factor p. This way, we can find 
        every prime factor except for the smallest one.
        - Let m be the number of primes no greater than n. Then we can split the prime numbers into
        sqrt(m) groups.
        After finishing asking a group, ask (A, 1) and check if the return value same as it 
        supposed to be without x. If it's the first time finding it different, it means the 
        smallest prime number is in the range, then just check every prime numbers in the 
        range by asking (A, p).
        - After finding the prime factors, for each factor, ask (A, p^k), it can be proved 
        this step will be done around log(n) times.
        - The total number of operations if around m + 2 * sqrt(m) + log(n)
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

int nt[MAXN], visited[MAXN];
vector<int> primes;
bool foundSmallest = false;

void sieveBase(int n) {
    FOR(i,2,n) {
        if (nt[i] == 0) {
            nt[i] = i;
            primes.push_back(i);
            for (ll j = (ll) i * i; j <= n; j += i) nt[j] = i;
        }
    }
}

int ask(char ch, int x) {
    cout << ch << ' ' << x << endl;
    int g;
    cin >> g;
    return g;
}

void answer(int x) {
    cout << "C " << x << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int n;
    cin >> n;
    sieveBase(n);
    int k = int(sqrt(SZ(primes)));
    int res = 1, sum = n;
    MS(visited, 0);
    FOR(i,0,SZ(primes)-1) {
        int x = ask('B', primes[i]);
        int num = 0;
        for (int j = primes[i]; j <= n; j += primes[i])
            if (!visited[j]) {
                num++;
                sum--;
                visited[j] = 1;
            }
        if (x != num) {
            for (ll w = primes[i]; w <= n; w *= primes[i]) {
                int y = ask('A', w);
                if (y) res *= primes[i];
                else break;
            }
        }
        if ((i % k == k-1 || i == SZ(primes)-1) && !foundSmallest) {
            int y = ask('A', 1);
            if (y != sum) {
                for (int j = i - k + 1; j <= i; j++) {
                    for (ll w = primes[j]; w <= n; w *= primes[j]) {
                        int z = ask('A', w);
                        if (z) {
                            res *= primes[j];
                            foundSmallest = true;
                        }
                        else break;
                    }
                    if (foundSmallest) break;
                }
            }
        }
    }
    answer(res);
    return 0;
}
