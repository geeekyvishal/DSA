#include <stdio.h>
#include <stdlib.h>

struct Node {
    int coefficient;
    int exponent;
    struct Node* next;
    struct Node* prev;
};

// Function to create a node
struct Node* createNode(int coeff, int exp) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->coefficient = coeff;
    newNode->exponent = exp;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Function to insert node at the end of doubly linked list
void insertNode(struct Node** head, int coeff, int exp) {
    struct Node* newNode = createNode(coeff, exp);
    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->prev = temp;
    }
}

// Function to display the polynomial
void displayPolynomial(struct Node* head) {
    if (head == NULL) {
        printf("0\n");
        return;
    }
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%dx^%d", temp->coefficient, temp->exponent);
        temp = temp->next;
        if (temp != NULL) {
            printf(" + ");
        }
    }
    printf("\n");
}

// Function to compute the derivative of a polynomial
struct Node* computeDerivative(struct Node* head) {
    struct Node* result = NULL;
    struct Node* temp = head;

    while (temp != NULL) {
        if (temp->exponent != 0) {
            int newCoeff = temp->coefficient * temp->exponent;
            int newExp = temp->exponent - 1;
            insertNode(&result, newCoeff, newExp);
        }
        temp = temp->next;
    }

    return result;
}

int main() {
    struct Node* poly = NULL;

    // Example polynomial 3x^3 + 5x^2 + 6x + 4
    insertNode(&poly, 3, 3);
    insertNode(&poly, 5, 2);
    insertNode(&poly, 6, 1);
    insertNode(&poly, 4, 0);

    printf("Original Polynomial: ");
    displayPolynomial(poly);

    struct Node* derivative = computeDerivative(poly);

    printf("Derivative of Polynomial: ");
    displayPolynomial(derivative);

    return 0;
}
