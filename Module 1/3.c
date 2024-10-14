#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
    newNode->next = newNode; // Circular Linked List
    return newNode;
}

// Function to insert node
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

// Function to evaluate the polynomial
double evaluatePolynomial(struct Node* head, double x) {
    double result = 0;
    struct Node* temp = head;
    do {
        result += temp->coefficient * pow(x, temp->exponent);
        temp = temp->next;
    } while (temp != head);
    return result;
}

int main() {
    struct Node* poly = NULL;

    // Example polynomial 3x^3 + 5x^2 + 6
    insertNode(&poly, 3, 3);
    insertNode(&poly, 5, 2);
    insertNode(&poly, 6, 0);

    double x = 2; // Example value of x

    printf("The value of the polynomial for x = %.2f is: %.2f\n", x, evaluatePolynomial(poly, x));

    return 0;
}
