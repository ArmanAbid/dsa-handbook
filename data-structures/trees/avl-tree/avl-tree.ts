class TreeNode {
    data: number;
    height: number;
    left: TreeNode | null;
    right: TreeNode | null;

    constructor(data: number) {
        this.data = data;
        this.height = 1;
        this.left = null;
        this.right = null;
    }
}

class AVLTree {
    private root: TreeNode | null;
    private length: number;

    constructor() {
        this.root = null;
        this.length = 0;
    }

    // HEIGHT: Get the height of a node.
    private getHeight(node: TreeNode | null): number {
        if (node === null) {
            return 0;
        }

        return node.height;
    }

    // Update the height of a node.
    private updateHeight(node: TreeNode): void {
        const leftHeight = this.getHeight(node.left);
        const rightHeight = this.getHeight(node.right);

        node.height = 1 + Math.max(leftHeight, rightHeight);
    }

    // BALANCE FACTOR: Left subtree height minus right subtree height.
    private getBalanceFactor(node: TreeNode | null): number {
        if (node === null) {
            return 0;
        }

        return (
            this.getHeight(node.left) -
            this.getHeight(node.right)
        );
    }

    // RIGHT ROTATION: Used for LL imbalance.
    private rotateRight(y: TreeNode): TreeNode {
        const x = y.left;

        if (x === null) {
            return y;
        }

        const subtree = x.right;

        x.right = y;
        y.left = subtree;

        // Update the lower node first.
        this.updateHeight(y);
        this.updateHeight(x);

        return x;
    }

    // LEFT ROTATION: Used for RR imbalance.
    private rotateLeft(x: TreeNode): TreeNode {
        const y = x.right;

        if (y === null) {
            return x;
        }

        const subtree = y.left;

        y.left = x;
        x.right = subtree;

        // Update the lower node first.
        this.updateHeight(x);
        this.updateHeight(y);

        return y;
    }

    // REBALANCE: Restore AVL balance after modification.
    private rebalance(node: TreeNode): TreeNode {
        this.updateHeight(node);

        const balance = this.getBalanceFactor(node);

        // Left-heavy subtree.
        if (balance > 1) {
            // LR case: Left rotation on the left child first.
            if (
                node.left !== null &&
                this.getBalanceFactor(node.left) < 0
            ) {
                node.left = this.rotateLeft(node.left);
            }

            // LL case.
            return this.rotateRight(node);
        }

        // Right-heavy subtree.
        if (balance < -1) {
            // RL case: Right rotation on the right child first.
            if (
                node.right !== null &&
                this.getBalanceFactor(node.right) > 0
            ) {
                node.right = this.rotateRight(node.right);
            }

            // RR case.
            return this.rotateLeft(node);
        }

        return node;
    }

    // INSERT: Recursively insert while preserving AVL balance.
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

            if (!result.inserted) {
                return {
                    node,
                    inserted: false
                };
            }
        } else if (value > node.data) {
            const result = this.insertNode(node.right, value);
            node.right = result.node;

            if (!result.inserted) {
                return {
                    node,
                    inserted: false
                };
            }
        } else {
            // Duplicate values are not inserted.
            return {
                node,
                inserted: false
            };
        }

        return {
            node: this.rebalance(node),
            inserted: true
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

    // DELETE: Remove a value while preserving AVL balance.
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

            if (!result.removed) {
                return {
                    node,
                    removed: false
                };
            }

            return {
                node: this.rebalance(node),
                removed: true
            };
        }

        if (value > node.data) {
            const result = this.removeNode(node.right, value);
            node.right = result.node;

            if (!result.removed) {
                return {
                    node,
                    removed: false
                };
            }

            return {
                node: this.rebalance(node),
                removed: true
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
            node: this.rebalance(node),
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

    // UPDATE: Change a value while preserving AVL ordering.
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

        // Remove the old value and insert the new value.
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

const tree = new AVLTree();

console.log("=== AVL TREE ===");

// INSERT
console.log("\n--- INSERT ---");

tree.insert(10);
tree.insert(20);
tree.insert(30);
tree.insert(40);
tree.insert(50);
tree.insert(25);

console.log("Inserted 6 values.");

console.log(
    "Insert duplicate 30:",
    tree.insert(30) ? "Inserted" : "Duplicate rejected"
);

// TRAVERSALS
console.log("\n--- TRAVERSALS ---");

console.log("Preorder:", tree.preorder());
console.log("Inorder:", tree.inorder());
console.log("Postorder:", tree.postorder());
console.log("Level-order:", tree.levelOrder());

// SEARCH
console.log("\n--- SEARCH ---");

console.log("Contains 25:", tree.contains(25));
console.log("Contains 90:", tree.contains(90));

// MINIMUM AND MAXIMUM
console.log("\n--- MINIMUM AND MAXIMUM ---");

console.log("Minimum:", tree.getMinimum());
console.log("Maximum:", tree.getMaximum());

// UPDATE
console.log("\n--- UPDATE ---");

console.log("Update 25 to 35:", tree.update(25, 35));

console.log(
    "Update 35 to 40:",
    tree.update(35, 40),
    "(duplicate value)"
);

console.log("Inorder after update:", tree.inorder());

// DELETE
console.log("\n--- DELETE ---");

console.log("Remove leaf 10:", tree.remove(10));
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
tree.insert(150);

console.log("Inorder:", tree.inorder());