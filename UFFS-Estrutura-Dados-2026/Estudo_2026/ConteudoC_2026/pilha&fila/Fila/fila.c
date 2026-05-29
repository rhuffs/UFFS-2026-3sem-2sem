#include <stdio.h>
#include <stdlib.h>

//FIFO - First in First Out
// Vetor ou Lista simplesmente encadeada


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node;

typedef struct Queue {
    Node* head;
    Node* tail;
} Queue;

Queue* newQueue() {
    Queue* queue = (Queue*) malloc(sizeof(Queue));

    queue->head = NULL;
    queue->tail = NULL;

    return queue;
}

bool isEmpty(Queue* queue) {
    return queue->head == NULL;
}

void enQueue(Queue* queue, int value) {
    Node* newNode = (Node*) malloc(sizeof(Node));

    newNode->value = value;
    newNode->next = NULL;
    
    if (isEmpty(queue)) {
        queue->head = newNode;
    } else {
        queue->tail->next = newNode;
    }
    
    queue->tail = newNode;
}

Node* deQueue(Queue* queue) {
    if (isEmpty(queue)) {
        return NULL;
    }

    Node* head = queue->head;
    queue->head = queue->head->next;

    if (queue->head == NULL) {
        queue->tail = NULL;
    }

    return head;
}

void printQueue(Queue* queue) {
    printf("Fila: ");
    for (Node* current = queue->head; current != NULL; current = current->next) {
        printf("%d ", current->value);
    }
    printf("\n");
}

void freeAll(Queue* queue) {
    while (!isEmpty(queue)) {
        free(deQueue(queue));
    }
}

int main() {
    Queue* queue = newQueue();

    enQueue(queue, 1);
    enQueue(queue, 2);
    enQueue(queue, 3);

    printQueue(queue);
    printf("\n======================\n");
    printf("Head: %d\n", queue->head->value);
    printf("Tail: %d", queue->tail->value);
    printf("\n======================\n");

    Node* aux;
    aux = deQueue(queue);
    printf("Removido: %d\n", aux->value);
    free(aux);
    aux = deQueue(queue);
    printf("Removido: %d", aux->value);
    free(aux);

    printf("\n======================\n");
    printQueue(queue);
    enQueue(queue, 4);
    printf("\n======================\n");
    printQueue(queue);
    printf("\n======================\n");
    printf("Head: %d\n", queue->head->value);
    printf("Tail: %d", queue->tail->value);

    freeAll(queue);

    return 0;
}