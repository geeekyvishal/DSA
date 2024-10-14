#include <stdio.h>
#include <stdlib.h>

struct Node {
    int coefficient;
    int exponentX;
    int exponentY;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int coeff, int expX, int expY) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->coefficient = coeff;
    newNode->exponentX = expX;
    newNode->exponentY = expY;
    newNode->next = NULL;
    return newNode;
}

// Function to insert node at the end of the list
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

// Function to display 2-variable polynomial
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

// Function to add two 2-variable polynomials
struct Node* addPolynomials(struct Node* poly1, struct Node* poly2) {
    struct Node* result = NULL;
    struct Node* p1 = poly1;
    struct Node* p2 = poly2;

    while (p1 != NULL && p2 != NULL) {
        if (p1->exponentX > p2->exponentX || 
           (p1->exponentX == p2->exponentX && p1->exponentY > p2->exponentY)) {
            insertNode(&result, p1->coefficient, p1->exponentX, p1->exponentY);
            p1 = p1->next;
        } else if (p1->exponentX < p2->exponentX || 
                  (p1->exponentX == p2->exponentX && p1->exponentY < p2->exponentY)) {
            insertNode(&result, p2->coefficient, p2->exponentX, p2->exponentY);
            p2 = p2->next;
        } else {
            int sumCoeff = p1->coefficient + p2->coefficient;
            insertNode(&result, sumCoeff, p1->exponentX, p1->exponentY);
            p1 = p1->next;
            p2 = p2->next;
        }
    }

    // Remaining terms of poly1
    while (p1 != NULL) {
        insertNode(&result, p1->coefficient, p1->exponentX, p1->exponentY);
        p1 = p1->next;
    }

    // Remaining terms of poly2
    while (p2 != NULL) {
        insertNode(&result, p2->coefficient, p2->exponentX, p2->exponentY);
        p2 = p2->next;
    }

    return result;
}

int main() {
    struct Node* poly1 = NULL;
    struct Node* poly2 = NULL;

    // Example polynomials:
    // poly1: 3x^2y^1 + 2x^1y^2 + 1x^0y^0
    insertNode(&poly1, 3, 2, 1);
    insertNode(&poly1, 2, 1, 2);
    insertNode(&poly1, 1, 0, 0);

    // poly2: 1x^2y^1 + 4x^0y^0
    insertNode(&poly2, 1, 2, 1);
    insertNode(&poly2, 4, 0, 0);

    printf("Polynomial 1: ");
    displayPolynomial(poly1);

    printf("Polynomial 2: ");
    displayPolynomial(poly2);

    struct Node* sum = addPolynomials(poly1, poly2);

    printf("Sum of 2-variable Polynomials: ");
    displayPolynomial(sum);

    return 0;
}
