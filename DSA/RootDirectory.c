#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 50

typedef struct Node {
    char name[MAX_NAME];
    int isDirectory; 
    struct Node *child;
    struct Node *sibling;
} Node;

typedef struct DeletedNode {
    char name[MAX_NAME];
    int isDirectory;
    struct DeletedNode *next;
} DeletedNode;

DeletedNode *deletedHead = NULL; 

// Function prototypes
Node* createNode(const char *name, int isDirectory);
void addNode(Node *parent, const char *name, int isDirectory);
void deleteNode(Node *node);
void deleteSpecificNode(Node *parent, const char *name);
void recoverNode(Node *root);
Node* searchNode(Node *root, const char *name);
void displayStructure(Node *root, int level);
void cleanupMemory(Node *root);
void cleanupDeletedList();
int isProtectedDirectory(const char *name); 
Node* createNode(const char *name, int isDirectory) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        perror("Failed to allocate memory for new node");
        exit(EXIT_FAILURE);
    }
    strcpy(newNode->name, name);
    newNode->isDirectory = isDirectory;
    newNode->child = NULL;
    newNode->sibling = NULL;
    return newNode;
}

void addToDeleted(const char *name, int isDirectory) {
    DeletedNode *newDeletedNode = (DeletedNode*)malloc(sizeof(DeletedNode));
    if (newDeletedNode == NULL) {
        perror("Failed to allocate memory for deleted node");
        exit(EXIT_FAILURE);
    }
    strcpy(newDeletedNode->name, name);  
    newDeletedNode->isDirectory = isDirectory; 
    newDeletedNode->next = deletedHead;
    deletedHead = newDeletedNode;
}

void recoverNode(Node *root) {
    if (!deletedHead) {
        printf("No nodes to recover.\n");
        return;
    }

    DeletedNode *recoveredDeletedNode = deletedHead;
    deletedHead = deletedHead->next; 
    addNode(root, recoveredDeletedNode->name, recoveredDeletedNode->isDirectory);
    printf("Node %s recovered successfully.\n", recoveredDeletedNode->name);
    free(recoveredDeletedNode); 
}

void addNode(Node *parent, const char *name, int isDirectory) {
    Node *newNode = createNode(name, isDirectory);
    if (!parent->child) {
        parent->child = newNode;
    } else {
        Node *temp = parent->child;
        while (temp->sibling) {
            temp = temp->sibling;
        }
        temp->sibling = newNode;
    }
}

void displayStructure(Node *root, int level) {
    if (!root) return;
    for (int i = 0; i < level; i++) printf("  ");
    printf("|-- %s\n", root->name);
    if (root->isDirectory) {
        displayStructure(root->child, level + 1);
    }
    displayStructure(root->sibling, level);
}

Node* searchNode(Node *root, const char *name) {
    if (!root) return NULL;
    if (strcmp(root->name, name) == 0) return root;

    Node *childResult = searchNode(root->child, name);
    if (childResult) return childResult;

    return searchNode(root->sibling, name);
}

void deleteNode(Node *node) {
    if (!node) return;
    deleteNode(node->child);
    deleteNode(node->sibling);
    free(node);
}

int isProtectedDirectory(const char *name) {
    return strcmp(name, "Downloads") == 0 ||
           strcmp(name, "Documents") == 0 ||
           strcmp(name, "Music") == 0 ||
           strcmp(name, "Desktop") == 0 ||
           strcmp(name, "Pictures") == 0;
}

void deleteSpecificNode(Node *parent, const char *name) {
    Node *temp = parent->child, *prev = NULL;

    while (temp && strcmp(temp->name, name) != 0) {
        prev = temp;
        temp = temp->sibling;
    }
    if (!temp) {
        printf("Node %s not found.\n", name);
        return;
    }

    if (isProtectedDirectory(temp->name)) {
        printf("Node %s cannot be deleted as it is a protected directory.\n", name);
        return;
    }

    addToDeleted(temp->name, temp->isDirectory);

    if (prev) {
        prev->sibling = temp->sibling;
    } else {
        parent->child = temp->sibling;
    }
    deleteNode(temp);
    printf("Node %s deleted successfully.\n", name);
}

void menu(Node *root) {
    int choice;
    char name[MAX_NAME];
    char parentName[MAX_NAME];

    while (1) {
        printf("\n--- File Directory System Menu ---\n");
        printf("1. Add File\n");
        printf("2. Add Directory\n");
        printf("3. Display Directory Structure\n");
        printf("4. Search for a File/Directory\n");
        printf("5. Delete a File/Directory\n");
        printf("6. Recover Last Deleted Node\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                printf("Enter the directory to add file in: ");
                scanf("%s", parentName);
                Node *parent = searchNode(root, parentName);
                if (!parent || !parent->isDirectory) {
                    printf("Directory not found or is not a directory.\n");
                    break;
                }
                printf("Enter file name: ");
                scanf("%s", name);
                addNode(parent, name, 0);
                printf("File %s added successfully under %s.\n", name, parentName);
                break;
            }
            case 2: {
                printf("Enter the parent directory to add new directory in (use 'root' for top-level): ");
                scanf("%s", parentName);
                Node *parent = (strcmp(parentName, "root") == 0) ? root : searchNode(root, parentName);
                if (!parent || !parent->isDirectory) {
                    printf("Directory not found or is not a directory.\n");
                    break;
                }
                printf("Enter new directory name: ");
                scanf("%s", name);
                addNode(parent, name, 1);
                printf("Directory %s added successfully under %s.\n", name, parentName);
                break;
            }
            case 3:
                printf("\nDirectory Structure:\n");
                displayStructure(root, 0);
                break;
            case 4:
                printf("Enter the name of the file/directory to search: ");
                scanf("%s", name);
                Node *foundNode = searchNode(root, name);
                if (foundNode) {
                    printf("%s found! It is a %s.\n", foundNode->name, foundNode->isDirectory ? "directory" : "file");
                } else {
                    printf("%s not found.\n", name);
                }
                break;
            case 5:
                printf("Enter the parent directory name: ");
                scanf("%s", parentName);
                Node *parentDir = (strcmp(parentName, "root") == 0) ? root : searchNode(root, parentName);
                if (!parentDir || !parentDir->isDirectory) {
                    printf("Parent directory not found or is not a directory.\n");
                    break;
                }
                printf("Enter the name of the file/directory to delete: ");
                scanf("%s", name);
                deleteSpecificNode(parentDir, name);
                break;
            case 6:
                recoverNode(root);
                break;
            case 7:
                printf("Exiting program. Cleaning up memory...\n");
                cleanupMemory(root);
                cleanupDeletedList();
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

void cleanupMemory(Node *root) {
    if (!root) return;
    cleanupMemory(root->child);
    cleanupMemory(root->sibling);
    free(root);
}

void cleanupDeletedList() {
    while (deletedHead) {
        DeletedNode *temp = deletedHead;
        deletedHead = deletedHead->next;
        free(temp);
    }
}

int main() {


    Node *root = createNode("root", 1);



    addNode(root, "Documents", 1);
    addNode(root, "Downloads", 1);
    addNode(root, "Music", 1);
    addNode(root, "Desktop", 1);
    addNode(root, "Pictures", 1);
    menu(root);
    return 0;
}