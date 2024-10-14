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

// Function to display polynomial
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

// Function to divide two polynomials
struct Node* dividePolynomials(struct Node* dividend, struct Node* divisor) {
    struct Node* quotient = NULL;
    struct Node* remainder = dividend;

    while (remainder != NULL && remainder->exponent >= divisor->exponent) {
        int newCoeff = remainder->coefficient / divisor->coefficient;
        int newExp = remainder->exponent - divisor->exponent;
        insertNode(&quotient, newCoeff, newExp);

        // Create a temporary polynomial for the current term of the quotient
        struct Node* tempDivisor = NULL;
        insertNode(&tempDivisor, newCoeff * divisor->coefficient, 0); // For constant term
        insertNode(&tempDivisor, newCoeff * divisor->coefficient, divisor->exponent);

        // Subtract the tempDivisor from the remainder
        struct Node* newRemainder = NULL;
        struct Node* tempR = remainder;
        while (tempR != NULL) {
            int coeff = tempR->coefficient;
            int exp = tempR->exponent;
            coeff -= tempDivisor->coefficient; // Modify as needed for subtraction
            if (coeff != 0) {
                insertNode(&newRemainder, coeff, exp);
            }
            tempR = tempR->next;
        }
        remainder = newRemainder;
    }
    return quotient;
}

int main() {
    struct Node* dividend = NULL;
    struct Node* divisor = NULL;

    // Example: Dividend: 6x^3 + 11x^2 + 3x + 2
    insertNode(&dividend, 6, 3);
    insertNode(&dividend, 11, 2);
    insertNode(&dividend, 3, 1);
    insertNode(&dividend, 2, 0);

    // Example: Divisor: 2x + 1
    insertNode(&divisor, 2, 1);
    insertNode(&divisor, 1, 0);

    printf("Dividend: ");
    displayPolynomial(dividend);

    printf("Divisor: ");
    displayPolynomial(divisor);

    struct Node* quotient = dividePolynomials(dividend, divisor);
    
    printf("Quotient: ");
    displayPolynomial(quotient);

    return 0;
}
