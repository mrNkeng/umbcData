#ifndef BST_H
#define BST_H
#include <iostream>
#include <string>
using namespace std;

class Node{
    private:
    string  m_value;
    Node*   m_left;
    Node*   m_right;
    Node(const string& v) : m_value(v), 
        m_left(nullptr), m_right(nullptr) { }
    friend class BST;
};
class BST{
    public:
    BST():m_root(nullptr){};
    ~BST();
    void insert(const string& element);
    void remove(const string& element);
    void dump();
    Node* find(const string& element);
    Node* findMin();
    private:
    Node* m_root;
    void insert(const string& element, Node*& aNode);
    Node* remove(Node* aNode, const string& element);
    Node* findMin(Node* aNode);
    void inOrder(Node* aNode);
    void clear(Node* aNode);
    bool empty();
    Node* find(Node* aNode, const string& element);
};
#endif