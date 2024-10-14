#include <stdio.h>
#include <stdlib.h>

struct Node {
    int coefficient;
    int exponent;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int coeff, int exp) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->coefficient = coeff;
    newNode->exponent = exp;
    newNode->next = newNode;  // Circular Linked List
    return newNode;
}

// Function to insert node at the end of circular linked list
void insertNode(struct Node** head, int coeff, int exp) {
    struct Node* newNode = createNode(coeff, exp);
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

// Function to display polynomial
void displayPolynomial(struct Node* head) {
    if (head == NULL) {
        printf("0\n");
        return;
    }
    struct Node* temp = head;
    do {
        printf("%dx^%d", temp->coefficient, temp->exponent);
        temp = temp->next;
        if (temp != head) {
            printf(" + ");
        }
    } while (temp != head);
    printf("\n");
}

// Function to subtract two polynomials
struct Node* subtractPolynomials(struct Node* poly1, struct Node* poly2) {
    struct Node* result = NULL;
    struct Node* p1 = poly1;
    struct Node* p2 = poly2;

    do {
        insertNode(&result, p1->coefficient, p1->exponent);
        p1 = p1->next;
    } while (p1 != poly1);

    do {
        insertNode(&result, -p2->coefficient, p2->exponent);
        p2 = p2->next;
    } while (p2 != poly2);

    return result;
}

int main() {
    struct Node* poly1 = NULL;
    struct Node* poly2 = NULL;

    // Example polynomials
    insertNode(&poly1, 3, 3); // 3x^3
    insertNode(&poly1, 5, 2); // 5x^2
    insertNode(&poly1, 6, 0); // 6

    insertNode(&poly2, 1, 3); // 1x^3
    insertNode(&poly2, 2, 1); // 2x^1
    insertNode(&poly2, 1, 0); // 1

    printf("Polynomial 1: ");
    displayPolynomial(poly1);

    printf("Polynomial 2: ");
    displayPolynomial(poly2);

    struct Node* diff = subtractPolynomials(poly1, poly2);

    printf("Difference of Polynomials: ");
    displayPolynomial(diff);

    return 0;
}
