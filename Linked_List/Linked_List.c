#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct node *create_node(int x);
struct node *combine_two_lists(struct node *first, struct node *second);
void print_list(struct node *head);
void print_list_recursion(struct node *head);
void print_list_recursion_rev(struct node *head);
struct node *insert_node(struct node *head, int n, int x);
struct node *delete_node(struct node *head, int n);
void free_list(struct node *head);
struct node *reverse_list(struct node *head);
struct node *reverse_list_recursion(struct node *head);

struct node {
    int data;
    struct node *next;
};

int main() {
    struct node *list = NULL;

    list = insert_node(list, 0, 691);
    list = insert_node(list, 1, 692);
    list = insert_node(list, 2, 693);
    list = insert_node(list, 3, 694);
    list = insert_node(list, 2, 699);

    print_list(list);

    //list = delete_node(list, 3);

    //print_list(list);

    //list = reverse_list(list);
    list = reverse_list_recursion(list);

    //print_list_recursion(list);
    //printf("\n");
    //print_list_recursion_rev(list);
    //printf("\n");

    print_list(list);

    free_list(list);

    return 0;
}

struct node *create_node(int x) {
    // Casts the void pointer to a "struct node" pointer
    struct node *temp = (struct node*)malloc(sizeof(struct node));
    // Makes sure that there is enough memory in heap, malloc returns NULL when there isn't
    assert(temp != NULL);

    /*
    if(temp == NULL) {
        printf("Memory not available");
        exit(1);
    }
    */

    temp->data = x;     // (*temp).data
    temp->next = NULL;
    return temp;
}

struct node *combine_two_lists(struct node *first, struct node *second) {
    if(first == NULL) {
        // If first linked list is empty
        return second;
    } else if (second == NULL) {
        // If second linked list is empty
        return first;
    }
    struct node *current = first;

    // Moves current to last node of first list
    while(current->next != NULL) {
        current = current->next;
    }

    // Points last node of first list to head node of second list
    current->next = second;
    return first;
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

void print_list_recursion(struct node *head) {
    struct node *current = head;

    if(current != NULL) {
        printf("%d\t", current->data);
        print_list_recursion(current->next);
    }
}

void print_list_recursion_rev(struct node *head) {
    struct node *current = head;

    if(current != NULL) {
        print_list_recursion_rev(current->next);
        printf("%d\t", current->data);
    }
}

// Inserts a node at the nth position in a linked list assuming n >= 0
// If n is greater than the size of the list, then insert at the end
struct node *insert_node(struct node *head, int n, int x) {
    struct node *insert = (struct node*)malloc(sizeof(struct node));
    assert(insert != NULL);
    insert->data = x;

    // List is empty, return node that is inserted
    if(head == NULL) {
        insert->next = NULL;
        return insert;
    }

    struct node *current = head;

    // Insert at beginning of list
    if(n == 0){
        insert->next = head;
        return insert;
    }

    int count = 0;
    while(current->next != NULL && count < n - 1) {
        current = current->next;
        count++;
    }
    if(count == n - 1) {
        // Insert at nth position
        insert->next = current->next;
        current->next = insert;
    } else {
        // Position is larger than list size, insert at end
        current->next = insert;
        insert->next = NULL;
    }
    return head;
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
    while(current->next != NULL && count < n - 1) {
        current = current->next;
        count++;
    }
    if(current->next == NULL){
        return head;
    } else {
        // Delete at nth position
        struct node *temp = current->next;
        current->next = temp->next;
        free(temp);
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
    if(head == NULL) {
        return NULL;
    }
    // 1 or more nodes
    struct node *previous = NULL;
    struct node *current = head;
    struct node *temp = NULL;
    while(current != NULL) {
        temp = current->next;
        current->next = previous;
        previous = current;
        current = temp;
    }
    return previous;
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
    
    tail->next = NULL;
    return head;
}
