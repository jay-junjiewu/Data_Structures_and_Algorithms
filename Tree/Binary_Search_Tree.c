#include <stdio.h>
#include <stdlib.h>

/*
Binary Tree (BT) implementation using dynamically created nodes
Binary Search Tree (BST) is binary tree where in internal node, 
    value of all nodes in left subtree is <= internal node and all nodes in right subtree > internal node
*/

struct node {
    int data;
    struct node *left;
    struct node *right;
};

struct node *get_new_node(int data);
struct node *insert(struct node *root, int data);

int search(struct node *root, int data);
int find_min(struct node *root);
int find_max(struct node *root);
int height(struct node *root);

void level_order(struct node *root);
void print_current_level(struct node *root, int levels_to_go);

void preorder(struct node *root);
void inorder(struct node *root);
void postorder(struct node *root);



int main() {
    struct node *BSTroot = NULL;   // Empty tree

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

    printf("%d\t", search(BSTroot, 15));
    printf("%d\t", search(BSTroot, 12));
    printf("%d\t", search(BSTroot, 19));
    printf("%d\t", search(BSTroot, 69));
    printf("\n");

    printf("Min: %d\t", find_min(BSTroot));
    printf("Max: %d\t", find_max(BSTroot));              printf("\n");

    printf("Height: %d\t", height(BSTroot));             printf("\n");

    printf("Level Order: ");    level_order(BSTroot);    printf("\n");
    printf("Preorder: ");       preorder(BSTroot);       printf("\n");
    printf("Inorder: ");        inorder(BSTroot);        printf("\n");
    printf("Postorder: ");      postorder(BSTroot);      printf("\n");
   
    return 0;
}


// Creates a leaf node
struct node *get_new_node(int data) {
    struct node *new_node = (struct node*)malloc(sizeof(struct node));
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

// Inserts a node in a BST
// Time complexity is O(log n) since we only traverse through one subtree out of the two recursively
struct node *insert(struct node *root, int data) {
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

// Searches for a value in a BST
// Time complexity is O(log n) since search space is n -> n/2 -> n/4 ->...-> 1 with max steps k=log(n)
int search(struct node *root, int data) {
    if(root == NULL)            return 0;   // Tree is empty
    if (root->data == data)     return 1;   // Found the value

    if(data < root->data) {
        // Search to left of tree
        return search(root->left, data);
    } else {
        // Search to right of tree
        return search(root->right, data);
    }
}

// Finds the minimum value in a BST (iterative approach)
// Time complexity is O(log n)
int find_min(struct node *root) {
    if(root == NULL) {
        // Tree is empty
        printf("Error: Tree is empty");
        exit(1);
    }
    // root is a local vaiable, do not need current
    /*
    struct node *current = root;
    while(current->left != NULL) {
        current = current->left;
    }
    return current->data;
    */
    while(root->left != NULL) {
        root = root->left;
    }
    return root->data;
}

// Finds the maximum value in a BST (recursive approach)
// Time complexity is O(log n)
int find_max(struct node *root) {
    if(root == NULL) {
        // Tree is empty
        printf("Error: Tree is empty");
        exit(1);
    }
    if(root->right == NULL) {
        return root->data;
    }
    return find_max(root->right); 
}

// Returns the height of a BT
// Time complexity is O(n) since we make a recursive call to each node in the BT, visiting each node once
int height(struct node *root) {
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

// Breadth-first/Level-order BT traversal: visiting all nodes at same level first before moving on to next level

// Depth-first BT traversal: visiting the whole subtree of a child node before moving to the next child node
//      Preorder traversal:     root, left, right   DLR
//      Inorder traversal:      left, root, right   LDR     gives a sorted list in BST
//      Postorder traversal:    left, right, root   LRD


// The idea is to first find the height of the tree, then for each level, print the nodes at that level
//      Printing the nodes at each level can be done using a recursive function that branches from root
//      "levels_to_go" time to reach the intended level and print all the nodes at that level
// Time complexity is O(n*log n)....not good
//      for loop is O(log n) since height function is O(log n)
//      print_current_level is O(n) since we are branching down, each node being visited only once
// A better algorithm is using queues, implemented in C++ to use the queue library ;)
void level_order(struct node *root) {
    if(root == NULL) return;

    int h = height(root);
    for(int i = 0; i <= h; i++) {
        print_current_level(root, i);
    }
}
void print_current_level(struct node *parent, int levels_to_go) {
    if(parent == NULL) return;

    if(levels_to_go == 0) {
        printf("%d ", parent->data);
    }
    // Branch down to child node is levels_to_go is > 0
    print_current_level(parent->left, levels_to_go - 1);
    print_current_level(parent->right, levels_to_go - 1);
}

// Time complexity of below 3 algorithms is O(n) since each node is only visited once
void preorder(struct node *root) {
    if(root == NULL) return;
    printf("%d ", root->data);  // D
    preorder(root->left);       // L
    preorder(root->right);      // R
}
void inorder(struct node *root) {
    if(root == NULL) return;
    inorder(root->left);        // L
    printf("%d ", root->data);  // D
    inorder(root->right);       // R
}
void postorder(struct node *root) {
    if(root == NULL) return;
    postorder(root->left);      // L
    postorder(root->right);     // R
    printf("%d ", root->data);  // D
}
