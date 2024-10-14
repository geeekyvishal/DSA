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

// Function to remove all terms with even exponents
struct Node* removeEvenExponents(struct Node* head) {
    struct Node* temp = head;

    while (temp != NULL) {
        if (temp->exponent % 2 == 0) {
            if (temp == head) {
                head = temp->next;
                if (head != NULL) {
                    head->prev = NULL;
                }
            } else {
                temp->prev->next = temp->next;
                if (temp->next != NULL) {
                    temp->next->prev = temp->prev;
                }
            }
            struct Node* toDelete = temp;
            temp = temp->next;
            free(toDelete);
        } else {
            temp = temp->next;
        }
    }
    return head;
}

int main() {
    struct Node* poly = NULL;

    // Example polynomial 3x^3 + 4x^2 + 5x + 6
    insertNode(&poly, 3, 3);
    insertNode(&poly, 4, 2);
    insertNode(&poly, 5, 1);
    insertNode(&poly, 6, 0);

    printf("Original Polynomial: ");
    displayPolynomial(poly);

    poly = removeEvenExponents(poly);

    printf("After removing even exponents: ");
    displayPolynomial(poly);

    return 0;
}
