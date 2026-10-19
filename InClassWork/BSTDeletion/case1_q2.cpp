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
// Preorder (Node, Left, Right): together with the inorder it fixes the tree's shape
void printPreorder(Node* node)
{
    if (node == nullptr) return;
    cout << node->data << " ";
    printPreorder(node->left);
    printPreorder(node->right);
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

    // Case 1: delete the root (40). It has two children.
    // 1. find the inorder successor: the smallest value in the right subtree
    Node* parent = root;
    Node* succ = root->right;                // go right once (60)
    while (succ->left != nullptr)            // then left as far as possible
    {
        parent = succ;
        succ = succ->left;                   // succ = 50, parent = 60
    }
    // 2. copy the successor's value into the root
    root->data = succ->data;                 // root now holds 50
    // 3. remove the successor node (it has no left child)
    if (parent == root)
        parent->right = succ->right;
    else
        parent->left = succ->right;          // 60->left = NULL
    delete succ;

    cout << "After:  ";
    printInorder(root);
    cout << "  (root = " << root->data << ")" << endl;
    cout << "Preorder after: ";
    printPreorder(root);
    cout << endl;

    freeTree(root);
    return 0;
}
//=============================================================================
