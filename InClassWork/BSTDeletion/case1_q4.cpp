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
// Usual BST insert: smaller keys go left, larger keys go right
Node* insert(Node* node, int key)
{
    if (node == nullptr) return new Node(key);
    if (key < node->data) node->left = insert(node->left, key);
    else                  node->right = insert(node->right, key);
    return node;
}
//=============================================================================
int main()
{
    // Tree P: insert 45, 25, 65, 15, 35, 55, 75, 30, 60 in that order
    int arr[] = {45, 25, 65, 15, 35, 55, 75, 30, 60};
    int n = sizeof(arr) / sizeof(arr[0]);
    Node* root = nullptr;
    for (int i = 0; i < n; i++)
        root = insert(root, arr[i]);

    cout << "Before: ";
    printInorder(root);
    cout << "  (root = " << root->data << ")" << endl;

    // Case 1, Q4: delete the root (45) of tree P. It has two children.
    // 1. find the inorder successor: the smallest value in the right subtree
    Node* parent = root;
    Node* succ = root->right;                // go right once (65)
    while (succ->left != nullptr)            // then left as far as possible
    {
        parent = succ;
        succ = succ->left;                   // succ = 55, parent = 65
    }
    // 2. copy the successor's value into the root
    root->data = succ->data;                 // root now holds 55
    // 3. remove the successor node (it has no left child)
    if (parent == root)
        parent->right = succ->right;
    else
        parent->left = succ->right;          // 65->left = 60 (B4: 55's right child moves up)
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
