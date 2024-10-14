#include <stdio.h>
#include <stdlib.h>

struct Node {
    int coefficient;
    int exponent;
    struct Node* next;
    struct Node* prev;
};

// Function to create a new node
struct Node* createNode(int coeff, int exp) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->coefficient = coeff;
    newNode->exponent = exp;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Function to insert a node at the end of the list
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

// Function to add two polynomials
struct Node* addPolynomials(struct Node* poly1, struct Node* poly2) {
    struct Node* result = NULL;
    struct Node* p1 = poly1;
    struct Node* p2 = poly2;

    while (p1 != NULL && p2 != NULL) {
        if (p1->exponent > p2->exponent) {
            insertNode(&result, p1->coefficient, p1->exponent);
            p1 = p1->next;
        } else if (p1->exponent < p2->exponent) {
            insertNode(&result, p2->coefficient, p2->exponent);
            p2 = p2->next;
        } else {
            int sumCoeff = p1->coefficient + p2->coefficient;
            insertNode(&result, sumCoeff, p1->exponent);
            p1 = p1->next;
            p2 = p2->next;
        }
    }

    // If remaining terms in poly1
    while (p1 != NULL) {
        insertNode(&result, p1->coefficient, p1->exponent);
        p1 = p1->next;
    }

    // If remaining terms in poly2
    while (p2 != NULL) {
        insertNode(&result, p2->coefficient, p2->exponent);
        p2 = p2->next;
    }

    return result;
}

int main() {
    struct Node* poly1 = NULL;
    struct Node* poly2 = NULL;

    // Example polynomial 1: 3x^3 + 5x^2 + 6
    insertNode(&poly1, 3, 3);
    insertNode(&poly1, 5, 2);
    insertNode(&poly1, 6, 0);

    // Example polynomial 2: 6x^2 + 8x + 2
    insertNode(&poly2, 6, 2);
    insertNode(&poly2, 8, 1);
    insertNode(&poly2, 2, 0);

    printf("Polynomial 1: ");
    displayPolynomial(poly1);
    
    printf("Polynomial 2: ");
    displayPolynomial(poly2);

    struct Node* sum = addPolynomials(poly1, poly2);

    printf("Sum of Polynomials: ");
    displayPolynomial(sum);

    return 0;
}
