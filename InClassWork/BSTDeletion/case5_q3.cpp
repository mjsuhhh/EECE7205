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

    // Case 5, Q3: if the key is not found, insert it at the NULL link where the search stopped
    Node* parent = nullptr;                      // remember the parent this time
    Node* cur = root;
    int key = 25;
    while (cur != nullptr && cur->data != key)
    {
        parent = cur;
        if (key < cur->data) cur = cur->left;    // 25 < 40: go left to 20
        else                 cur = cur->right;   // 25 > 20: go right to 30
    }                                            // 25 < 30: go left, NULL
    if (cur == nullptr)
    {
        Node* newNode = new Node(key);
        if (parent == nullptr)
        {
            root = newNode;                      // empty tree: the new node is the root
            cout << key << " is not in the tree: it becomes the root" << endl;
        }
        else if (key < parent->data)
        {
            parent->left = newNode;              // 30->left = 25
            cout << key << " is not in the tree: inserted at " << parent->data << "->left" << endl;
        }
        else
        {
            parent->right = newNode;
            cout << key << " is not in the tree: inserted at " << parent->data << "->right" << endl;
        }
    }

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
