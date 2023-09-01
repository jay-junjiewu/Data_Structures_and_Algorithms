#include <iostream>
#include <queue>

using namespace std;

// Note that we need to use g++ compiler for C++ file (not gcc), change it in the tasks.json file

class node {
public:
    int data;
    node *left, *right;
};

node *get_new_node(int data);
node *insert(node *root, int data);
int height(node *root);
void level_order(node *root);


int main() {
    node *BSTroot = NULL;   // Empty tree

    BSTroot = insert(BSTroot, 15);
    BSTroot = insert(BSTroot, 10);
    BSTroot = insert(BSTroot, 20);
    BSTroot = insert(BSTroot, 25);
    BSTroot = insert(BSTroot, 8);
    BSTroot = insert(BSTroot, 12);
    BSTroot = insert(BSTroot, 13);
    BSTroot = insert(BSTroot, 14);
    BSTroot = insert(BSTroot, 11);
    /*
                   15
                /      \
               10       20
             /    \        \
            8     12        25
                 /  \
                11   13
                       \
                        14
    */

    cout << height(BSTroot) << "\n";

    level_order(BSTroot);   // Using a queue

    return 0;
}

// Creates a leaf node
node *get_new_node(int data) {
    node *new_node = new node();
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

// Inserts a node in a BST
node *insert(node *root, int data) {
    if(root == NULL) {
        // Tree is empty
        root = get_new_node(data);
    } else if(data <= root->data) {
        // Insert to left of tree
        root->left = insert(root->left, data);
    } else {
        // Insert to right of tree
        root->right = insert(root->right, data);
    }
    return root;
}

// Returns the height of a binary tree
int height(node *root) {
    if(root == NULL) {
        return -1;
    }
    // Compare the left and right heights
    int left_height = height(root->left);
    int right_height = height(root->right);

    // Since height of an empty tree is -1 and height of a leaf node is 0, there is a +1 in return
    if(left_height >= right_height) {
        return left_height + 1;
    } else {
        return right_height + 1;
    }
}


// The idea is to push the root node into the Queue, print and pop nodes from the queue while
//      adding the children nodes of the popped parent node
// Time complexity is O(n) since we make are pushing each node into the queue, visiting them only once
void level_order(node *root) {
    if(root == NULL) return;

    // Creates an object from the "queue" class, containing type "node" pointer, named "Q"
    queue<node*> Q;

    // Insert root node into the queue
    Q.push(root);

    // There is at least one discovered node
    while(!Q.empty()) {
        node* current = Q.front();
        cout << current->data << " ";
        if(current->left != NULL) Q.push(current->left);
        if(current->right != NULL) Q.push(current->right);
        Q.pop();
    }
}