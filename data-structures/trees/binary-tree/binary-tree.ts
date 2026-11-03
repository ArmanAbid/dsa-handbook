export { };

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

class BinaryTree {
    private root: TreeNode | null;
    private length: number;

    constructor() {
        this.root = null;
        this.length = 0;
    }

    // Find the first matching node using level-order traversal.
    private findNode(value: number): TreeNode | null {
        if (this.root === null) {
            return null;
        }

        const nodes: TreeNode[] = [this.root];
        let index = 0;

        while (index < nodes.length) {
            const current = nodes[index];
            index++;

            if (current === undefined) {
                continue;
            }

            if (current.data === value) {
                return current;
            }

            if (current.left !== null) {
                nodes.push(current.left);
            }

            if (current.right !== null) {
                nodes.push(current.right);
            }
        }

        return null;
    }

    // INSERT: Add a node at the first available position.
    insert(value: number): boolean {
        const newNode = new TreeNode(value);

        // Insert the first node as the root.
        if (this.root === null) {
            this.root = newNode;
            this.length++;
            return true;
        }

        const nodes: TreeNode[] = [this.root];
        let index = 0;

        while (index < nodes.length) {
            const current = nodes[index];
            index++;

            if (current === undefined) {
                continue;
            }

            // Check the left child first.
            if (current.left === null) {
                current.left = newNode;
                this.length++;
                return true;
            }

            nodes.push(current.left);

            // Then check the right child.
            if (current.right === null) {
                current.right = newNode;
                this.length++;
                return true;
            }

            nodes.push(current.right);
        }

        return false;
    }

    // SEARCH: Check whether a value exists.
    contains(value: number): boolean {
        return this.findNode(value) !== null;
    }

    // UPDATE: Change the value of an existing node.
    update(oldValue: number, newValue: number): boolean {
        const node = this.findNode(oldValue);

        if (node === null) {
            return false;
        }

        node.data = newValue;
        return true;
    }

    // DELETE: Remove a node and preserve the complete shape.
    remove(value: number): boolean {
        if (this.root === null) {
            return false;
        }

        const nodes: {
            node: TreeNode;
            parent: TreeNode | null;
        }[] = [
                {
                    node: this.root,
                    parent: null
                }
            ];

        let index = 0;

        let target: TreeNode | null = null;
        let deepest: TreeNode | null = null;
        let deepestParent: TreeNode | null = null;

        while (index < nodes.length) {
            const item = nodes[index];
            index++;

            if (item === undefined) {
                continue;
            }

            const current = item.node;
            const parent = item.parent;

            // Record the first matching node.
            if (target === null && current.data === value) {
                target = current;
            }

            // The final node visited is the deepest,
            // rightmost node in level-order traversal.
            deepest = current;
            deepestParent = parent;

            if (current.left !== null) {
                nodes.push({
                    node: current.left,
                    parent: current
                });
            }

            if (current.right !== null) {
                nodes.push({
                    node: current.right,
                    parent: current
                });
            }
        }

        if (target === null || deepest === null) {
            return false;
        }

        // Replace the target value with the deepest node value.
        target.data = deepest.data;

        // Remove the deepest node.
        if (deepestParent === null) {
            this.root = null;
        } else if (deepestParent.right === deepest) {
            deepestParent.right = null;
        } else {
            deepestParent.left = null;
        }

        this.length--;
        return true;
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

const tree = new BinaryTree();

console.log("==== BINARY TREE ====");

// INSERT
console.log("\n--- INSERT ---");

tree.insert(10);
tree.insert(20);
tree.insert(30);
tree.insert(40);
tree.insert(50);
tree.insert(60);
tree.insert(70);

console.log("Inserted 7 nodes.");

// TRAVERSALS
console.log("\n--- TRAVERSALS ---");

console.log("Preorder:", tree.preorder());
console.log("Inorder:", tree.inorder());
console.log("Postorder:", tree.postorder());
console.log("Level-order:", tree.levelOrder());

// SEARCH
console.log("\n--- SEARCH ---");

console.log("Contains 50:", tree.contains(50));
console.log("Contains 90:", tree.contains(90));

// UPDATE
console.log("\n--- UPDATE ---");

if (tree.update(50, 55)) {
    console.log("Updated 50 to 55.");
}

console.log("Level-order after update:", tree.levelOrder());

// DELETE
console.log("\n--- DELETE ---");

if (tree.remove(20)) {
    console.log("Removed 20.");
}

console.log("Level-order after removal:", tree.levelOrder());
console.log("Contains 20:", tree.contains(20));

// SIZE AND EMPTY CHECK
console.log("\n--- SIZE AND EMPTY CHECK ---");

console.log("Size:", tree.sizeOf());
console.log("Is empty:", tree.isEmpty());

// CLEAR
console.log("\n--- CLEAR ---");

tree.clearTree();

console.log("Size after clearing:", tree.sizeOf());
console.log("Is empty:", tree.isEmpty());
console.log("Level-order after clearing:", tree.levelOrder());

// INSERT AFTER CLEAR
console.log("\n--- INSERT AFTER CLEAR ---");

tree.insert(100);
tree.insert(200);

console.log("Level-order:", tree.levelOrder());