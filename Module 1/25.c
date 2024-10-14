#include <stdio.h>
#include <stdlib.h>

enum Color { RED, BLACK };

struct Node {
    int data;
    enum Color color;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = newNode->parent = NULL;
    newNode->color = RED; // New nodes are always red
    return newNode;
}

// Function to rotate left
void leftRotate(struct Node** root, struct Node* x) {
    struct Node* y = x->right;
    x->right = y->left;
    if (y->left != NULL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
        *root = y; // y becomes the new root
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

// Function to rotate right
void rightRotate(struct Node** root, struct Node* y) {
    struct Node* x = y->left;
    y->left = x->right;
    if (x->right != NULL) {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if (y->parent == NULL) {
        *root = x; // x becomes the new root
    } else if (y == y->parent->right) {
        y->parent->right = x;
    } else {
        y->parent->left = x;
    }
    x->right = y;
    y->parent = x;
}

// Function to fix violations of red-black properties
void fixViolation(struct Node** root, struct Node* x) {
    struct Node* parent = NULL;
    struct Node* grandparent = NULL;

    while ((x != *root) && (x->color == RED) && (x->parent->color == RED)) {
        parent = x->parent;
        grandparent = parent->parent;

        // Case: parent is a left child
        if (parent == grandparent->left) {
            struct Node* uncle = grandparent->right;

            // Case 1: Uncle is RED
            if (uncle != NULL && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                x = grandparent; // Move up the tree
            } else {
                // Case 2: x is a right child
                if (x == parent->right) {
                    leftRotate(root, parent);
                    x = parent;
                    parent = x->parent;
                }
                // Case 3: x is a left child
                rightRotate(root, grandparent);
                parent->color = BLACK;
                grandparent->color = RED;
            }
        } else {
            struct Node* uncle = grandparent->left;

            // Case 1: Uncle is RED
            if ((uncle != NULL) && (uncle->color == RED)) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                x = grandparent; // Move up the tree
            } else {
                // Case 2: x is a left child
                if (x == parent->left) {
                    rightRotate(root, parent);
                    x = parent;
                    parent = x->parent;
                }
                // Case 3: x is a right child
                leftRotate(root, grandparent);
                parent->color = BLACK;
                grandparent->color = RED;
            }
        }
    }
    (*root)->color = BLACK; // Ensure root is always black
}

// Function to insert a new node
struct Node* insert(struct Node** root, int data) {
    struct Node* newNode = createNode(data);
    struct Node* y = NULL;
    struct Node* x = *root;

    while (x != NULL) {
        y = x;
        if (newNode->data < x->data) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    newNode->parent = y;
    if (y == NULL) {
        *root = newNode; // New node is root
    } else if (newNode->data < y->data) {
        y->left = newNode;
    } else {
        y->right = newNode;
    }

    fixViolation(root, newNode);
    return newNode;
}

// Function to find the minimum node
struct Node* findMin(struct Node* node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

// Function to delete a node
struct Node* deleteNode(struct Node* root, int data) {
    struct Node* z = root;
    struct Node* x, * y;

    // Find the node to be deleted
    while (z != NULL) {
        if (z->data == data) {
            break;
        } else if (data < z->data) {
            z = z->left;
        } else {
            z = z->right;
        }
    }

    if (z == NULL) {
        printf("Node not found\\n");
        return root;
    }

    y = z; // Node to be deleted
    enum Color yOriginalColor = y->color;

    if (z->left == NULL) {
        x = z->right;
        if (x != NULL) x->parent = z->parent;
        if (z->parent == NULL) {
            root = z->right; // z is root
        } else if (z == z->parent->left) {
            z->parent->left = z->right;
        } else {
            z->parent->right = z->right;
        }
    } else if (z->right == NULL) {
        x = z->left;
        if (x != NULL) x->parent = z->parent;
        if (z->parent == NULL) {
            root = z->left; // z is root
        } else if (z == z->parent->left) {
            z->parent->left = z->left;
        } else {
            z->parent->right = z->left;
        }
    } else {
        y = findMin(z->right); // Successor
        yOriginalColor = y->color;
        x = y->right;

        if (y->parent == z) {
            if (x != NULL) x->parent = y;
        } else {
            if (x != NULL) x->parent = y->parent;
            y->parent->left = x;
            y->right = z->right;
            z->right->parent = y;
        }

        if (z->parent == NULL) {
            root = y; // y becomes root
        } else if (z == z->parent->left) {
            z->parent->left = y;
        } else {
            z->parent->right = y;
        }
        y->left = z->left;
        z->left->parent = y;
        y->color = z->color;
    }

    free(z);
    if (yOriginalColor == BLACK) {
        // Fix violations if y was black
        // Implement necessary logic for fixing violations
    }

    return root;
}

// Function for inorder traversal
void inorder(struct Node* root) {
    if (root == NULL) {
        return;
    }
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

int main() {
    struct Node* root = NULL;

    // Insert some nodes
    int keys[] = { 20, 15, 25, 10, 5, 30, 35 };
    for (int i = 0; i < sizeof(keys) / sizeof(keys[0]); i++) {
        root = insert(&root, keys[i]);
    }

    printf("Inorder traversal of the created Red-Black tree is:\n");
    inorder(root);

    // Deletion
    root = deleteNode(root, 20);

    printf("Inorder traversal of the Red-Black tree after deletion:\n");
    inorder(root);

    return 0;
}
