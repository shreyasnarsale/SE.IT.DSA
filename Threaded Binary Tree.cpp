//Problem Statement:- 
/* 
Implement In-order Threaded Binary Tree and traverse it in In-order and Pre-order. 
*/ 


#include <iostream>
#include <limits>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;
    int lbit; // 0 = thread, 1 = child
    int rbit; // 0 = thread, 1 = child
    Node(int value) : data(value), left(nullptr), right(nullptr), lbit(0), rbit(0) {}
};

class TBT {
private:
    Node* root;
    Node* head;

public:
    TBT() : root(nullptr), head(nullptr) {}

    void insertNode(int value);
    void inorder();
    void preorder();
    bool isDuplicate(int value); // Validation to avoid duplicate nodes
};

// Check for duplicate values
bool TBT::isDuplicate(int value) {
    Node* curr = root;
    while (curr) {
        if (value == curr->data) return true;
        if (value < curr->data) {
            if (curr->lbit == 1) curr = curr->left;
            else break;
        } else {
            if (curr->rbit == 1) curr = curr->right;
            else break;
        }
    }
    return false;
}

// Insert node in Threaded Binary Tree
void TBT::insertNode(int value) {
    if (isDuplicate(value)) {
        cout << "Value " << value << " already exists. Skipping insertion.\n";
        return;
    }

    Node* temp = new Node(value);

    if (!root) { // First node
        root = temp;
        head = new Node(9999); // Dummy head
        head->left = root;
        head->lbit = 1;
        head->right = head;
        head->rbit = 1;

        root->left = head;
        root->right = head;
    } else {
        Node* current = root;
        while (true) {
            if (value < current->data) {
                if (current->lbit == 0) {
                    temp->left = current->left;
                    temp->right = current;
                    current->left = temp;
                    current->lbit = 1;
                    break;
                } else {
                    current = current->left;
                }
            } else { // value > current->data
                if (current->rbit == 0) {
                    temp->right = current->right;
                    temp->left = current;
                    current->right = temp;
                    current->rbit = 1;
                    break;
                } else {
                    current = current->right;
                }
            }
        }
    }
}

// In-order Traversal
void TBT::inorder() {
    if (!root) {
        cout << "Tree is empty.\n";
        return;
    }

    Node* current = root;
    // Go to leftmost node
    while (current->lbit == 1) current = current->left;

    while (current != head) {
        cout << current->data << " ";

        if (current->rbit == 1) {
            current = current->right;
            while (current->lbit == 1) current = current->left;
        } else {
            current = current->right;
        }
    }
    cout << endl;
}

// Pre-order Traversal
void TBT::preorder() {
    if (!root) {
        cout << "Tree is empty.\n";
        return;
    }

    Node* current = root;
    while (current != head) {
        cout << current->data << " ";

        if (current->lbit == 1)
            current = current->left;
        else if (current->rbit == 1)
            current = current->right;
        else {
            while (current != head && current->rbit == 0)
                current = current->right;
            if (current != head)
                current = current->right;
        }
    }
    cout << endl;
}

// Main function
int main() {
    TBT tbt;
    int choice, value;

    while (true) {
        cout << "\nThreaded Binary Tree Menu:\n";
        cout << "1. Insert Node\n";
        cout << "2. In-order Traversal\n";
        cout << "3. Pre-order Traversal\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";

        cin >> choice;

        if (cin.fail()) { // Validate input
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between 1-4.\n";
            continue;
        }

        switch (choice) {
        case 1:
            cout << "Enter value to insert: ";
            cin >> value;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid value. Must be an integer.\n";
            } else {
                tbt.insertNode(value);
                cout << "Node " << value << " inserted.\n";
            }
            break;

        case 2:
            cout << "In-order Traversal: ";
            tbt.inorder();
            break;

        case 3:
            cout << "Pre-order Traversal: ";
            tbt.preorder();
            break;

        case 4:
            cout << "Exiting program.\n";
            return 0;

        default:
            cout << "Invalid choice. Enter 1-4.\n";
        }
    }

    return 0;
}
