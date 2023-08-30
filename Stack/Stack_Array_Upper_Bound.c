#include <stdio.h>
#include <stdlib.h>

// Array implementation of stack with upper bound
/*
For our array to behave like a stack, insertion and deletion must
be performed at the end
We will have variable "top" to keep track of index of last element in array
If stack is empty, top = -1
We will assume stack_arr[0] is bottom most element of stack
*/

#define MAX 4       // Maximum number of elements in stack

// Global Declaration of the Stack
int stack_arr[MAX];
int top = -1;       // Stack iniitally empty

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
    if(top == -1) {
        return 1;
    }
    return 0;
}
int isFull() {
    if(top == MAX - 1) {
        return 1;
    }
    return 0;
}

void push(int data) {
    if(isFull()) {
        printf("Stack Overflow\n");
        return;
    }
    top = top + 1;
    stack_arr[top] = data;
}

int pop() {
    // Note that the element is not actually deleted, just the top is decremented
    if(isEmpty()) {
        printf("Stack Underflow\n");
        exit(1);
    }
    int value = stack_arr[top];
    top = top - 1;
    return value;
}

void print_stack() {
    if(isEmpty()) {
        printf("Stack Underflow\n");
        return;
    }
    int i = top;
    while (i != -1) {
        printf("%d\t", stack_arr[i]);
        i--;
    }
    printf("\n");
}
