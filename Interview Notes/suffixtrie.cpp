
#include <bits/stdc++.h>
using namespace std;

// Do not edit the class below except for the
// populateSuffixTrieFrom and contains methods.
// Feel free to add new properties and methods
// to the class.
class TrieNode {
public:
    unordered_map<char, TrieNode *> children;
};

class SuffixTrie {
public:
    TrieNode *root;
    char endSymbol;

    SuffixTrie(string str) {
        this->root = new TrieNode();
        this->endSymbol = '*';
        this->populateSuffixTrieFrom(str);
    }

    void populateSuffixTrieFrom(string str) {
        for (int i = 0; i < str.length(); i++) {
            this->insertSubstringStartingAt(i, str);
        }
    }
	
    void insertSubstringStartingAt(int i, string &str) {
        TrieNode *node = this->root;
        for (int j = i; j < str.length(); j++) {
            char ch = str[j];
            if (node->children.find(ch) == node->children.end()) { 
                node->children[ch] = new TrieNode();
            }
            node = node->children[ch];
        }
        node->children[this->endSymbol] = NULL;
    }

    bool contains(string str) {
        TrieNode *node = this->root;
            for (char ch : str) {
                if (node->children.find(ch) == node->children.end()) {
                    return false;
                }
                node = node->children[ch];
            }
        return node->children.find(this->endSymbol) != node->children.end();
    }
};
