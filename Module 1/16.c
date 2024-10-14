#include <stdio.h>
#include <stdlib.h>

struct Node {
    int value;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the end of the linked list
void insertNode(struct Node** head, int value) {
    struct Node* newNode = createNode(value);
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

// Function to get the maximum value in the linked list
int getMax(struct Node* head) {
    int max = head->value;
    struct Node* temp = head;
    while (temp != NULL) {
        if (temp->value > max) {
            max = temp->value;
        }
        temp = temp->next;
    }
    return max;
}

// Function to perform counting sort based on the significant digit
void countingSort(struct Node** head, int exp) {
    struct Node* output[10] = { NULL }; // Output linked lists for each digit (0-9)
    struct Node* temp = *head;
    
    while (temp != NULL) {
        int index = (temp->value / exp) % 10;
        insertNode(&output[index], temp->value);
        temp = temp->next;
    }

    // Reconstruct the original linked list
    *head = NULL;
    for (int i = 0; i < 10; i++) {
        if (output[i] != NULL) {
            struct Node* tempOut = output[i];
            while (tempOut != NULL) {
                insertNode(head, tempOut->value);
                tempOut = tempOut->next;
            }
        }
    }
}

// Function to perform radix sort
void radixSort(struct Node** head) {
    int max = getMax(*head);
    for (int exp = 1; max / exp > 0; exp *= 10) {
        countingSort(head, exp);
    }
}

void displayList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->value);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    struct Node* list = NULL;

    // Example unsorted list
    insertNode(&list, 170);
    insertNode(&list, 45);
    insertNode(&list, 75);
    insertNode(&list, 90);
    insertNode(&list, 802);
    insertNode(&list, 24);
    insertNode(&list, 2);
    insertNode(&list, 66);

    printf("Unsorted List: ");
    displayList(list);

    radixSort(&list);

    printf("Sorted List: ");
    displayList(list);

    return 0;
}
