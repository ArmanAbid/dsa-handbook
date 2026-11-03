class TreeNode {
    data: number;
    left: TreeNode | null;
    right: TreeNode | null;

    constructor(data: number) {
        this.data = data;
        this.left = null;
        this.right = null;
    }
}

class BinarySearchTree {
    private root: TreeNode | null;
    private length: number;

    constructor() {
        this.root = null;
        this.length = 0;
    }

    // INSERT: Recursively insert while preserving BST ordering.
    private insertNode(
        node: TreeNode | null,
        value: number
    ): { node: TreeNode; inserted: boolean } {
        if (node === null) {
            return {
                node: new TreeNode(value),
                inserted: true
            };
        }

        if (value < node.data) {
            const result = this.insertNode(node.left, value);
            node.left = result.node;

            return {
                node,
                inserted: result.inserted
            };
        }

        if (value > node.data) {
            const result = this.insertNode(node.right, value);
            node.right = result.node;

            return {
                node,
                inserted: result.inserted
            };
        }

        // Equal values are not inserted.
        return {
            node,
            inserted: false
        };
    }

    // SEARCH: Find a node containing the given value.
    private findNode(value: number): TreeNode | null {
        let current = this.root;

        while (current !== null) {
            if (value === current.data) {
                return current;
            }

            if (value < current.data) {
                current = current.left;
            } else {
                current = current.right;
            }
        }

        return null;
    }

    // Find the node with the smallest value in a subtree.
    private minimumNode(node: TreeNode | null): TreeNode | null {
        if (node === null) {
            return null;
        }

        while (node.left !== null) {
            node = node.left;
        }

        return node;
    }

    // Find the node with the largest value in a subtree.
    private maximumNode(node: TreeNode | null): TreeNode | null {
        if (node === null) {
            return null;
        }

        while (node.right !== null) {
            node = node.right;
        }

        return node;
    }

    // DELETE: Remove a value while preserving BST ordering.
    private removeNode(
        node: TreeNode | null,
        value: number
    ): { node: TreeNode | null; removed: boolean } {
        if (node === null) {
            return {
                node: null,
                removed: false
            };
        }

        if (value < node.data) {
            const result = this.removeNode(node.left, value);
            node.left = result.node;

            return {
                node,
                removed: result.removed
            };
        }

        if (value > node.data) {
            const result = this.removeNode(node.right, value);
            node.right = result.node;

            return {
                node,
                removed: result.removed
            };
        }

        // Case 1: No left child.
        if (node.left === null) {
            return {
                node: node.right,
                removed: true
            };
        }

        // Case 2: No right child.
        if (node.right === null) {
            return {
                node: node.left,
                removed: true
            };
        }

        // Case 3: Two children.
        // Replace with the inorder successor.
        const successor = this.minimumNode(node.right);

        if (successor === null) {
            return {
                node,
                removed: false
            };
        }

        node.data = successor.data;

        const result = this.removeNode(
            node.right,
            successor.data
        );

        node.right = result.node;

        return {
            node,
            removed: true
        };
    }

    // PREORDER: Root -> Left -> Right.
    preorder(): number[] {
        const values: number[] = [];

        const traverse = (node: TreeNode | null): void => {
            if (node === null) {
                return;
            }

            values.push(node.data);

            traverse(node.left);
            traverse(node.right);
        };

        traverse(this.root);
        return values;
    }

    // INORDER: Left -> Root -> Right.
    inorder(): number[] {
        const values: number[] = [];

        const traverse = (node: TreeNode | null): void => {
            if (node === null) {
                return;
            }

            traverse(node.left);

            values.push(node.data);

            traverse(node.right);
        };

        traverse(this.root);
        return values;
    }

    // POSTORDER: Left -> Right -> Root.
    postorder(): number[] {
        const values: number[] = [];

        const traverse = (node: TreeNode | null): void => {
            if (node === null) {
                return;
            }

            traverse(node.left);
            traverse(node.right);

            values.push(node.data);
        };

        traverse(this.root);
        return values;
    }

    // LEVEL-ORDER: Visit nodes level by level.
    levelOrder(): number[] {
        const values: number[] = [];

        if (this.root === null) {
            return values;
        }

        const nodes: TreeNode[] = [this.root];
        let index = 0;

        while (index < nodes.length) {
            const current = nodes[index];
            index++;

            if (current === undefined) {
                continue;
            }

            values.push(current.data);

            if (current.left !== null) {
                nodes.push(current.left);
            }

            if (current.right !== null) {
                nodes.push(current.right);
            }
        }

        return values;
    }

    // INSERT: Add a value.
    insert(value: number): boolean {
        const result = this.insertNode(this.root, value);

        this.root = result.node;

        if (result.inserted) {
            this.length++;
        }

        return result.inserted;
    }

    // SEARCH: Check whether a value exists.
    contains(value: number): boolean {
        return this.findNode(value) !== null;
    }

    // UPDATE: Change an existing value without breaking BST ordering.
    update(oldValue: number, newValue: number): boolean {
        if (!this.contains(oldValue)) {
            return false;
        }

        if (oldValue === newValue) {
            return true;
        }

        // Duplicate values are not allowed.
        if (this.contains(newValue)) {
            return false;
        }

        // Delete the old value and insert the new one.
        // The total number of nodes remains unchanged.
        const removed = this.remove(oldValue);

        if (!removed) {
            return false;
        }

        return this.insert(newValue);
    }

    // DELETE: Remove a value.
    remove(value: number): boolean {
        const result = this.removeNode(this.root, value);

        this.root = result.node;

        if (result.removed) {
            this.length--;
        }

        return result.removed;
    }

    // MINIMUM: Get the smallest value.
    getMinimum(): number | undefined {
        const node = this.minimumNode(this.root);

        if (node === null) {
            return undefined;
        }

        return node.data;
    }

    // MAXIMUM: Get the largest value.
    getMaximum(): number | undefined {
        const node = this.maximumNode(this.root);

        if (node === null) {
            return undefined;
        }

        return node.data;
    }

    // SIZE: Get the number of nodes.
    sizeOf(): number {
        return this.length;
    }

    // CHECK: Check whether the tree is empty.
    isEmpty(): boolean {
        return this.root === null;
    }

    // CLEAR: Remove all nodes.
    clearTree(): void {
        this.root = null;
        this.length = 0;
    }
}

// DEMONSTRATION

const tree = new BinarySearchTree();

console.log("==== BINARY SEARCH TREE ====");

// INSERT
console.log("\n--- INSERT ---");

tree.insert(50);
tree.insert(30);
tree.insert(70);
tree.insert(20);
tree.insert(40);
tree.insert(60);
tree.insert(80);

console.log("Inserted 7 values.");

console.log(
    "Insert duplicate 50:",
    tree.insert(50) ? "Inserted" : "Duplicate rejected"
);

// TRAVERSALS
console.log("\n--- TRAVERSALS ---");

console.log("Preorder:", tree.preorder());
console.log("Inorder:", tree.inorder());
console.log("Postorder:", tree.postorder());
console.log("Level-order:", tree.levelOrder());

// SEARCH
console.log("\n--- SEARCH ---");

console.log("Contains 60:", tree.contains(60));
console.log("Contains 90:", tree.contains(90));

// MINIMUM AND MAXIMUM
console.log("\n--- MINIMUM AND MAXIMUM ---");

console.log("Minimum:", tree.getMinimum());
console.log("Maximum:", tree.getMaximum());

// UPDATE
console.log("\n--- UPDATE ---");

console.log("Update 40 to 45:", tree.update(40, 45));

console.log(
    "Update 45 to 70:",
    tree.update(45, 70),
    "(duplicate value)"
);

console.log("Inorder after update:", tree.inorder());

// DELETE
console.log("\n--- DELETE ---");

console.log("Remove leaf 20:", tree.remove(20));
console.log("Remove node 30:", tree.remove(30));
console.log("Remove missing 100:", tree.remove(100));

console.log("Inorder after removal:", tree.inorder());

// SIZE AND EMPTY CHECK
console.log("\n--- SIZE AND EMPTY CHECK ---");

console.log("Size:", tree.sizeOf());
console.log("Is empty:", tree.isEmpty());

// CLEAR
console.log("\n--- CLEAR ---");

tree.clearTree();

console.log("Size after clearing:", tree.sizeOf());
console.log("Is empty:", tree.isEmpty());

console.log("Inorder after clearing:", tree.inorder());

// INSERT AFTER CLEAR
console.log("\n--- INSERT AFTER CLEAR ---");

tree.insert(100);
tree.insert(50);

console.log("Inorder:", tree.inorder());