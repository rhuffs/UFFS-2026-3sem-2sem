#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    char value;
    struct Node* next;
} Node;

typedef struct Stack {
    Node* top;
} Stack;

Stack* newStack() {
    Stack* stack = (Stack*) malloc(sizeof(Stack));
    stack->top = NULL;
    return stack;
}

bool isEmpty(Stack* stack) {
    return stack->top == NULL;
}

void push(Stack* stack, char value) {
    Node* newNode = (Node*) malloc(sizeof(Node));

    newNode->value = value;
    newNode->next = stack->top;
    stack->top = newNode;
}

Node* pop(Stack* stack) {
    if (isEmpty(stack)) {
        return NULL;
    }

    Node* top = stack->top;
    stack->top = stack->top->next;

    return top;
}

void printStack(Stack* stack) {
    printf("Pilha:\n");
    for (Node* current = stack->top; current != NULL; current = current->next) {
        printf("%c\n", current->value);
    }
}

void freeAll(Stack* stack) {
    while (!isEmpty(stack)) {
        free(pop(stack));
    }
}

int isOpenChar(char value) {
    return value == '(' || value == '[' || value == '{';
}

int isCloseChar(char value) {
    return value == ')' || value == ']' || value == '}';
}

int isMatchingChar(char open, char close) {
    return
        open == '(' && close == ')' ||
        open == '[' && close == ']' ||
        open == '{' && close == '}';
}

int main() {
    Stack* stack = newStack();
    char* expression = "(a * 1)[{1 + 2]} = 0";
    
    int isValid = 1;
    
    for (int i = 0; expression[i] != '\0'; i++) {
        if(isOpenChar(expression[i])) { 
            push(stack, expression[i]);
        }
        
        if (isCloseChar(expression[i])) {
            isValid = isMatchingChar(pop(stack)->value, expression[i]);
            if (!isValid) {
                break;
            }
        }
    }
    
    if (isValid) {
        printf("Válido!");
    } else {
        printf("inválido!");
    }

    printf("\n======================\n");
    freeAll(stack);

    return 0;
}

//:D
// :(