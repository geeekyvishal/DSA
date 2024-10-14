#include <stdio.h>
#include <stdlib.h>

struct Node {
    int coefficient;
    int exponent;
    struct Node* next;
};

// Function to create a node
struct Node* createNode(int coeff, int exp) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->coefficient = coeff;
    newNode->exponent = exp;
    newNode->next = NULL;
    return newNode;
}

// Function to insert node at the end of singly linked list
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

// Function to compute the integration of a polynomial
struct Node* computeIntegration(struct Node* head) {
    struct Node* result = NULL;
    struct Node* temp = head;

    while (temp != NULL) {
        int newCoeff = temp->coefficient / (temp->exponent + 1);
        int newExp = temp->exponent + 1;
        insertNode(&result, newCoeff, newExp);
        temp = temp->next;
    }

    return result;
}

int main() {
    struct Node* poly = NULL;

    // Example polynomial 3x^2 + 5x + 6
    insertNode(&poly, 3, 2);
    insertNode(&poly, 5, 1);
    insertNode(&poly, 6, 0);

    printf("Original Polynomial: ");
    displayPolynomial(poly);

    struct Node* integral = computeIntegration(poly);

    printf("Integration of Polynomial: ");
    displayPolynomial(integral);

    return 0;
}
