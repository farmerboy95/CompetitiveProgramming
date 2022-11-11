/*
    Template Version: 1.0.0 - 20220620
    Author: Nguyen Tan Bao
    Status: AC
    Idea:
        - Use Splay Tree
        - Submitted here: http://120.78.128.11/Problem.jsp?pid=2239
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

// Splay Tree Node
struct Node {
    // define parent node and its 2 children
    Node* parent, *children[2];
    // the size of the subtree with root as this node
    int size;
    // value of the node
    int val;
    // label of lazy reversal
    int labelReverse;

    // constructor
    Node(int val) {
        parent = children[0] = children[1] = NULL;
        size = 1;
        this->val = val;
        labelReverse = 0;
    }

    // apply labels and push them down to children
    void pushDown() {
        if (labelReverse) {
            FOR(i,0,1) {
                if (children[i]) {
                    children[i]->reverse();
                }
            }
            labelReverse = 0;
        }
    }

    // update size of subtree
    void update() {
        size = 1;
        FOR(i,0,1) {
            if (children[i]) {
                size += children[i]->size;
            }
        }
    }

    // reverse the whole subtree, first thing is to swap 2 children
    void reverse() {
        swap(children[0], children[1]);
        labelReverse ^= 1;
    }
};

struct SplayTree {
    Node *root;
    vector<int> res;

    // create splay tree with 2 dummy nodes (far-left and far-right)
    SplayTree() {
        root = new Node(-1);
        root->children[1] = new Node(-1);
        root->size = 2;
        root->children[1]->parent = root;
    }

    // since we have 2 dummy nodes, the size should be 2 less than the real size
    int size() { 
        return root->size - 2;
    }

    // Helper function to rotate node
    void rotate(Node *node) {
        int dirOfNode = (node->parent->children[1] == node);
        Node *parentNode = node->parent;

        Node *movingChildOfNode = node->children[dirOfNode ^ 1];

        if (parentNode->parent) {
            parentNode->parent->children[parentNode->parent->children[1] == parentNode] = node;
        }

        node->parent = parentNode->parent;
        node->children[dirOfNode ^ 1] = parentNode;

        parentNode->parent = node;
        parentNode->children[dirOfNode] = movingChildOfNode;

        if (movingChildOfNode) {
            movingChildOfNode->parent = parentNode;
        }

        parentNode->update();
        node->update();
    }

    // Splay node so that it is under desiredParent (or to root if desiredParent is null).
    void splay(Node *node, Node *desiredParent = NULL) {
        while (node->parent != desiredParent) {
            Node *parent = node->parent, *parentOfParent = parent->parent;
            if (parentOfParent == desiredParent) {
                rotate(node);
            } else if ((parentOfParent->children[0] == parent) == (parent->children[0] == node)) {
                rotate(parent);
                rotate(node);
            } else {
                rotate(node);
                rotate(node);
            }
        }
        if (!desiredParent) {
            root = node;
        }
    }

    // Helper function to walk down the tree.
    int walk(Node *node, int &dir, int &pos) {
        node->pushDown();
        int leftSize = node->children[0] ? node->children[0]->size : 0;
        dir = (leftSize < pos);
        if (dir) {
            pos -= leftSize + 1;
        }
        return leftSize;
    }

    // Insert node n to position pos
    void insert(Node *node, int pos) {
        Node *cur = root;
        int dir;
        // since we have the far-left dummy node and pos starts from 0, increase pos
        pos++;
        while (1) {
            walk(cur, dir, pos);
            if (!cur->children[dir]) {
                break;
            }
            cur = cur->children[dir];
        }

        cur->children[dir] = node;
        node->parent = cur;
        splay(node);
    }

    // Find the node at position pos. If sp is true, splay it.
    Node* find(int pos, int sp = true) {
        Node *cur = root;
        int dir;
        // since we have the far-left dummy node and pos starts from 0, increase pos
        pos++;
        while (pos < walk(cur, dir, pos) || dir) {
            cur = cur->children[dir];
        }
        if (sp) splay(cur);
        return cur;
    }

    // find range [posL, posR)
    // splay node posR to root, then splay posL-1 to below posR, then [posL, posR-1] will be right node of posL-1
    Node *findRange(int posL, int posR) {
        Node *r = find(posR), *l = find(posL - 1, false);
        splay(l, r);
        if (l->children[1]) l->children[1]->pushDown();
        return l->children[1];
    }

    // find range then disconnect it from the tree
    // remove from position [posL, posR)
    Node* eraseRange(int posL, int posR) {
        Node *range = findRange(posL, posR);
        range->parent->children[1] = NULL;
        range->parent->update();
        range->parent->parent->update();
        range->parent = NULL;
        return range;
    }

    // recursively print subtree with in-order traversal
    void print(Node *cur, string pref) {
        if (cur == NULL) return;
        cur->pushDown();
        print(cur->children[1], pref + "  ");
        cout << pref << cur->val << "\n";
        print(cur->children[0], pref + "  ");
    }

    // print the whole tree with in-order traversal
    // the tree shown in output will be the same as the real tree if you rotate it 90 degree clockwise
    void printTree() {
        print(root, "");
        cout << "\n";
    }

    void printAnsRev(Node *cur, vector<int> &r) {
        if (cur == NULL) return;
        cur->pushDown();
        printAnsRev(cur->children[0], r);
        if (cur->val != -1) {
            r.push_back(cur->val);
        }
        printAnsRev(cur->children[1], r);
    }

    void printAns() {
        res.clear();
        printAnsRev(root, res);
        FOR(i,0,SZ(res)-1) {
            if (i > 0) cout << ' ';
            cout << res[i];
        }
        cout << "\n";
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int n, m;
    while (cin >> n >> m && !(n == -1 && m == -1)) {
        SplayTree t;
        FOR(i,1,n) {
            t.insert(new Node(i), t.size());
        }
        while (m--) {
            string s;
            int x, y, k;
            cin >> s;
            if (s == "CUT") {
                cin >> x >> y >> k;
                Node *cut = t.eraseRange(x-1, y);
                t.insert(cut, k);
            } else {
                cin >> x >> y;
                t.findRange(x-1, y)->reverse();
            }
        }

        t.printAns();
    }
    return 0;
}
