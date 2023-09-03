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

int is_BST(struct node *root);

struct node *delete_node(struct node *root, int data, int mode);

struct node *get_successor(struct node *root, int data);
struct node *find_node(struct node *root, int data);


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

    printf("Min: %d\t%d\n", find_min(BSTroot)), find_max(BSTroot);

    printf("Height: %d\n", height(BSTroot));

    printf("Level Order: ");    level_order(BSTroot);    printf("\n");
    printf("Preorder: ");       preorder(BSTroot);       printf("\n");
    printf("Inorder: ");        inorder(BSTroot);        printf("\n");
    printf("Postorder: ");      postorder(BSTroot);      printf("\n");

    printf("Is BST: %d\n", is_BST(BSTroot));

    //BSTroot = delete_node(BSTroot, 15, 0); // Left Node gets shifted up if node to delete has 2 children
    //BSTroot = delete_node(BSTroot, 15, 1); // Right Node gets shifted up if node to delete has 2 children
    //printf("Level Order: ");    level_order(BSTroot);    printf("\n");

    printf("Inorder successor of 15: %d\n", get_successor(BSTroot, 15)->data);
   
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

// Determines whether a binary tree is a BST
// BT is a BST when left child <= parent, right child > parent, two subtrees are BST
// returns 1 if BT is BST
// Time complexity is O(n) since all nodes are being traveresed through once
// Alternitavely can traverse inorder and if values are nondecreasing, then BT is BST
int is_BST(struct node *root) {
    if(root == NULL) {
        printf("Empty Tree!");
        exit(1);
    }
    // Leaf Node
    if(root->left == NULL && root->right == NULL) return 1;

    if(root->left != NULL) {
        // Checks if left child node is <= parent node
        if( !(root->left->data <= root->data) ) return 0;

        // Checks if left subtree is BST
        if( !is_BST(root->left) ) return 0;
    }
    if(root->right != NULL) {
        // Checks if right child node is > parent node
        if( !(root->right->data > root->data) ) return 0;

        // Checks if right subtree is BST
        if( !is_BST(root->right) ) return 0;
    }
    return 1;
}

// When we delete a node from a BST, different situations may occur
//      node is leaf node: remains a BST if leaf node is removed
//      node has 1 child: remains a BST if we point the parent node to the child node
//      node has 2 child: 
//        mode 0: find max in left subtree, copy max into node to delete, delete duplicate from left subtree
//        mode 1: find min in right subtree, copy min into node to delete, delete duplicate from right subtree
// Worst case scenario, we have to traverse half of the tree so time complexity is O(log n)
struct node *delete_node(struct node *root, int data, int mode) {
    if(root == NULL) return NULL;
    
    // Node to delete is root
    if(data == root->data) {
        // node is leaf node
        if(root->left == NULL && root->right == NULL) {
            free(root);
            root = NULL;
            return NULL;
        }

        // node has 1 child (XOR)
        if(root->left == NULL ^ root->right == NULL) {
            struct node *to_delete = root;
            if(root->left != NULL) {
                root = root->left;
            } else {
                root = root->right;
            }
            free(to_delete);
            return root;
        }

        // node has 2 children
        if(mode == 0) {
            // Shift left child up
            int max = find_max(root->left);
            root->data = max;
            root->left = delete_node(root->left, max, mode);
            return root;
        } else {
            // Shift right child up
            int min = find_min(root->right);
            root->data = min;
            root->right = delete_node(root->right, min, mode);
            return root;
        }

    }
    // Node to delete is in left subtree
    if(data < root->data) {
        root->left = delete_node(root->left, data, mode);
        return root;
    } 
    // Node to delete is in right subtree
    if(data > root->data) {
        root->right = delete_node(root->right, data, mode);
        return root;
    }
}


// When we perform inorder traverse of BST, we get the data in ascending order, 
//   we wish to find the inorder successor of a given data in BST
//      
// Time complexity is O(log n)
struct node *get_successor(struct node *root, int data) {
    // Find the node that we want the successor of, O(log n)
    struct node *current = find_node(root, data);

    if(current == NULL) return NULL;

    // Node has right subtree: successor is the left most node (min) in right subtree
    // Time complexity of finding the minimum is O(log n)
    if(current->right != NULL) {
        current = current->right;
        while(current->left != NULL) {
            current = current->left;
        }
        return current;
    }

    // Node has no right subtree: trace the path from root to node and find the deepest ancestor 
    //    for which current node is in its left subtree
    // Time complexity of tracing the path is O(log n)
    struct node *successor = NULL;
    struct node *ancestor = root;
    while(ancestor != current) {
        if(current->data < ancestor->data) {
            successor = ancestor;
            ancestor = ancestor->left;
        } else {
            ancestor = ancestor->right;
        }
    }
    return successor;
    
}
struct node *find_node(struct node *root, int data) {
    if(root == NULL)            return NULL;   // Tree is empty
    if (root->data == data)     return root;   // Found the value

    if(data < root->data) {
        // Search to left of tree
        return find_node(root->left, data);
    } else {
        // Search to right of tree
        return find_node(root->right, data);
    }
}