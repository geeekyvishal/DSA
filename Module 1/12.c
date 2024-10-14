#include <stdio.h>
#include <stdlib.h>

struct Node {
    int coefficient;
    int exponentX;
    int exponentY;
    struct Node* next;
};

// Function to create a node
struct Node* createNode(int coeff, int expX, int expY) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->coefficient = coeff;
    newNode->exponentX = expX;
    newNode->exponentY = expY;
    newNode->next = newNode;  // Circular Linked List
    return newNode;
}

// Function to insert node at the end of circular linked list
void insertNode(struct Node** head, int coeff, int expX, int expY) {
    struct Node* newNode = createNode(coeff, expX, expY);
    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Node* temp = *head;
        while (temp->next != *head) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->next = *head;
    }
}

// Function to display the polynomial
void displayPolynomial(struct Node* head) {
    if (head == NULL) {
        printf("0\n");
        return;
    }
    struct Node* temp = head;
    do {
        printf("%dx^%dy^%d", temp->coefficient, temp->exponentX, temp->exponentY);
        temp = temp->next;
        if (temp != head) {
            printf(" + ");
        }
    } while (temp != head);
    printf("\n");
}

// Function to compute partial derivative with respect to x
struct Node* partialDerivativeX(struct Node* head) {
    struct Node* result = NULL;
    struct Node* temp = head;

    do {
        if (temp->exponentX != 0) {
            int newCoeff = temp->coefficient * temp->exponentX;
            int newExpX = temp->exponentX - 1;
            insertNode(&result, newCoeff, newExpX, temp->exponentY);
        }
        temp = temp->next;
    } while (temp != head);

    return result;
}

// Function to compute partial derivative with respect to y
struct Node* partialDerivativeY(struct Node* head) {
    struct Node* result = NULL;
    struct Node* temp = head;

    do {
        if (temp->exponentY != 0) {
            int newCoeff = temp->coefficient * temp->exponentY;
            int newExpY = temp->exponentY - 1;
            insertNode(&result, newCoeff, temp->exponentX, newExpY);
        }
        temp = temp->next;
    } while (temp != head);

    return result;
}

int main() {
    struct Node* poly = NULL;

    // Example polynomial 3x^2y^1 + 4x^1y^2 + 5x^2y^2
    insertNode(&poly, 3, 2, 1);
    insertNode(&poly, 4, 1, 2);
    insertNode(&poly, 5, 2, 2);

    printf("Original Polynomial: ");
    displayPolynomial(poly);

    struct Node* derivativeX = partialDerivativeX(poly);
    struct Node* derivativeY = partialDerivativeY(poly);

    printf("Partial Derivative with respect to x: ");
    displayPolynomial(derivativeX);

    printf("Partial Derivative with respect to y: ");
    displayPolynomial(derivativeY);

    return 0;
}
