#include <stdio.h>
#include <stdlib.h>

// Linked List implementation of stack
/*
Can be used when size of stack is unknown in advance
Head of the list is used as the top of the stack since push and pop is O(1)
If end of the list is used as top of the stack, then push pop is O(n)
Stack Overflow is when there is no space to dynamically allocate memory (malloc return NULL)
Stack Underflow is when top of stack is NULL
*/

struct node {
    int data;
    struct node *next;
};

struct node *top = NULL;

int isEmpty();
void push(int data);
int pop();
void print_stack();


int main() {
    int data;

    push(1);
    push(2);
    data = pop();
    push(3);
    push(4);
    push(5);
    push(6);

    print_stack();

    return 0;
}

int isEmpty() {
    if(top == NULL) {
        return 1;
    }
    return 0;
}

void push(int data) {
    struct node *new_node = (struct node*)malloc(sizeof(struct node));

    if(new_node == NULL) {
        printf("Stack Overflow\n");
        exit(1);
    }
    new_node->data = data;
    new_node->next = top;
    top = new_node;
}

int pop() {
    if(isEmpty()) {
        printf("Stack Underflow\n");
        exit(1);
    }
    int value = top->data;
    struct node *to_delete = top;
    top = top->next;
    free(to_delete);
    return value;
}

void print_stack() {
    if(isEmpty()) {
        printf("Stack Underflow\n");
        exit(1);
    }
    struct node *current = top;
    while(current != NULL) {
        printf("%d\t", current->data);
        current = current->next;
    }
    printf("\n");
}
