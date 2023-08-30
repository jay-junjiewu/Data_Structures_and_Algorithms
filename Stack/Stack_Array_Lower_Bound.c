#include <stdio.h>
#include <stdlib.h>

// Array implementation of stack with lower bound
/*
We will assume stack_arr[0] is top most element of stack
No need for "top" to keep track of last inserted element (since it is stack_arr[0])
We do need to keep track of first inserted element "first"
*/

#define MAX 4       // Maximum number of elements in stack

// Global Declaration of the Stack
int stack_arr[MAX];
int first = -1;       // Stack iniitally empty

int isEmpty();
int isFull();
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
    if(first == -1) {
        return 1;
    }
    return 0;
}
int isFull() {
    if(first == MAX - 1) {
        return 1;
    }
    return 0;
}

void push(int data) {
    if(isFull()) {
        printf("Stack Overflow\n");
        return;
    }
    first += 1;
    for(int i = first; i > 0; i--) {
        stack_arr[i] = stack_arr[i - 1];
    }
    stack_arr[0] = data;
}

int pop() {
    if(isEmpty()) {
        printf("Stack Underflow\n");
        exit(1);
    }

    int value = stack_arr[0];
    for(int i = 0; i < first; i++) {
        stack_arr[i] = stack_arr[i + 1];
    }
    first -= 1;
    return value;
}

void print_stack() {
    if(isEmpty()) {
        printf("Stack Underflow\n");
        return;
    }
    int i = 0;
    while (i <= first) {
        printf("%d\t", stack_arr[i]);
        i++;
    }
    printf("\n");
}
