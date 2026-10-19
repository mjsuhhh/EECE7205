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

    // Case 5, Q2: trace the search for 25, 5, 45 and 75, counting comparisons
    int keys[] = {25, 5, 45, 75};
    for (int k = 0; k < 4; k++)
    {
        int key = keys[k];
        Node* parent = nullptr;
        Node* cur = root;
        int comparisons = 0;
        cout << key << ": ";
        while (cur != nullptr && cur->data != key)
        {
            comparisons++;
            parent = cur;
            if (key < cur->data) { cout << cur->data << " L, "; cur = cur->left; }
            else                 { cout << cur->data << " R, "; cur = cur->right; }
        }
        if (cur == nullptr)
            cout << "NULL -> " << comparisons << " comparisons, stops at " << parent->data
                 << (key < parent->data ? "->left" : "->right") << endl;
    }

    cout << "After:  ";
    printInorder(root);
    cout << "  (root = " << root->data << ")" << endl;

    freeTree(root);
    return 0;
}
//=============================================================================
