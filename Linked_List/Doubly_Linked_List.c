#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct node *insert_node(struct node *head, int n, int x);
void print_list(struct node *head);
struct node *delete_node(struct node *head, int n);
void free_list(struct node *head);

struct node *reverse_list(struct node *head);
struct node *reverse_list_recursion(struct node *head);

// Similar to single linked list with an additional pointer to the previous node
// The prev pointer points to NULL in first node
// The next pointer points to NULL in last node
struct node {
    int data;
    struct node *next;
    struct node *prev;
};

int main() {
    struct node *list = NULL;

    list = insert_node(list, 0, 691);
    list = insert_node(list, 1, 692);
    list = insert_node(list, 2, 693);
    list = insert_node(list, 3, 694);
    list = insert_node(list, 2, 699);

    print_list(list);

    //list = delete_node(list, 2);
    //print_list(list);

    //list = reverse_list(list);
    list = reverse_list_recursion(list);

    print_list(list);

    free_list(list);

    return 0;
}

// Inserts a node at the nth position in a linked list assuming n >= 0
// If n is greater than the size of the list, then insert at the end
struct node *insert_node(struct node *head, int n, int x) {
    struct node *insert = (struct node*)malloc(sizeof(struct node));
    assert(insert != NULL);
    insert->data = x;

    // List is empty, return node that is inserted
    if(head == NULL) {
        insert->prev = NULL;
        insert->next = NULL;
        return insert;
    }

    struct node *current = head;

    // Insert at beginning of list
    if(n == 0){
        insert->prev = NULL;
        insert->next = head;
        return insert;
    }

    int count = 0;
    while(current->next != NULL && count < n - 1) {
        current = current->next;
        count++;
    }
    if(current->next == NULL) {
        // Insert at end of list
        current->next = insert;
        insert->prev = current;
        insert->next = NULL;
        return head;
    } else {
        // Insert at nth position
        current->next->prev = insert;   // Only for more than 2 nodes
        insert->next = current->next;
        current->next = insert;
        insert->prev = current;
        return head;
    }
}

void print_list(struct node *head) {
    struct node *current = head;

    // If list is empty
    if(current == NULL) {
        printf("Empty List\n");
    } else {
        // More than one node
        while(current != NULL) {
            printf("%d\t", current->data);
            current = current->next;
        }
        printf("\n");
    }
}

// Delete a node at the nth position in a linked list assuming n >= 0
// If n is greater than the size of the list, then do nothing
struct node *delete_node(struct node *head, int n) {

    // List is empty, do nothing
    if(head == NULL) {
        return NULL;
    }

    struct node *current = head;

    // Delete at beginning of list
    if(n == 0){
        head = head->next;
        free(current);
        return head;
    }

    int count = 0;
    while(current->next != NULL && count < n) {
        current = current->next;
        count++;
    }
    if(current->next != NULL) {
        // Delete at nth position
        current->prev->next = current->next;
        current->next->prev = current->prev;
        free(current);
    } else if(count == n) {
        // Delete last node
        current->prev->next = NULL;
        free(current);
    }
    return head;
}

void free_list(struct node *head) {
    if (head != NULL) {
        free_list(head->next);
        free(head);
        head = NULL;
    }
}

struct node *reverse_list(struct node *head) {
    if(head == NULL || head->next == NULL) {
        return head;
    }
    // 2 or more nodes

    struct node *current = head;
    struct node *ahead = head->next;

    // First node, current at head
    current->next = NULL;
    current->prev = ahead;
    current = ahead;
    ahead = current->next;

    while(ahead != NULL) {
        current->next = current->prev;
        current->prev = ahead;
        current = ahead;
        ahead = ahead ->next;
    }

    // Last node, current at tail
    current->next = current->prev;
    current->prev = NULL;
    return current;
}

struct node *reverse_list_recursion(struct node *head) {
    // List is empty or 1 node
    if(head == NULL || head->next == NULL) {
        return head;
    }
    
    // 2 or more nodes
    struct node *tail = head; // current head will be the tail in the reversed list

    // This will reverse the sublist, and make the head reference the last node
    head = reverse_list_recursion(head->next);

    // Make tail of the sublist (tail->next) point to the new tail
    tail->next->next = tail; 

    // Make previous node of tail point to tail of sublist
    tail->prev = tail->next;

    tail->next = NULL;
    return head;
}
