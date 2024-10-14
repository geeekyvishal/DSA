#include <stdio.h>
#include <stdlib.h>

struct Node {
    int row;
    int col;
    int value;
    struct Node* next;
};

// Function to create a node
struct Node* createNode(int row, int col, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->row = row;
    newNode->col = col;
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the end of the list
void insertNode(struct Node** head, int row, int col, int value) {
    struct Node* newNode = createNode(row, col, value);
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

// Function to display sparse matrix
void displaySparseMatrix(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("Row: %d, Col: %d, Value: %d\n", temp->row, temp->col, temp->value);
        temp = temp->next;
    }
}

// Function to transpose a sparse matrix
struct Node* transposeSparseMatrix(struct Node* head) {
    struct Node* transposed = NULL;
    struct Node* temp = head;
    
    while (temp != NULL) {
        insertNode(&transposed, temp->col, temp->row, temp->value);
        temp = temp->next;
    }
    return transposed;
}

int main() {
    struct Node* sparseMatrix = NULL;

    // Example sparse matrix:
    insertNode(&sparseMatrix, 0, 0, 5);
    insertNode(&sparseMatrix, 1, 2, 8);
    insertNode(&sparseMatrix, 2, 1, 7);
    insertNode(&sparseMatrix, 3, 3, 6);

    printf("Original Sparse Matrix:\n");
    displaySparseMatrix(sparseMatrix);

    struct Node* transposedMatrix = transposeSparseMatrix(sparseMatrix);

    printf("Transposed Sparse Matrix:\n");
    displaySparseMatrix(transposedMatrix);

    return 0;
}
