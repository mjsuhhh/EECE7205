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
    Node* root = nullptr;                        // empty tree

    // Q4: check for an empty tree before anything reads root->data (rule B2)
    if (root == nullptr)
    {
        cout << "the tree is empty" << endl;
        return 0;
    }

    cout << "Before: ";
    printInorder(root);
    cout << "  (root = " << root->data << ")" << endl;

    // Case 5: the key is not in the tree (delete 25).
    Node* cur = root;
    int key = 25;
    while (cur != nullptr && cur->data != key)
    {
        if (key < cur->data) cur = cur->left;    // 25 < 40: go left to 20
        else                 cur = cur->right;   // 25 > 20: go right to 30
    }                                            // 25 < 30: go left, NULL
    if (cur == nullptr)
        cout << key << " is not in the tree: nothing to delete" << endl;

    cout << "After:  ";
    printInorder(root);
    cout << "  (root = " << root->data << ")" << endl;

    freeTree(root);
    return 0;
}
//=============================================================================
