#include <iostream>
#include <queue>
using namespace std;

// Node structure
struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Binary Search Tree class
class BST {
private:
    Node* root;

    // Helper for insertion
    Node* insert(Node* node, int val) {
        if (!node) return new Node(val);
        if (val < node->data) node->left = insert(node->left, val);
        else if (val > node->data) node->right = insert(node->right, val);
        return node; // Ignore duplicates
    }

    // Helper for deletion
    Node* deleteNode(Node* node, int val) {
        if (!node) return nullptr;
        if (val < node->data) node->left = deleteNode(node->left, val);
        else if (val > node->data) node->right = deleteNode(node->right, val);
        else {
            if (!node->left) { Node* temp = node->right; delete node; return temp; }
            else if (!node->right) { Node* temp = node->left; delete node; return temp; }
            Node* temp = findMin(node->right);
            node->data = temp->data;
            node->right = deleteNode(node->right, temp->data);
        }
        return node;
    }

    // Helper for searching
    Node* search(Node* node, int val) {
        if (!node || node->data == val) return node;
        return (val < node->data) ? search(node->left, val) : search(node->right, val);
    }

    // Find minimum node
    Node* findMin(Node* node) {
        while (node->left) node = node->left;
        return node;
    }

    // Recursive inorder traversal
    void inorder(Node* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    // Max depth of tree
    int maxDepth(Node* node) {
        if (!node) return 0;
        return max(maxDepth(node->left), maxDepth(node->right)) + 1;
    }

    // Mirror image of tree
    Node* mirror(Node* node) {
        if (!node) return nullptr;
        swap(node->left, node->right);
        mirror(node->left);
        mirror(node->right);
        return node;
    }

    // Copy tree
    Node* copy(Node* node) {
        if (!node) return nullptr;
        Node* newNode = new Node(node->data);
        newNode->left = copy(node->left);
        newNode->right = copy(node->right);
        return newNode;
    }

    // Display parents and their children
    void displayParents(Node* node) {
        if (!node) return;
        if (node->left || node->right) {
            cout << "Parent: " << node->data << " - Children: ";
            if (node->left) cout << node->left->data << " ";
            if (node->right) cout << node->right->data << " ";
            cout << endl;
        }
        displayParents(node->left);
        displayParents(node->right);
    }

    // Display leaf nodes
    void displayLeaves(Node* node) {
        if (!node) return;
        if (!node->left && !node->right) cout << node->data << " ";
        displayLeaves(node->left);
        displayLeaves(node->right);
    }

    // Display level-wise
    void displayLevel(Node* node, int level) {
        if (!node) return;
        if (level == 1) cout << node->data << " ";
        else if (level > 1) {
            displayLevel(node->left, level - 1);
            displayLevel(node->right, level - 1);
        }
    }

public:
    BST() : root(nullptr) {}

    void insert(int val) { root = insert(root, val); }
    void deleteNode(int val) { root = deleteNode(root, val); }
    Node* search(int val) { return search(root, val); }
    void displayTree() { inorder(root); cout << endl; }
    int getDepth() { return maxDepth(root); }

    void displayMirror() {
        root = mirror(root);
        displayTree();
        root = mirror(root); // restore original
    }

    BST copyTree() {
        BST newTree;
        newTree.root = copy(root);
        return newTree;
    }

    void displayParentsAndChildren() { displayParents(root); }
    void displayLeafNodes() { displayLeaves(root); cout << endl; }

    void displayLevelWise() {
        int depth = getDepth();
        for (int i = 1; i <= depth; i++) {
            displayLevel(root, i);
            cout << endl;
        }
    }
};

// Main menu
int main() {
    BST tree;
    while (true) {
        cout << "\nBinary Search Tree Menu:\n"
             << "1. Insert node\n2. Delete node\n3. Search node\n"
             << "4. Display original tree\n5. Display depth\n6. Display mirror image\n"
             << "7. Display copied tree\n8. Display parents and children\n"
             << "9. Display leaf nodes\n10. Display tree level-wise\n0. Exit\n"
             << "Enter your choice: ";
        int choice; cin >> choice;
        if (choice == 0) break;

        int val;
        switch (choice) {
        case 1:
            cout << "Enter value to insert: "; cin >> val; tree.insert(val); break;
        case 2:
            cout << "Enter value to delete: "; cin >> val; tree.deleteNode(val); break;
        case 3:
            cout << "Enter value to search: "; cin >> val;
            tree.search(val) ? cout << "Node found!\n" : cout << "Node not found!\n";
            break;
        case 4: cout << "Tree (inorder): "; tree.displayTree(); break;
        case 5: cout << "Depth: " << tree.getDepth() << endl; break;
        case 6: cout << "Mirror Image: "; tree.displayMirror(); break;
        case 7: cout << "Copied Tree: "; tree.copyTree().displayTree(); break;
        case 8: cout << "Parents and Children:\n"; tree.displayParentsAndChildren(); break;
        case 9: cout << "Leaf Nodes: "; tree.displayLeafNodes(); break;
        case 10: cout << "Level-wise:\n"; tree.displayLevelWise(); break;
        default: cout << "Invalid choice.\n";
        }
    }
    cout << "Exiting program.\n";
    return 0;
}
