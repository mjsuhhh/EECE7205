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
// Usual BST insert: smaller keys go left, larger keys go right
Node* insert(Node* node, int key)
{
    if (node == nullptr) return new Node(key);
    if (key < node->data) node->left = insert(node->left, key);
    else                  node->right = insert(node->right, key);
    return node;
}
//=============================================================================
// Height in edges: an empty tree has height -1, a single node has height 0
int height(Node* node)
{
    if (node == nullptr) return -1;
    int hl = height(node->left);
    int hr = height(node->right);
    return 1 + (hl > hr ? hl : hr);
}
//=============================================================================
// Case 2 search and unlink, counting one key comparison per node visited
Node* deleteLeaf(Node* root, int key, int& comparisons)
{
    Node* parent = nullptr;
    Node* cur = root;
    comparisons = 0;
    while (cur != nullptr)
    {
        comparisons++;                       // compare key with cur->data
        if (key == cur->data) break;
        parent = cur;
        if (key < cur->data) cur = cur->left;
        else                 cur = cur->right;
    }
    if (parent->left == cur) parent->left = nullptr;
    else                     parent->right = nullptr;
    delete cur;
    return root;
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

    // Chain: insert 10, 20, 30, 40, 50, 60, 70 in that order
    int arr[] = {10, 20, 30, 40, 50, 60, 70};
    int n = sizeof(arr) / sizeof(arr[0]);
    Node* chain = nullptr;
    for (int i = 0; i < n; i++)
        chain = insert(chain, arr[i]);

    int count;
    int h = height(root);
    cout << "Tree T: h = " << h << endl;
    cout << "Before: ";
    printInorder(root);
    cout << "  (root = " << root->data << ")" << endl;
    root = deleteLeaf(root, 70, count);
    cout << "After:  ";
    printInorder(root);
    cout << "  (root = " << root->data << ")" << endl;
    cout << "Deleting leaf 70: " << count << " comparisons (h + 1 = " << h + 1 << ")" << endl;
    cout << endl;

    h = height(chain);
    cout << "Chain:  h = " << h << endl;
    cout << "Before: ";
    printInorder(chain);
    cout << "  (root = " << chain->data << ")" << endl;
    chain = deleteLeaf(chain, 70, count);
    cout << "After:  ";
    printInorder(chain);
    cout << "  (root = " << chain->data << ")" << endl;
    cout << "Deleting leaf 70: " << count << " comparisons (h + 1 = " << h + 1 << ")" << endl;

    freeTree(root);
    freeTree(chain);
    return 0;
}
//=============================================================================
