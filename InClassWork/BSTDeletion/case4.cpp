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

    // Case 4: delete a node with TWO children (20).
    // 1. search for 20
    Node* cur = root;
    int key = 20;
    while (cur != nullptr && cur->data != key)
    {
        if (key < cur->data) cur = cur->left;
        else                 cur = cur->right;
    }
    // 2. find the inorder successor: right once, then left as far as possible
    Node* parent = cur;
    Node* succ = cur->right;                 // 30
    while (succ->left != nullptr)
    {
        parent = succ;
        succ = succ->left;
    }
    // 3. copy the successor's value into the node
    cur->data = succ->data;                  // the node that held 20 now holds 30
    // 4. remove the successor node (it has no left child)
    if (parent == cur)
        parent->right = succ->right;         // 30 was cur's right child
    else
        parent->left = succ->right;
    delete succ;

    cout << "After:  ";
    printInorder(root);
    cout << "  (root = " << root->data << ")" << endl;

    freeTree(root);
    return 0;
}
//=============================================================================
