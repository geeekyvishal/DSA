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
    newNode->next = NULL;
    return newNode;
}

// Function to insert node at the end of singly linked list
void insertNode(struct Node** head, int coeff, int expX, int expY) {
    struct Node* newNode = createNode(coeff, expX, expY);
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
        printf("%dx^%dy^%d", temp->coefficient, temp->exponentX, temp->exponentY);
        temp = temp->next;
        if (temp != NULL) {
            printf(" + ");
        }
    }
    printf("\n");
}

// Function to multiply two 2-variable polynomials
struct Node* multiplyPolynomials(struct Node* poly1, struct Node* poly2) {
    struct Node* result = NULL;

    for (struct Node* p1 = poly1; p1 != NULL; p1 = p1->next) {
        for (struct Node* p2 = poly2; p2 != NULL; p2 = p2->next) {
            int newCoeff = p1->coefficient * p2->coefficient;
            int newExpX = p1->exponentX + p2->exponentX;
            int newExpY = p1->exponentY + p2->exponentY;
            insertNode(&result, newCoeff, newExpX, newExpY);
        }
    }

    return result;
}

int main() {
    struct Node* poly1 = NULL;
    struct Node* poly2 = NULL;

    // Example polynomials: poly1 = 3x^2y^1 + 5x^1y^2, poly2 = 2x^1y^1 + 4
    insertNode(&poly1, 3, 2, 1);
    insertNode(&poly1, 5, 1, 2);

    insertNode(&poly2, 2, 1, 1);
    insertNode(&poly2, 4, 0, 0);

    printf("Polynomial 1: ");
    displayPolynomial(poly1);

    printf("Polynomial 2: ");
    displayPolynomial(poly2);

    struct Node* product = multiplyPolynomials(poly1, poly2);

    printf("Product of 2-variable Polynomials: ");
    displayPolynomial(product);

    return 0;
}
