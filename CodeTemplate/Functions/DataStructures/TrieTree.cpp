// Illustrate by the form of SRM 722 Div 1 Easy
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
const int MAXN = 100010;
const int MAXM = 200010;
const int MAXK = 110;
const int MAXQ = 200010;

struct TrieNode {
    TrieNode *children[10];
    bool isEndOfWord;
}; 

TrieNode *getNode() {
    TrieNode *pNode =  new TrieNode;
    pNode->isEndOfWord = false;
    FOR(i,0,9) pNode->children[i] = nullptr; 
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

bool search(TrieNode *root, string &key) { 
    TrieNode *pCrawl = root; 
    FOR(i,0,SZ(key)-1) { 
        int index = key[i] - '0'; 
        if (!pCrawl->children[index]) return false; 
        pCrawl = pCrawl->children[index]; 
    } 
    return (pCrawl != nullptr && pCrawl->isEndOfWord); 
}

bool isEmpty(TrieNode* root) {
    FOR(i,0,9)
        if (root->children[i]) return false; 
    return true; 
}

// optional for copying, hasn't been tested yet
TrieNode* remove(TrieNode* root, string &key, int depth = 0) {
    if (!root) return nullptr; 
    if (depth == SZ(key)) {
        if (root->isEndOfWord) root->isEndOfWord = false; 
        if (isEmpty(root)) { 
            delete (root); 
            root = nullptr;
        } 
        return root; 
    } 

    int index = key[depth] - '0'; 
    root->children[index] = remove(root->children[index], key, depth + 1); 
 
    if (isEmpty(root) && root->isEndOfWord == false) { 
        delete (root); 
        root = nullptr; 
    } 
    return root; 
}

class TCPhoneHome {
    public:
    ll mu[20];

    ll count(TrieNode *root, int digits) {
        ll res = 0;
        if (root->isEndOfWord) return res;
        FOR(i,0,9) {
            if (root->children[i]) res += count(root->children[i], digits-1);
            else res += mu[digits-1];
        }
        return res;
    }

    ll validNumbers(int digits, vector<string> specialPrefixes) {
        mu[0] = 1;
        FOR(i,1,17) mu[i] = mu[i-1] * 10;
        TrieNode *root = getNode();
        FOR(i,0,SZ(specialPrefixes)-1) insert(root, specialPrefixes[i]);
        return count(root, digits);
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    TCPhoneHome a;
    cout << a.validNumbers(7, {"0", "1", "911"}) << endl;
    cout << a.validNumbers(10, {"0", "1", "911"}) << endl;
    cout << a.validNumbers(8, {"1", "12", "123"}) << endl;
    cout << a.validNumbers(9, {"12", "13", "14"}) << endl;
    cout << a.validNumbers(3, {"411"}) << endl;
    return 0;
}
