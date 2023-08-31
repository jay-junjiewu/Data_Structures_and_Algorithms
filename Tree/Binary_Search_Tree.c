#include <stdio.h>
#include <stdlib.h>

/*
Binary Search Tree (BST) implementation using dynamically created nodes
BST is binary tree where in internal node, 
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

int main() {
    struct node *BSTroot = NULL;   // Empty tree

    BSTroot = insert(BSTroot, 15);
    BSTroot = insert(BSTroot, 10);
    BSTroot = insert(BSTroot, 20);
    BSTroot = insert(BSTroot, 25);
    BSTroot = insert(BSTroot, 8);
    BSTroot = insert(BSTroot, 12);

    printf("%d\t", search(BSTroot, 15));
    printf("%d\t", search(BSTroot, 12));
    printf("%d\t", search(BSTroot, 19));
    printf("%d\t", search(BSTroot, 69));

    printf("\n");

    printf("%d\t", find_min(BSTroot));
    printf("%d\t", find_max(BSTroot));

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