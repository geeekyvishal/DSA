#include <stdio.h>
#include <stdlib.h>

struct Node {
    int row;
    int col;
    int value;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int row, int col, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->row = row;
    newNode->col = col;
    newNode->value = value;
    newNode->next = newNode; // Circular linked list
    return newNode;
}

// Function to insert a node at the end of circular linked list
void insertNode(struct Node** head, int row, int col, int value) {
    struct Node* newNode = createNode(row, col, value);
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

// Function to display sparse matrix
void displaySparseMatrix(struct Node* head) {
    if (head == NULL) {
        printf("0\n");
        return;
    }
    struct Node* temp = head;
    do {
        printf("Row: %d, Col: %d, Value: %d\n", temp->row, temp->col, temp->value);
        temp = temp->next;
    } while (temp != head);
}

// Function to multiply two sparse matrices
struct Node* multiplySparseMatrices(struct Node* sparse1, struct Node* sparse2) {
    struct Node* result = NULL;
    struct Node* temp1 = sparse1;
    struct Node* temp2;

    do {
        temp2 = sparse2;
        do {
            if (temp1->col == temp2->row) {
                insertNode(&result, temp1->row, temp2->col, temp1->value * temp2->value);
            }
            temp2 = temp2->next;
        } while (temp2 != sparse2);
        temp1 = temp1->next;
    } while (temp1 != sparse1);

    return result;
}

int main() {
    struct Node* sparseMatrix1 = NULL;
    struct Node* sparseMatrix2 = NULL;

    // Example sparse matrix 1
    insertNode(&sparseMatrix1, 0, 1, 3);
    insertNode(&sparseMatrix1, 1, 0, 5);
    insertNode(&sparseMatrix1, 1, 2, 4);

    // Example sparse matrix 2
    insertNode(&sparseMatrix2, 1, 0, 2);
    insertNode(&sparseMatrix2, 0, 2, 6);
    insertNode(&sparseMatrix2, 2, 1, 1);

    printf("Sparse Matrix 1:\n");
    displaySparseMatrix(sparseMatrix1);

    printf("Sparse Matrix 2:\n");
    displaySparseMatrix(sparseMatrix2);

    struct Node* product = multiplySparseMatrices(sparseMatrix1, sparseMatrix2);

    printf("Product of Sparse Matrices:\n");
    displaySparseMatrix(product);

    return 0;
}
