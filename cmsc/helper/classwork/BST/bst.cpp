#include "bst.h"

BST::~BST(){
    clear(m_root);
}
void BST::clear(Node* aNode){
    if (aNode != nullptr){
        clear(aNode->m_left);
        clear(aNode->m_right);
        aNode->m_value = "";
        delete aNode;
        aNode = nullptr;
    }
}

void BST::dump(){
    inOrder(m_root);
}
void BST::insert(const string& element){
    insert(element, m_root);
}
void BST::insert(const string& element, Node*& aNode){
    if (aNode == nullptr){
        Node* newNode = new Node(element);
        aNode = newNode;
    }
    else if (element < aNode->m_value)
    {
        insert(element, aNode->m_left);
    }
    else{//element > aNode->m_value
        insert(element, aNode->m_right);
    }
}
void BST::inOrder(Node* aNode){
    if (aNode != nullptr){
        inOrder(aNode->m_left);
        cout << aNode->m_value << " ";
        inOrder(aNode->m_right);
    }
}
bool BST::empty(){
    return (m_root == nullptr);
}
Node* BST::findMin(){
    return findMin(m_root);
}
Node* BST::findMin(Node* aNode){
    if (aNode == nullptr || aNode->m_left == nullptr){
        return aNode;
    }
    else{
        return findMin(aNode->m_left);
    }
}
Node* BST::find(const string& element){
    return find(m_root, element);
}
Node* BST::find(Node* aNode, const string& element){
    if (aNode == nullptr || aNode->m_value == element)
    {
        return aNode;
    }
    else if (element < aNode->m_value)
        return find(aNode->m_left, element);
    else
        return find(aNode->m_right, element);
}
void BST::remove(const string& element){
    m_root = remove(m_root, element);
}
Node* BST::remove(Node* aNode, const string& element){
    if (aNode == nullptr) return aNode;//the case node not found
    else if (element < aNode->m_value)//the case to move left
        aNode->m_left = remove(aNode->m_left, element);
    else if (element > aNode->m_value)//the case to move right
        aNode->m_right = remove(aNode->m_right, element);
    else if (aNode->m_left != nullptr && aNode->m_right != nullptr){
        //the case of node with two children
        Node* temp = findMin(aNode->m_right);
        aNode->m_value = temp->m_value;
        aNode->m_right = remove(aNode->m_right, aNode->m_value);
    }
    else{
        //the case of node with one child or no children at all
        Node* temp = aNode;
        if (aNode->m_left == nullptr)
            aNode = aNode->m_right;
        else
            aNode = aNode->m_left;
        delete temp;
    }
    return aNode;
}

