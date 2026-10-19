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
// Delete key from the BST and return the (possibly new) root
Node* deleteNode(Node* root, int key)
{
    // B1: search for the key, remembering its parent
    Node* parent = nullptr;
    Node* cur = root;
    while (cur != nullptr && cur->data != key)
    {
        parent = cur;
        if (key < cur->data) cur = cur->left;
        else                 cur = cur->right;
    }

    // B2: not found (this also covers the empty tree)
    if (cur == nullptr)
    {
        cout << key << " is not in the tree: nothing to delete" << endl;
        return root;
    }

    // B5: two children -> copy the inorder successor, then delete the successor node instead
    if (cur->left != nullptr && cur->right != nullptr)
    {
        Node* succParent = cur;
        Node* succ = cur->right;
        while (succ->left != nullptr)
        {
            succParent = succ;
            succ = succ->left;
        }
        cur->data = succ->data;
        parent = succParent;                 // from here on, remove succ (it has no left child)
        cur = succ;
    }

    // B3 / B4: cur now has at most one child, which takes its place (NULL for a leaf)
    Node* child = (cur->left != nullptr) ? cur->left : cur->right;
    if (parent == nullptr)        root = child;         // B6: the root pointer itself changes
    else if (parent->left == cur) parent->left = child;
    else                          parent->right = child;
    delete cur;
    return root;
}
//=============================================================================
// Print the inorder traversal and the root, or say that the tree is empty
void show(string label, Node* root)
{
    cout << label;
    if (root == nullptr)
    {
        cout << "(empty)" << endl;
        return;
    }
    printInorder(root);
    cout << "  (root = " << root->data << ")" << endl;
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

    show("Start:      ", root);
    int keys[] = {40, 10, 60, 25};
    for (int i = 0; i < 4; i++)
    {
        root = deleteNode(root, keys[i]);
        show("Delete " + to_string(keys[i]) + ":  ", root);
    }
    freeTree(root);

    // Extra checks: a root with one child, a single-node root, and an empty tree
    cout << endl;
    Node* chain = nullptr;
    chain = insert(chain, 10);
    chain = insert(chain, 20);
    chain = insert(chain, 30);
    show("Chain:      ", chain);
    int more[] = {10, 20, 30, 30};
    for (int i = 0; i < 4; i++)
    {
        chain = deleteNode(chain, more[i]);
        show("Delete " + to_string(more[i]) + ":  ", chain);
    }
    freeTree(chain);
    return 0;
}
//=============================================================================
