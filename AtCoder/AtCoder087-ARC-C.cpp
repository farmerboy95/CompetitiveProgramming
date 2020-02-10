/*
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Consider a trie, if we have all the strings of length from 1 to L, we would have a 
        complete binary tree of height L+1 in that trie
        - Put all the input strings into that trie, mark only the last node of each string.
        - A good string set means no marked pair of nodes has ancestor-descendant relation.
        - So we cannot use parents of marked nodes and descendants of them as well => the
        remaining nodes form a disjoint set of complete binary trees.
        - We can solve each tree independently using Grundy number (considering its height) 
        and xor all of them to get the result.
        - How to calculate Grundy number? https://img.atcoder.jp/arc087/editorial.pdf (page 7)
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

struct TrieNode {
    TrieNode *children[2];
    bool isEndOfWord;
}; 

TrieNode *getNode() {
    TrieNode *pNode =  new TrieNode;
    pNode->isEndOfWord = false;
    FOR(i,0,1) pNode->children[i] = nullptr; 
    return pNode; 
}

void insert(TrieNode *root, string &key) {
    TrieNode *pCrawl = root; 
    FOR(i,0,SZ(key)-1) { 
        int index = key[i] - '0'; 
        if (!pCrawl->children[index]) pCrawl->children[index] = getNode(); 
        pCrawl = pCrawl->children[index]; 
    }
    pCrawl->isEndOfWord = true;
}

string s;
int n;
ll L;

ll getGrundyNumber(TrieNode *root, int depth) {
    if (root->isEndOfWord) return 0;
    ll res = 0;
    FOR(i,0,1) {
        if (!root->children[i]) {
            ll h = L - depth;
            ll grundy = (-h) & (h);
            res ^= grundy;
        }
        else {
            res ^= getGrundyNumber(root->children[i], depth+1);
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n >> L;
    TrieNode *root = getNode();
    FOR(i,1,n) {
        cin >> s;
        insert(root, s);
    }

    ll res = getGrundyNumber(root, 0);
    if (res) cout << "Alice";
    else cout << "Bob";
    return 0;
}
