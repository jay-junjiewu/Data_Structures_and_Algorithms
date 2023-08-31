#include <stdio.h>
#include <stdlib.h>

// Linked List implementation of queue
/*
We will use a linked list implementation for a queue with front 
and rear pointers (to achieve O(1) for enqueue and dequeue)

Alternatively, we can use circular linked list with only a rear pointer
*/

struct node {
    int data;
    struct node *next;
};

// Global Declaration of the Queue
struct node *front = NULL;
struct node *rear = NULL;

int isEmpty();
int isFull();
void enqueue(int data);
int dequeue();
void print_queue();


int main() {
    int data;
    enqueue(1);
    enqueue(2);
    data = dequeue();
    enqueue(3);
    enqueue(4);
    enqueue(5);
    enqueue(6);

    print_queue();

    return 0;
}

int isEmpty() {
    if(front == NULL && rear == NULL) {
        return 1;
    }
    return 0;
}

void enqueue(int data) {
    struct node *new_node = (struct node*)malloc(sizeof(struct node));

    if(new_node == NULL) {
        printf("Queue is Full\n");
        exit(1);
    }

    new_node->data = data;
    new_node->next = NULL;

    if(isEmpty()) {
        front = new_node;
        rear = new_node;
    } else {
        rear->next = new_node;
        rear = new_node;
    }
}

int dequeue() {
    if(isEmpty()) {
        printf("Queue is Empty\n");
        exit(1);
    }
    int value; // Store the element that is removed to be returned
    if(front == rear) {
        // Queue has only one element, make queue empty
        value = front->data;
        free(front);
        front = NULL;
        rear = NULL;
        return value;
    }
    struct node *to_free = front;
    front = front->next;
    free(to_free);
    return value;
}

void print_queue() {
    if(isEmpty()) {
        printf("Queue is Empty\n");
        return;
    }
    // Print all elements
    struct node* current = front;
    while(current != NULL) {
        printf("%d\t", current->data);
        current = current->next;
    }
    printf("\n");
}
