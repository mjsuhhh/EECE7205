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
    // Insert 10, 20, 30 in that order: 10 -> right 20 -> right 30
    int arr[] = {10, 20, 30};
    int n = sizeof(arr) / sizeof(arr[0]);
    Node* root = nullptr;
    for (int i = 0; i < n; i++)
        root = insert(root, arr[i]);

    cout << "Before: ";
    printInorder(root);
    cout << "  (root = " << root->data << ")" << endl;

    // Case 3, Q4: delete the root 10, which has one child (20).
    // 1. search for 10, remembering its parent
    Node* parent = nullptr;
    Node* cur = root;
    int key = 10;
    while (cur != nullptr && cur->data != key)
    {
        parent = cur;
        if (key < cur->data) cur = cur->left;
        else                 cur = cur->right;
    }
    // 2. its only child takes its place
    Node* child = (cur->left != nullptr) ? cur->left : cur->right;   // 20
    if (parent == nullptr)        root = child;                      // B6: the root pointer changes
    else if (parent->left == cur) parent->left = child;
    else                          parent->right = child;
    delete cur;

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
