
#include <iostream> 
#include <cstring>

using namespace std;
typedef int T;

#define CMP_EQ(a, b) ((a) == (b))
#define CMP_LT(a, b) ((a) < (b))
#define CMP_GT(a, b) ((a) > (b))

typedef struct Node {
    T data;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
    
} Node;

Node* getFreeNode(T value, Node* parent) {
    Node* tmp = (Node*)malloc(sizeof(Node));
    tmp->left = tmp->right = NULL;
    tmp->data = value;
    tmp->parent = parent;
    return tmp;
}

void insert(Node** head, int value) {
    Node* tmp = NULL;
    Node* ins = NULL;
    if (*head == NULL) {
        *head = getFreeNode(value, NULL);
        return;
    }

    tmp = *head;
    while (tmp) {
        if (CMP_GT(value, tmp->data)) {
            if (tmp->right) {
                tmp = tmp->right;
                continue;
            }
            else {
                tmp->right = getFreeNode(value, tmp);
                return;
            }
        }
        else if (CMP_LT(value, tmp->data)) {
            if (tmp->left) {
                tmp = tmp->left;
                continue;
            }
            else {
                tmp->left = getFreeNode(value, tmp);
                return;
            }
        }
        else {
            exit(2);
        }
    }
}

Node* getNodeByValue(Node* root, T value) {
    while (root) {
        if (CMP_GT(root->data, value)) {
            root = root->left;
            continue;
        }
        else if (CMP_LT(root->data, value)) {
            root = root->right;
            continue;
        }
        else {
            return root;
        }
    }
    return NULL;
}

void removeNodeByPtr(Node* target) {
    if (target->left) {
        if (target == target->parent->left) {
            target->parent->left = target->left;
        }
        else {
            target->parent->right = target->left;
        }
    }
    else if (target->right) {
        if (target == target->parent->right) {
            target->parent->right = target->right;
        }
        else {
            target->parent->left = target->right;
        }
    }
    else {
        if (target == target->parent->left) {
            target->parent->left = NULL;
        }
        else {
            target->parent->right = NULL;
        }
    }
    free(target);
}

void deleteValue(Node* root, T value) {
    Node* target = getNodeByValue(root, value);
    removeNodeByPtr(target);
}

void printTree(Node* root, const char* dir, int level) {
    if (root) {
        printf("lvl %d %s = %d\n", level, dir, root->data);
        printTree(root->left, "left", level + 1);
        printTree(root->right, "right", level + 1);
    }
}

int main() {
    setlocale(LC_ALL, "ru");
    Node* root = NULL;

    insert(&root, 1);
    insert(&root, 2);
    insert(&root, 3);
    insert(&root, 10);
    insert(&root, 9);
    insert(&root, 8);
    insert(&root, 222);

    printTree(root, "root", 0);
    deleteValue(root, 4);
    printf("parent of 7 is %d\n", getNodeByValue(root, 7)->parent->data);
    printTree(root, "root", 0);
    deleteValue(root, 8);
    printTree(root, "root", 0);
    printf("------------------\n");
    deleteValue(root, 10);
    printTree(root, "root", 0);

    system("pause");
    return 0;
}