#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int value) {
        data = value;
        left = NULL;
        right = NULL;
    }
};

class BinarySearchTree {
private:
    TreeNode* root;
    int length;

    // INSERT: Recursively insert while preserving BST ordering.
    TreeNode* insertNode(
        TreeNode* node,
        int value,
        bool& inserted
    ) {
        if (node == NULL) {
            inserted = true;
            return new TreeNode(value);
        }

        if (value < node->data) {
            node->left = insertNode(node->left, value, inserted);
        } else if (value > node->data) {
            node->right = insertNode(node->right, value, inserted);
        }

        // Equal values are not inserted.
        return node;
    }

    // SEARCH: Find a node containing the given value.
    TreeNode* findNode(int value) const {
        TreeNode* current = root;

        while (current != NULL) {
            if (value == current->data) {
                return current;
            }

            if (value < current->data) {
                current = current->left;
            } else {
                current = current->right;
            }
        }

        return NULL;
    }

    // Find the node with the smallest value in a subtree.
    TreeNode* minimumNode(TreeNode* node) const {
        if (node == NULL) {
            return NULL;
        }

        while (node->left != NULL) {
            node = node->left;
        }

        return node;
    }

    // Find the node with the largest value in a subtree.
    TreeNode* maximumNode(TreeNode* node) const {
        if (node == NULL) {
            return NULL;
        }

        while (node->right != NULL) {
            node = node->right;
        }

        return node;
    }

    // DELETE: Remove a value while preserving BST ordering.
    TreeNode* removeNode(
        TreeNode* node,
        int value,
        bool& removed
    ) {
        if (node == NULL) {
            return NULL;
        }

        if (value < node->data) {
            node->left = removeNode(node->left, value, removed);
        } else if (value > node->data) {
            node->right = removeNode(node->right, value, removed);
        } else {
            removed = true;

            // Case 1: No left child.
            if (node->left == NULL) {
                TreeNode* replacement = node->right;
                delete node;
                return replacement;
            }

            // Case 2: No right child.
            if (node->right == NULL) {
                TreeNode* replacement = node->left;
                delete node;
                return replacement;
            }

            // Case 3: Two children.
            // Replace with the inorder successor.
            TreeNode* successor = minimumNode(node->right);

            node->data = successor->data;

            bool successorRemoved = false;

            node->right = removeNode(
                node->right,
                successor->data,
                successorRemoved
            );
        }

        return node;
    }

    // PREORDER: Root -> Left -> Right.
    void preorderTraversal(
        TreeNode* node,
        vector<int>& values
    ) const {
        if (node == NULL) {
            return;
        }

        values.push_back(node->data);

        preorderTraversal(node->left, values);
        preorderTraversal(node->right, values);
    }

    // INORDER: Left -> Root -> Right.
    void inorderTraversal(
        TreeNode* node,
        vector<int>& values
    ) const {
        if (node == NULL) {
            return;
        }

        inorderTraversal(node->left, values);

        values.push_back(node->data);

        inorderTraversal(node->right, values);
    }

    // POSTORDER: Left -> Right -> Root.
    void postorderTraversal(
        TreeNode* node,
        vector<int>& values
    ) const {
        if (node == NULL) {
            return;
        }

        postorderTraversal(node->left, values);
        postorderTraversal(node->right, values);

        values.push_back(node->data);
    }

    // Release all nodes recursively.
    void destroyTree(TreeNode* node) {
        if (node == NULL) {
            return;
        }

        destroyTree(node->left);
        destroyTree(node->right);

        delete node;
    }

    // Prevent accidental shallow copying of owned pointers.
    BinarySearchTree(const BinarySearchTree&);
    BinarySearchTree& operator=(const BinarySearchTree&);

public:
    // CREATE: Initialize an empty BST.
    BinarySearchTree() {
        root = NULL;
        length = 0;
    }

    // INSERT: Add a value.
    bool insert(int value) {
        bool inserted = false;

        root = insertNode(root, value, inserted);

        if (inserted) {
            length++;
        }

        return inserted;
    }

    // SEARCH: Check whether a value exists.
    bool contains(int value) const {
        return findNode(value) != NULL;
    }

    // UPDATE: Change an existing value without breaking BST ordering.
    bool update(int oldValue, int newValue) {
        if (!contains(oldValue)) {
            return false;
        }

        if (oldValue == newValue) {
            return true;
        }

        // Duplicate values are not allowed.
        if (contains(newValue)) {
            return false;
        }

        // Delete the old value and insert the new one.
        // The total number of nodes remains unchanged.
        bool removed = remove(oldValue);

        if (!removed) {
            return false;
        }

        return insert(newValue);
    }

    // DELETE: Remove a value.
    bool remove(int value) {
        bool removed = false;

        root = removeNode(root, value, removed);

        if (removed) {
            length--;
        }

        return removed;
    }

    // MINIMUM: Get the smallest value.
    bool getMinimum(int& value) const {
        TreeNode* node = minimumNode(root);

        if (node == NULL) {
            return false;
        }

        value = node->data;
        return true;
    }

    // MAXIMUM: Get the largest value.
    bool getMaximum(int& value) const {
        TreeNode* node = maximumNode(root);

        if (node == NULL) {
            return false;
        }

        value = node->data;
        return true;
    }

    // PREORDER: Root -> Left -> Right.
    vector<int> preorder() const {
        vector<int> values;
        preorderTraversal(root, values);
        return values;
    }

    // INORDER: Left -> Root -> Right.
    vector<int> inorder() const {
        vector<int> values;
        inorderTraversal(root, values);
        return values;
    }

    // POSTORDER: Left -> Right -> Root.
    vector<int> postorder() const {
        vector<int> values;
        postorderTraversal(root, values);
        return values;
    }

    // LEVEL-ORDER: Visit nodes level by level.
    vector<int> levelOrder() const {
        vector<int> values;

        if (root == NULL) {
            return values;
        }

        queue<TreeNode*> nodes;
        nodes.push(root);

        while (!nodes.empty()) {
            TreeNode* current = nodes.front();
            nodes.pop();

            values.push_back(current->data);

            if (current->left != NULL) {
                nodes.push(current->left);
            }

            if (current->right != NULL) {
                nodes.push(current->right);
            }
        }

        return values;
    }

    // SIZE: Get the number of nodes.
    int sizeOf() const {
        return length;
    }

    // CHECK: Check whether the tree is empty.
    bool isEmpty() const {
        return root == NULL;
    }

    // CLEAR: Remove all nodes and free their memory.
    void clearTree() {
        destroyTree(root);

        root = NULL;
        length = 0;
    }

    // Destructor: Automatically free remaining nodes.
    ~BinarySearchTree() {
        clearTree();
    }
};

// Helper function to print a traversal.
void printValues(const char* label, const vector<int>& values) {
    cout << label;

    for (unsigned int i = 0; i < values.size(); i++) {
        cout << values[i];

        if (i < values.size() - 1) {
            cout << " -> ";
        }
    }

    if (values.empty()) {
        cout << "Empty";
    }

    cout << endl;
}

// DEMONSTRATION

int main() {
    BinarySearchTree tree;
    int value;

    cout << "==== BINARY SEARCH TREE ====" << endl;

    // INSERT
    cout << "\n--- INSERT ---" << endl;

    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    cout << "Inserted 7 values." << endl;

    cout << "Insert duplicate 50: "
         << (tree.insert(50) ? "Inserted" : "Duplicate rejected")
         << endl;

    // TRAVERSALS
    cout << "\n--- TRAVERSALS ---" << endl;

    printValues("Preorder: ", tree.preorder());
    printValues("Inorder: ", tree.inorder());
    printValues("Postorder: ", tree.postorder());
    printValues("Level-order: ", tree.levelOrder());

    // SEARCH
    cout << "\n--- SEARCH ---" << endl;

    cout << "Contains 60: "
         << (tree.contains(60) ? "Yes" : "No") << endl;

    cout << "Contains 90: "
         << (tree.contains(90) ? "Yes" : "No") << endl;

    // MINIMUM AND MAXIMUM
    cout << "\n--- MINIMUM AND MAXIMUM ---" << endl;

    if (tree.getMinimum(value)) {
        cout << "Minimum: " << value << endl;
    }

    if (tree.getMaximum(value)) {
        cout << "Maximum: " << value << endl;
    }

    // UPDATE
    cout << "\n--- UPDATE ---" << endl;

    cout << "Update 40 to 45: "
         << (tree.update(40, 45) ? "Updated" : "Rejected")
         << endl;

    cout << "Update 45 to 70: "
         << (tree.update(45, 70) ? "Updated" : "Rejected")
         << " (duplicate value)" << endl;

    printValues("Inorder after update: ", tree.inorder());

    // DELETE
    cout << "\n--- DELETE ---" << endl;

    cout << "Remove leaf 20: "
         << (tree.remove(20) ? "Removed" : "Not found") << endl;

    cout << "Remove node 30: "
         << (tree.remove(30) ? "Removed" : "Not found") << endl;

    cout << "Remove missing 100: "
         << (tree.remove(100) ? "Removed" : "Not found") << endl;

    printValues("Inorder after removal: ", tree.inorder());

    // SIZE AND EMPTY CHECK
    cout << "\n--- SIZE AND EMPTY CHECK ---" << endl;

    cout << "Size: " << tree.sizeOf() << endl;
    cout << "Is empty: " << (tree.isEmpty() ? "Yes" : "No") << endl;

    // CLEAR
    cout << "\n--- CLEAR ---" << endl;

    tree.clearTree();

    cout << "Size after clearing: " << tree.sizeOf() << endl;
    cout << "Is empty: " << (tree.isEmpty() ? "Yes" : "No") << endl;

    printValues("Inorder after clearing: ", tree.inorder());

    // INSERT AFTER CLEAR
    cout << "\n--- INSERT AFTER CLEAR ---" << endl;

    tree.insert(100);
    tree.insert(50);

    printValues("Inorder: ", tree.inorder());

    return 0;
}