/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - As the string contains only 2 letters A and B, so we group them with number of times
        each character appears in each group.
        - The first observation here is that if the string ends with one or many consecutive "BA",
        we call it a group of "BA", after one operation, that group of "BA" will still be there.
        Easy to see with some drafting.
        - The second observation is that, one operation is like this: Take the first character 
        of the string. If it's A, we change it to B and put it back to the beginning of the string. 
        If it's B, we flip it and all the other characters in the string (A -> B, B -> A). Put that 
        character to the end of the string. The above sequence can only be true if we remove all the
        trailing "BA" from the string. It means we don't need to care about the trailing "BA".
        - The third observation is that, it would take about O(1) operations to create one "BA" at the
        end of the string, so it would take O(n) for the string to have full "BA". There are 2 cases here:
            + Case 1: n is odd. So the string could be ABABA...BA or BBABA...BA after O(n) operations.
            After one operation, the first will become the second and vice versa. We can easily deal
            with the result here as there are only 2 cases.
            + Case 2: n is even. So the string could be BABABA...BA after O(n) operations. Easy to deal.
        - Ok, we've nearly got there. We can use deque to do the stuff. The only problem here is to 
        flip the string. It can be done with a variable "stat". If stat = 0, the values in deque are
        the same as the string, if stat = 1, the values in deque are the reversed comparing to the string.
        - Complexity O(n)
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

int n, k;
string s, res;
deque<II> a;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> k;
    cin >> s;

    // grouping
    char ch = s[0];
    int cnt = 1;
    FOR(i,1,n-1) {
        if (s[i] == ch) cnt++;
        else {
            a.push_back(II(ch-'A', cnt));
            ch = s[i];
            cnt = 1;
        }
    }
    a.push_back(II(ch-'A', cnt));
    
    int stat = 0;
    while (k) {
        int firstChar = a.front().FI;

        if (a.front().SE == 1) a.pop_front();
        else {
            II p = a.front();
            a.pop_front();
            p.SE--;
            a.push_front(p);
        }

        int realFirstChar = firstChar;
        if (stat) realFirstChar = 1-realFirstChar;

        if (realFirstChar == 0) {
            // A
            II p = II(1-firstChar, 1);
            if (SZ(a) && a.front().FI == p.FI) {
                II q = a.front();
                a.pop_front();
                q.SE++;
                a.push_front(q);
            } else {
                a.push_front(p);
            }
        } else {
            // B
            stat = 1-stat;
            II p = II(firstChar, 1);
            if (SZ(a) && a.back().FI == p.FI) {
                II q = a.back();
                a.pop_back();
                q.SE++;
                a.push_back(q);
            } else {
                a.push_back(p);
            }
        }

        // remove trailing "BA"
        if (SZ(a) > 1 && a.back().SE == 1) {
            int realLastChar = a.back().FI;
            if (stat) realLastChar = 1-realLastChar;
            if (realLastChar == 0 && SZ(a) > 1) {
                a.pop_back();
                if (a.back().SE == 1) a.pop_back();
                else {
                    II p = a.back();
                    a.pop_back();
                    p.SE--;
                    a.push_back(p);
                }
            }
        }
        k--;

        // check if it's time to stop
        if (SZ(a) == 1 && a.front().SE == 1 && k % 2 == 0) break;
        if (SZ(a) == 0) break;
    }

    // get res
    while (SZ(a)) {
        II p = a.front();
        a.pop_front();
        if (stat) p.FI = 1-p.FI;
        FOR(i,1,p.SE) res += char('A' + p.FI);
    }
    // add "BA" till the res length is n
    while (SZ(res) < n) res += "BA";
    cout << res;
    return 0;
}
