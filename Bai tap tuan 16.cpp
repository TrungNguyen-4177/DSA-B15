#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;
    int height;

    Node(int key) {
        data = key;
        left = right = nullptr;
        height = 1;
    }
};

class AVLTree {
public:
    Node* root;

    AVLTree() {
        root = nullptr;
    }

    int height(Node* node) {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    int getBalance(Node* node) {
        if (node == nullptr)
            return 0;
        return height(node->left) - height(node->right);
    }

    void updateHeight(Node* node) {
        node->height = max(height(node->left), height(node->right)) + 1;
    }

    Node* insert(Node* node, int key) {
        if (node == nullptr)
            return new Node(key);

        if (key < node->data)
            node->left = insert(node->left, key);
        else if (key > node->data)
            node->right = insert(node->right, key);
        else 
            return node;

        updateHeight(node);

        int balance = getBalance(node);


        if (balance > 1 && key < node->left->data)
            return rightRotate(node);
            
        if (balance < -1 && key > node->right->data)
            return leftRotate(node);

        if (balance > 1 && key > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && key < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node* leftRotate(Node* z) {
        Node* y = z->right;
        Node* T2 = y->left;

        y->left = z;
        z->right = T2; 
        
        updateHeight(z);
        updateHeight(y);

        return y;
    }

    Node* rightRotate(Node* z) {
        Node* y = z->left;
        Node* T3 = y->right;

        y->right = z;
        z->left = T3;

        updateHeight(z);
        updateHeight(y);

        return y;
    }

    void inorder(Node* node) {
        if (node != nullptr) {
            inorder(node->left);
            cout << node->data << " ";
            inorder(node->right);
        }
    }


    void insert_value(int key) {
        root = insert(root, key);
    }

    void print_inorder() {
        inorder(root);
        cout << endl;
    }
};

int main() {
    AVLTree avl;

    int numbers[] = {20, 25, 30, 10, 5, 15};
    int n = sizeof(numbers) / sizeof(numbers[0]);

    for (int i = 0; i < n; i++) {
        avl.insert_value(numbers[i]);
    }

    cout << "Sap xep theo thu tu cay : ";
    avl.print_inorder();

    return 0;
}
