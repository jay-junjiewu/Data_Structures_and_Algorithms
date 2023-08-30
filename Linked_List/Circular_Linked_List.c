#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*
In circular linked list, we use tail pointer instead of head pointer
This eliminates the need of traversing throught the entire list to
insert a node at beginning or end of list
*/
struct node {
    int data;
    struct node *next;
};

void print_list(struct node *tail);
struct node *insert_node(struct node *tail, int n, int x);
struct node *delete_node(struct node *tail, int n);
void free_list(struct node *tail);

int main() {
    struct node *list = NULL;

    list = insert_node(list, 0, 691);
    list = insert_node(list, 1, 692);
    list = insert_node(list, 2, 693);
    list = insert_node(list, 3, 694);
    list = insert_node(list, 2, 699);

    print_list(list);

    list = delete_node(list, 6);

    print_list(list);

    free_list(list);

    return 0;
}

// Inserts a node at the nth position in a linked list assuming n >= 0
// If n is greater than the size of the list, then it "wraps around" and inserts
struct node *insert_node(struct node *tail, int n, int x) {
    struct node *insert = (struct node*)malloc(sizeof(struct node));
    assert(insert != NULL);
    insert->data = x;

    // List is empty, return node that is inserted
    if(tail == NULL) {
        insert->next = insert;
        return insert;
    }

    struct node *current = tail;

    int count = 0;
    while(count < n) {
        current = current->next;
        count++;
    }
    // Insert at nth position
    insert->next = current->next;
    current->next = insert;

    // If insert at the tail of the list, need to update tail pointer
    if(current == tail) {
        tail = insert;
    }
    return tail;
}

void print_list(struct node *tail) {
    if(tail == NULL) {
        // If list is empty
        printf("Empty List");
    } else if(tail->next == tail){
        // If list has 1 node
        printf("%d\t", tail->data);
    } else {
        // 2 or more nodes
        struct node *current = tail->next;
        while(current != tail) {
            printf("%d\t", current->data);
            current = current->next;
        }
        printf("%d\t", current->data);  // print the tail
    }
    printf("\n");
}

// Delete a node at the nth position in a linked list assuming n >= 0
// If n is greater than the size of the list, then it wraps around
struct node *delete_node(struct node *tail, int n) {

    // List is empty, do nothing
    if(tail == NULL) {
        return NULL;
    }

    struct node *current = tail;

    int count = 0;
    while(count < n) {
        current = current->next;
        count++;
    }
    // Delete at nth position
    struct node *to_delete = current->next;
    current->next = to_delete->next;

    // If delete at the tail of the list, need to update tail pointer
    if(to_delete == tail) {
        tail = current;
    }
    free(to_delete);
    return tail;
}

void free_list(struct node *tail) {
    // Empty list
    if(tail == NULL) {
        return;
    }
    if(tail->next == tail) {
        // One node
        free(tail);
        tail = NULL;
        return;
    }
    // Breaks the circular linked list into a regular one
    struct node *head = tail->next;
    tail->next = NULL;

    if (head != NULL) {
        free_list(head->next);
        free(head);
        head = NULL;
    }
}