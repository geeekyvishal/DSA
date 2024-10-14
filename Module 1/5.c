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

// Function to display the polynomial
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

// Function to remove all terms with odd coefficients
struct Node* removeOddCoefficients(struct Node* head) {
    if (head == NULL) return NULL;

    struct Node* current = head;
    struct Node* prev = NULL;
    do {
        if (current->coefficient % 2 != 0) {
            if (current == head) {
                head = current->next;
            }
            if (prev != NULL) {
                prev->next = current->next;
            }
            struct Node* temp = current;
            current = current->next;
            free(temp);
        } else {
            prev = current;
            current = current->next;
        }
    } while (current != head);

    return head;
}

int main() {
    struct Node* poly = NULL;

    // Example polynomial 3x^3 + 4x^2 + 5x + 6
    insertNode(&poly, 3, 3);
    insertNode(&poly, 4, 2);
    insertNode(&poly, 5, 1);
    insertNode(&poly, 6, 0);

    printf("Polynomial: ");
    displayPolynomial(poly);

    poly = removeOddCoefficients(poly);

    printf("After removing odd coefficients: ");
    displayPolynomial(poly);

    return 0;
}
