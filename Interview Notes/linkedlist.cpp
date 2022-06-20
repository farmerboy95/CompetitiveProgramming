
#include <bits/stdc++.h>
using namespace std;

class Node {
public:
  int value;
  Node *prev;
  Node *next;

  Node(int value);
};

// Feel free to add new properties and methods to the class.
class DoublyLinkedList {
public:
  Node *head;
  Node *tail;

    DoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
    }

    void setHead(Node *node) {
        if (head == NULL) {
            head = tail = node;
            return;
        }
        insertBefore(head, node);
    }

    void setTail(Node *node) {
        if (tail == NULL) {
            head = tail = node;
            return;
        }
        insertAfter(tail, node);
    }

    void insertBefore(Node *node, Node *nodeToInsert) {
        if (nodeToInsert == head && head == tail) return;
        remove(nodeToInsert);
        nodeToInsert->prev = node->prev;
        nodeToInsert->next = node;
        if (node->prev == NULL) {
            head = nodeToInsert;
        } else {
            node->prev->next = nodeToInsert;
        }
        node->prev = nodeToInsert;
    }

    void insertAfter(Node *node, Node *nodeToInsert) {
        if (nodeToInsert == head && head == tail) return;
        remove(nodeToInsert);
        nodeToInsert->prev = node;
        nodeToInsert->next = node->next;
        if (node->next == NULL) {
            tail = nodeToInsert;
        } else {
            node->next->prev = nodeToInsert;
        }
        node->next = nodeToInsert;
    }

    void insertAtPosition(int position, Node *nodeToInsert) {
        if (position == 1) {
            setHead(nodeToInsert);
            return;
        }
        Node *cur = head;
        int currentPos = 1;
        while (cur != NULL && currentPos != position) {
            currentPos++;
            cur = cur->next;
        }
        if (cur != NULL) {
            insertBefore(cur, nodeToInsert);
        } else {
            setTail(nodeToInsert);
        }
    }

    // O(n) time, O(1) space
    void removeNodesWithValue(int value) {
        Node *cur = head;
        while (cur != NULL) {
            Node *consideringNode = cur;
            cur = cur->next;
            if (consideringNode->value == value) {
                remove(consideringNode);
            }
        }
    }

    // O(1) time, O(1) space
    void remove(Node *node) {
        if (node == head)
            head = head->next;
        if (node == tail)
            tail = tail->prev;
        
        if (node->prev != NULL) {
            node->prev->next = node->next;
        }
        if (node->next != NULL) {
            node->next->prev = node->prev;
        }
        node->prev = node->next = NULL;
    }

    // O(n) time, O(1) space
    bool containsNodeWithValue(int value) {
        Node *cur = head;
        while (cur != NULL) {
            if (cur->value == value) {
                return true;
            }
            cur = cur->next;
        }
        return false;
    }
};
