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

    // Case 4, Q3: delete 25 (two children) from tree P.
    // 1. search for 25
    Node* cur = root;
    int key = 25;
    while (cur != nullptr && cur->data != key)
    {
        if (key < cur->data) cur = cur->left;
        else                 cur = cur->right;
    }
    // 2. find the inorder successor: right once, then left as far as possible
    Node* parent = cur;
    Node* succ = cur->right;                 // 35, then left to 30
    while (succ->left != nullptr)
    {
        parent = succ;
        succ = succ->left;
    }
    // 3. copy the successor's value into the node
    cur->data = succ->data;                  // the node that held 25 now holds 30
    // 4. remove the successor node (it has no left child)
    if (parent == cur)
        parent->right = succ->right;
    else
        parent->left = succ->right;          // 35->left = NULL (30 has no right child)
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
