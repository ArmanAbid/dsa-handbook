#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct TreeNode {
    int data;
    int height;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int value) {
        data = value;
        height = 1;
        left = NULL;
        right = NULL;
    }
};

class AVLTree {
private:
    TreeNode* root;
    int length;

    // HEIGHT: Get the height of a node.
    int getHeight(TreeNode* node) const {
        if (node == NULL) {
            return 0;
        }

        return node->height;
    }

    // Update the height of a node.
    void updateHeight(TreeNode* node) {
        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);

        node->height = 1 + (
            leftHeight > rightHeight
                ? leftHeight
                : rightHeight
        );
    }

    // BALANCE FACTOR: Height of left subtree minus right subtree.
    int getBalanceFactor(TreeNode* node) const {
        if (node == NULL) {
            return 0;
        }

        return getHeight(node->left) - getHeight(node->right);
    }

    // RIGHT ROTATION: Used for LL imbalance.
    TreeNode* rotateRight(TreeNode* y) {
        TreeNode* x = y->left;
        TreeNode* subtree = x->right;

        x->right = y;
        y->left = subtree;

        // Update the lower node first.
        updateHeight(y);
        updateHeight(x);

        return x;
    }

    // LEFT ROTATION: Used for RR imbalance.
    TreeNode* rotateLeft(TreeNode* x) {
        TreeNode* y = x->right;
        TreeNode* subtree = y->left;

        y->left = x;
        x->right = subtree;

        // Update the lower node first.
        updateHeight(x);
        updateHeight(y);

        return y;
    }

    // REBALANCE: Restore AVL balance after modification.
    TreeNode* rebalance(TreeNode* node) {
        if (node == NULL) {
            return NULL;
        }

        updateHeight(node);

        int balance = getBalanceFactor(node);

        // Left-heavy subtree.
        if (balance > 1) {
            // LR case: Left rotation on the left child first.
            if (getBalanceFactor(node->left) < 0) {
                node->left = rotateLeft(node->left);
            }

            // LL case.
            return rotateRight(node);
        }

        // Right-heavy subtree.
        if (balance < -1) {
            // RL case: Right rotation on the right child first.
            if (getBalanceFactor(node->right) > 0) {
                node->right = rotateRight(node->right);
            }

            // RR case.
            return rotateLeft(node);
        }

        return node;
    }

    // INSERT: Recursively insert while preserving AVL balance.
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
        } else {
            // Duplicate values are not inserted.
            return node;
        }

        return rebalance(node);
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

    // DELETE: Remove a value while preserving AVL balance.
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

        return rebalance(node);
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
    AVLTree(const AVLTree&);
    AVLTree& operator=(const AVLTree&);

public:
    // CREATE: Initialize an empty AVL tree.
    AVLTree() {
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

    // UPDATE: Change a value while preserving AVL ordering.
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

        // Remove the old value and insert the new value.
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
    ~AVLTree() {
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
    AVLTree tree;
    int value;

    cout << "==== AVL TREE ====" << endl;

    // INSERT
    cout << "\n--- INSERT ---" << endl;

    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(25);

    cout << "Inserted 6 values." << endl;

    cout << "Insert duplicate 30: "
         << (tree.insert(30) ? "Inserted" : "Duplicate rejected")
         << endl;

    // TRAVERSALS
    cout << "\n--- TRAVERSALS ---" << endl;

    printValues("Preorder: ", tree.preorder());
    printValues("Inorder: ", tree.inorder());
    printValues("Postorder: ", tree.postorder());
    printValues("Level-order: ", tree.levelOrder());

    // SEARCH
    cout << "\n--- SEARCH ---" << endl;

    cout << "Contains 25: "
         << (tree.contains(25) ? "Yes" : "No") << endl;

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

    cout << "Update 25 to 35: "
         << (tree.update(25, 35) ? "Updated" : "Rejected")
         << endl;

    cout << "Update 35 to 40: "
         << (tree.update(35, 40) ? "Updated" : "Rejected")
         << " (duplicate value)" << endl;

    printValues("Inorder after update: ", tree.inorder());

    // DELETE
    cout << "\n--- DELETE ---" << endl;

    cout << "Remove leaf 10: "
         << (tree.remove(10) ? "Removed" : "Not found") << endl;

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
    tree.insert(150);

    printValues("Inorder: ", tree.inorder());

    return 0;
}