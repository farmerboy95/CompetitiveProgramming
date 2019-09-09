/*
    Author: Nguyen Tan Bao
    Status: Can't solve so far
    Approach:
        - At first I thought that after sorting the input, for each group of string with the same first character, 
        I could use g[i][j] which is the result when I take consecutive j strings of string group with (i + 'a') 
        as a starting character, then I could use dp to combine them together to get the result but I was deadly wrong on test 10. 
        - But above approach actually gave me the idea about Trie Tree, I could save an array of result if we choose X strings 
        on each node and combine childs' array together with DP.
        - After hours thinking about the solution with Trie Tree, I really could not end up with an approach 
        that can handle both space and time complexity, so that I looked at this submission
        https://codeforces.com/contest/178/submission/58235989
        - It uses Trie and saves an array on each node but on leaves and nodes that have 2 or more childs, that's brilliant.
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
#define WHATIS(x) cout << #x << " is " << x << endl;
#define ERROR(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
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

void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
    cout << *it << " = " << a << endl;
    err(++it, args...);
}

const ll MODBASE = 1000000007LL;
const int MAXN = 2010;
const int MAXM = 200010;
const int MAXK = 110;
const int MAXQ = 200010;

int n, K;
// we have at most N leaves and N nodes that have 2 or more childs
ll dp[MAXN * 2][MAXN], tmp[MAXN];

struct TrieNode {
    TrieNode *children[27];
    int depth, cnt;
}; 

TrieNode *getNode() {
    TrieNode *pNode =  new TrieNode;
    pNode->depth = 0;
    pNode->cnt = 0;
    FOR(i,0,26) pNode->children[i] = nullptr; 
    return pNode; 
}

void insert(TrieNode *root, string &key) {
    root->cnt++;
    TrieNode *pCrawl = root;
    FOR(i,0,SZ(key)-1) { 
        int index = key[i] - 'a';
        if (key[i] == '$') index = 26;
        if (!pCrawl->children[index]) {
            pCrawl->children[index] = getNode(); 
            pCrawl->children[index]->depth = pCrawl->depth + 1;
        }
        pCrawl = pCrawl->children[index];
        pCrawl->cnt++;
    }
}

int nowId = 0;

int getId() {
    return nowId++;
}

int calc(TrieNode *root) {
    int nodeId = -1;
    int posChild = -1, cntChild = 0;
    FOR(i,0,26)
        if (root->children[i] != nullptr) {
            cntChild++;
            posChild = i;
        }
    
    // leaf of tree, we get dp array right away
    if (posChild == -1) {
        nodeId = getId();
        // remember to -1 in depth because we are in '$' character, not the last a-z character of a string
        FOR(i,0,min(root->cnt,K)) dp[nodeId][i] = (ll) (root->depth-1) * i * (i - 1) / 2;
        return nodeId;
    }
    // if this node has only one child, go directly to it
    if (cntChild == 1) return calc(root->children[posChild]);
    
    // otherwise, use dp for each child
    nodeId = getId();
    FOR(i,0,K) dp[nodeId][i] = 0;
    int numOfString = 0;
    FOR(i,0,26)
        if (root->children[i] != nullptr) {
            int childNodeId = calc(root->children[i]);
            int numStringAtChild = root->children[i]->cnt;

            FOR(j,0,K) tmp[j] = 0;

            // with j strings that we have and k new string, combine them together and put them into a temp array with single dp
            // after reading the code, I realized that this part took smaller time than I thought, only O(n^2) for all
            FOR(j,0,min(K,numOfString))
                FOR(k,0,min(K,numStringAtChild)) {
                    if (j + k <= K) tmp[j+k] = max(tmp[j+k], (ll) dp[nodeId][j] + dp[childNodeId][k] + (ll) j * k * root->depth);
                    else break;
                }

            FOR(j,0,K) dp[nodeId][j] = tmp[j];
            numOfString += numStringAtChild;
            
        }
    return nodeId;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> K;
    TrieNode *root = getNode();
    FOR(i,0,n-1) {
        string t;
        cin >> t;
        // add one more character out of a-z to indicate the last point on Trie Tree
        // this would avoid the situation that an end point of a string is not a leaf
        t = t + "$";
        insert(root, t);
    }
    int nodeId = calc(root);
    cout << dp[nodeId][K];
    return 0;
}
