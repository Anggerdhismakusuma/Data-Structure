#include <stdio.h>
#include <stdlib.h>

struct Node {
    int id;
    int value;
    int international_achievements;
    int height;
    Node *left, *right;
};

int max(int a, int b) {
    return a > b ? a : b;
}

int getHeight(Node *node) {
    return node ? node->height : 0;
}

int getBalance(Node *node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

int calculateValue(int exam_pass, int have_c_grade) {
    if (exam_pass == 0 && have_c_grade == 1) return 0;
    if (exam_pass == 0 && have_c_grade == 0) return 1;
    if (exam_pass == 1 && have_c_grade == 1) return 2;
    return 3;
}

int compare(Node *a, Node *b) {
    if (a->value != b->value) return b->value - a->value;
    if (a->international_achievements != b->international_achievements) return b->international_achievements - a->international_achievements;
    return a->id - b->id;
}

Node* rightRotate(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    return x;
}

Node* leftRotate(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}

Node* insert(Node *node, int id, int exam_pass, int have_c_grade, int achievements) {
    if (!node) {
        Node *newNode = (Node*)malloc(sizeof(Node));
        newNode->id = id;
        newNode->value = calculateValue(exam_pass, have_c_grade);
        newNode->international_achievements = achievements;
        newNode->left = newNode->right = NULL;
        newNode->height = 1;
        return newNode;
    }

    Node temp;
    temp.id = id;
    temp.value = calculateValue(exam_pass, have_c_grade);
    temp.international_achievements = achievements;

    if (compare(&temp, node) < 0)
        node->left = insert(node->left, id, exam_pass, have_c_grade, achievements);
    else if (compare(&temp, node) > 0)
        node->right = insert(node->right, id, exam_pass, have_c_grade, achievements);
    else
        return node;

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    int balance = getBalance(node);

    if (balance > 1 && compare(&temp, node->left) < 0)
        return rightRotate(node);
    if (balance < -1 && compare(&temp, node->right) > 0)
        return leftRotate(node);
    if (balance > 1 && compare(&temp, node->left) > 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && compare(&temp, node->right) < 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

Node* minValueNode(Node *node) {
    Node *current = node;
    while (current->left)
        current = current->left;
    return current;
}

Node* findById(Node *node, int id) {
    if (!node) return NULL;
    if (node->id == id) return node;
    Node *found = findById(node->left, id);
    if (found) return found;
    return findById(node->right, id);
}

Node* deleteByData(Node *root, Node *target) {
    if (!root) return NULL;

    if (compare(target, root) < 0)
        root->left = deleteByData(root->left, target);
    else if (compare(target, root) > 0)
        root->right = deleteByData(root->right, target);
    else {
        if (!root->left || !root->right) {
            Node *temp = root->left ? root->left : root->right;
            free(root);
            return temp;
        }

        Node *temp = minValueNode(root->right);
        root->id = temp->id;
        root->value = temp->value;
        root->international_achievements = temp->international_achievements;
        root->right = deleteByData(root->right, temp);
    }

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

Node* deleteAVL(Node *root, int id) {
    Node *target = findById(root, id);
    if (target)
        root = deleteByData(root, target);
    return root;
}

void getTop3(Node *node, int *count) {
    if (!node || *count >= 3) return;
    getTop3(node->left, count);
    if (*count < 3) {
        printf("%d ", node->id);
        (*count)++;
    }
    getTop3(node->right, count);
}

int main() {
    Node *root1 = NULL;
    Node *root2 = NULL;

    root1 = insert(root1, 1, 1, 0, 10);
    root1 = insert(root1, 2, 1, 0, 6);
    root1 = insert(root1, 3, 1, 1, 8);
    root1 = insert(root1, 4, 1, 1, 5);
    root1 = insert(root1, 5, 0, 0, 5); 
    root1 = insert(root1, 6, 1, 0, 7);
    root1 = insert(root1, 7, 1, 0, 9);

    root1 = deleteAVL(root1, 2);
    root1 = deleteAVL(root1, 1);
    root1 = deleteAVL(root1, 3);
    root1 = deleteAVL(root1, 4);
    int count1 = 0;
    printf("Test Case 1: ");
    getTop3(root1, &count1);
    printf("\n");

    root2 = insert(root2, 1, 1, 1, 5);
    root2 = insert(root2, 2, 1, 1, 10);
    root2 = insert(root2, 3, 1, 1, 7);
    root2 = insert(root2, 4, 1, 0, 4);
    root2 = insert(root2, 5, 1, 0, 8);
    root2 = insert(root2, 6, 1, 0, 3);
    root2 = insert(root2, 7, 1, 0, 10);

    root2 = deleteAVL(root2, 2);
    root2 = deleteAVL(root2, 7);
    root2 = deleteAVL(root2, 5);

    int count2 = 0;
    printf("Test Case 2: ");
    getTop3(root2, &count2);
    printf("\n");
    return 0;
}