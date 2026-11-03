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

class BinaryTree {
private:
    TreeNode* root;
    int length;

    struct QueueItem {
        TreeNode* node;
        TreeNode* parent;

        QueueItem(TreeNode* n, TreeNode* p) {
            node = n;
            parent = p;
        }
    };

    // Find the first matching node using level-order traversal.
    TreeNode* findNode(int value) const {
        if (root == NULL) {
            return NULL;
        }

        queue<TreeNode*> nodes;
        nodes.push(root);

        while (!nodes.empty()) {
            TreeNode* current = nodes.front();
            nodes.pop();

            if (current->data == value) {
                return current;
            }

            if (current->left != NULL) {
                nodes.push(current->left);
            }

            if (current->right != NULL) {
                nodes.push(current->right);
            }
        }

        return NULL;
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
    BinaryTree(const BinaryTree&);
    BinaryTree& operator=(const BinaryTree&);

public:
    // CREATE: Initialize an empty tree.
    BinaryTree() {
        root = NULL;
        length = 0;
    }

    // INSERT: Add a node at the first available position.
    bool insert(int value) {
        TreeNode* newNode = new TreeNode(value);

        // Insert the first node as the root.
        if (root == NULL) {
            root = newNode;
            length++;
            return true;
        }

        queue<TreeNode*> nodes;
        nodes.push(root);

        while (!nodes.empty()) {
            TreeNode* current = nodes.front();
            nodes.pop();

            // Check the left child first.
            if (current->left == NULL) {
                current->left = newNode;
                length++;
                return true;
            }

            nodes.push(current->left);

            // Then check the right child.
            if (current->right == NULL) {
                current->right = newNode;
                length++;
                return true;
            }

            nodes.push(current->right);
        }

        delete newNode;
        return false;
    }

    // SEARCH: Check whether a value exists.
    bool contains(int value) const {
        return findNode(value) != NULL;
    }

    // UPDATE: Change the value of an existing node.
    bool update(int oldValue, int newValue) {
        TreeNode* node = findNode(oldValue);

        if (node == NULL) {
            return false;
        }

        node->data = newValue;
        return true;
    }

    // DELETE: Remove a node and preserve the complete shape.
    bool remove(int value) {
        if (root == NULL) {
            return false;
        }

        queue<QueueItem> nodes;

        nodes.push(QueueItem(root, NULL));

        TreeNode* target = NULL;
        TreeNode* deepest = NULL;
        TreeNode* deepestParent = NULL;

        while (!nodes.empty()) {
            QueueItem item = nodes.front();
            nodes.pop();

            TreeNode* current = item.node;

            // Record the first matching node.
            if (target == NULL && current->data == value) {
                target = current;
            }

            // The final node visited is the deepest,
            // rightmost node in level-order traversal.
            deepest = current;
            deepestParent = item.parent;

            if (current->left != NULL) {
                nodes.push(QueueItem(current->left, current));
            }

            if (current->right != NULL) {
                nodes.push(QueueItem(current->right, current));
            }
        }

        if (target == NULL || deepest == NULL) {
            return false;
        }

        // Replace the target value with the deepest node value.
        target->data = deepest->data;

        // Remove the deepest node.
        if (deepestParent == NULL) {
            root = NULL;
        } else if (deepestParent->right == deepest) {
            deepestParent->right = NULL;
        } else {
            deepestParent->left = NULL;
        }

        delete deepest;
        length--;

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
    ~BinaryTree() {
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
    BinaryTree tree;

    cout << "==== BINARY TREE ====" << endl;

    // INSERT
    cout << "\n--- INSERT ---" << endl;

    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(60);
    tree.insert(70);

    cout << "Inserted 7 nodes." << endl;

    // TRAVERSALS
    cout << "\n--- TRAVERSALS ---" << endl;

    printValues("Preorder: ", tree.preorder());
    printValues("Inorder: ", tree.inorder());
    printValues("Postorder: ", tree.postorder());
    printValues("Level-order: ", tree.levelOrder());

    // SEARCH
    cout << "\n--- SEARCH ---" << endl;

    cout << "Contains 50: "
         << (tree.contains(50) ? "Yes" : "No") << endl;

    cout << "Contains 90: "
         << (tree.contains(90) ? "Yes" : "No") << endl;

    // UPDATE
    cout << "\n--- UPDATE ---" << endl;

    if (tree.update(50, 55)) {
        cout << "Updated 50 to 55." << endl;
    }

    printValues("Level-order after update: ", tree.levelOrder());

    // DELETE
    cout << "\n--- DELETE ---" << endl;

    if (tree.remove(20)) {
        cout << "Removed 20." << endl;
    }

    printValues("Level-order after removal: ", tree.levelOrder());

    cout << "Contains 20: "
         << (tree.contains(20) ? "Yes" : "No") << endl;

    // SIZE AND EMPTY CHECK
    cout << "\n--- SIZE AND EMPTY CHECK ---" << endl;

    cout << "Size: " << tree.sizeOf() << endl;
    cout << "Is empty: " << (tree.isEmpty() ? "Yes" : "No") << endl;

    // CLEAR
    cout << "\n--- CLEAR ---" << endl;

    tree.clearTree();

    cout << "Size after clearing: " << tree.sizeOf() << endl;
    cout << "Is empty: " << (tree.isEmpty() ? "Yes" : "No") << endl;

    printValues("Level-order after clearing: ", tree.levelOrder());

    // INSERT AFTER CLEAR
    cout << "\n--- INSERT AFTER CLEAR ---" << endl;

    tree.insert(100);
    tree.insert(200);

    printValues("Level-order: ", tree.levelOrder());

    return 0;
}