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

    // Case 4, Q4: delete 25 from tree P using the inorder PREDECESSOR.
    // 1. search for 25
    Node* cur = root;
    int key = 25;
    while (cur != nullptr && cur->data != key)
    {
        if (key < cur->data) cur = cur->left;
        else                 cur = cur->right;
    }
    // 2. find the inorder predecessor: left once, then right as far as possible
    Node* parent = cur;
    Node* pred = cur->left;                  // 15
    while (pred->right != nullptr)
    {
        parent = pred;
        pred = pred->right;
    }
    // 3. copy the predecessor's value into the node
    cur->data = pred->data;                  // the node that held 25 now holds 15
    // 4. remove the predecessor node (it has no right child)
    if (parent == cur)
        parent->left = pred->left;           // 15 was cur's left child: 25-node->left = NULL
    else
        parent->right = pred->left;
    delete pred;

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
