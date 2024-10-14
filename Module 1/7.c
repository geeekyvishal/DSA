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

// Function to remove all terms with even exponents (sum of x and y exponents)
struct Node* removeEvenExponentSum(struct Node* head) {
    struct Node* current = head;
    struct Node* prev = NULL;

    do {
        int sumExponents = current->exponentX + current->exponentY;
        if (sumExponents % 2 == 0) {
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

    // Example polynomial 3x^2y^1 + 4x^1y^1 + 5x^2y^2 + 6x^0y^0
    insertNode(&poly, 3, 2, 1);
    insertNode(&poly, 4, 1, 1);
    insertNode(&poly, 5, 2, 2);
    insertNode(&poly, 6, 0, 0);

    printf("Original Polynomial: ");
    displayPolynomial(poly);

    poly = removeEvenExponentSum(poly);

    printf("After removing even exponent sum: ");
    displayPolynomial(poly);

    return 0;
}
