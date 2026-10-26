#include <iostream>
#include <string>
using namespace std;

//=============================================================================
class Node
{
public:
    int data;
    Node* left;
    Node* right;

    Node(int value)
    {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};
//=============================================================================
// Inorder (Left, Node, Right) prints a BST in sorted order
void printInorder(Node* node)
{
    if (node == nullptr) return;
    printInorder(node->left);
    cout << node->data << " ";
    printInorder(node->right);
}
//=============================================================================
// Free every node (postorder: children before parent)
void freeTree(Node* node)
{
    if (node == nullptr) return;
    freeTree(node->left);
    freeTree(node->right);
    delete node;
}
//=============================================================================
int main()
{
    // Tree T
    Node* root = new Node(40);
    root->left = new Node(20);
    root->right = new Node(60);
    root->left->left = new Node(10);
    root->left->right = new Node(30);
    root->right->left = new Node(50);
    root->right->right = new Node(70);

    cout << "Before: ";
    printInorder(root);
    cout << "  (root = " << root->data << ")" << endl;

    // Case 2, Q2: delete the leaf 70.
    // 1. search for 70, remembering its parent
    Node* parent = nullptr;
    Node* cur = root;
    int key = 70;
    while (cur != nullptr && cur->data != key)
    {
        parent = cur;
        if (key < cur->data) cur = cur->left;
        else                 cur = cur->right;
    }
    // 2. unlink it from its parent (60) and free it
    if (parent->left == cur) parent->left = nullptr;
    else                     parent->right = nullptr;
    delete cur;

    cout << "After:  ";
    printInorder(root);
    cout << "  (root = " << root->data << ")" << endl;

    freeTree(root);
    return 0;
}
//=============================================================================
