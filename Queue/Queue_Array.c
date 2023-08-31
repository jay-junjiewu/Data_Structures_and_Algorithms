#include <stdio.h>
#include <stdlib.h>

// Array implementation of queue
/*
We will use a circular array implementation for a queue (avoid problems when front == MAX-1)
Index of head will be front and index of tail will be rear
We will assume front is to the left and rear is to the right (when it is not wrapped around)
To insert or delete elements, we can increment front or rear (with wrap around)
*/

#define MAX 5       // Maximum number of elements in queue

// Global Declaration of the Queue
int queue_arr[MAX];
int front = -1;       // Queue iniitally empty
int rear = -1;

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
    if(front == -1 && rear == -1) {
        return 1;
    }
    return 0;
}
int isFull() {
    if( ((rear + 1) % MAX) == front) {
        // Next element of rear == front
        return 1;
    }
    return 0;
}

void enqueue(int data) {
    if(isFull()) {
        printf("Queue is Full\n");
        exit(1);
    }
    if(isEmpty()) {
        front = 0;
        rear = 0;
        queue_arr[0] = data;
        return;
    }

    // Increment rear, with wrap around (next element)
    rear = (rear + 1) % MAX;
    queue_arr[rear] = data;
    return;
}

int dequeue() {
    if(isEmpty()) {
        printf("Queue is Empty\n");
        exit(1);
    }
    int value; // Store the element that is removed to be returned
    if(front == rear) {
        // Queue has only one element, make queue empty
        value = queue_arr[front];
        front = -1;
        rear = -1;
        return value;
    }
    value = queue_arr[front];

    // Increment front, with wrap around (next element)
    front = (front + 1) % MAX;
    return value;
}

void print_queue() {
    if(isEmpty()) {
        printf("Queue is Empty\n");
        return;
    }
    // Print all elements except last one
    for(int i = front; i != rear; i = (i + 1) % MAX) {
        printf("%d\t", queue_arr[i]);
    }
    // Print last element (works even if queue only has one element)
    printf("%d\t", queue_arr[rear]);
    printf("\n");
}
