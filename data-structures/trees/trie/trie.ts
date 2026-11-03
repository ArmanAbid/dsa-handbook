class TrieNode {
    children: Map<string, TrieNode>;
    isEndOfWord: boolean;

    constructor() {
        this.children = new Map<string, TrieNode>();
        this.isEndOfWord = false;
    }
}

class Trie {
    private root: TrieNode;
    private wordCount: number;

    constructor() {
        this.root = new TrieNode();
        this.wordCount = 0;
    }

    // INSERT: Add a word character by character.
    insert(word: string): boolean {
        let current = this.root;

        for (const character of word) {
            let child = current.children.get(character);

            if (child === undefined) {
                child = new TrieNode();
                current.children.set(character, child);
            }

            current = child;
        }

        // Do not insert duplicate words.
        if (current.isEndOfWord) {
            return false;
        }

        current.isEndOfWord = true;
        this.wordCount++;

        return true;
    }

    // Find the node corresponding to a complete prefix.
    private findNode(value: string): TrieNode | null {
        let current = this.root;

        for (const character of value) {
            const child = current.children.get(character);

            if (child === undefined) {
                return null;
            }

            current = child;
        }

        return current;
    }

    // SEARCH: Check whether an exact word exists.
    search(word: string): boolean {
        const node = this.findNode(word);

        return node !== null && node.isEndOfWord;
    }

    // STARTS WITH: Check whether a prefix exists.
    startsWith(prefix: string): boolean {
        return this.findNode(prefix) !== null;
    }

    // REMOVE: Remove a word and prune unused nodes.
    // Returns whether the current node can also be deleted.
    private removeNode(
        node: TrieNode,
        word: string,
        index: number
    ): { canDelete: boolean; removed: boolean } {

        // Reached the end of the word.
        if (index === word.length) {
            if (!node.isEndOfWord) {
                return {
                    canDelete: false,
                    removed: false
                };
            }

            node.isEndOfWord = false;

            return {
                canDelete: node.children.size === 0,
                removed: true
            };
        }

        const character = word[index];

        if (character === undefined) {
            return {
                canDelete: false,
                removed: false
            };
        }

        const child = node.children.get(character);

        if (child === undefined) {
            return {
                canDelete: false,
                removed: false
            };
        }

        const result = this.removeNode(
            child,
            word,
            index + 1
        );

        if (result.canDelete) {
            node.children.delete(character);
        }

        const canDelete =
            !node.isEndOfWord && node.children.size === 0;

        return {
            canDelete,
            removed: result.removed
        };
    }

    // REMOVE: Delete a complete word.
    remove(word: string): boolean {
        // The root itself is never deleted.
        const result = this.removeNode(
            this.root,
            word,
            0
        );

        if (result.removed) {
            this.wordCount--;
        }

        return result.removed;
    }

    // Collect all complete words.
    private collectWords(
        node: TrieNode,
        currentWord: string,
        words: string[]
    ): void {
        if (node.isEndOfWord) {
            words.push(currentWord);
        }

        for (const [character, child] of node.children) {
            this.collectWords(
                child,
                currentWord + character,
                words
            );
        }
    }

    // LIST WORDS: Get all stored words.
    getWords(): string[] {
        const words: string[] = [];

        this.collectWords(this.root, "", words);

        return words;
    }

    // SIZE: Get the number of stored words.
    sizeOf(): number {
        return this.wordCount;
    }

    // CHECK: Check whether the Trie is empty.
    isEmpty(): boolean {
        return this.wordCount === 0;
    }

    // DISPLAY: Show all stored words.
    printWords(): void {
        const words = this.getWords();

        if (words.length === 0) {
            console.log("Words: Empty");
        } else {
            console.log("Words:", words);
        }
    }

    // CLEAR: Remove all nodes.
    clearTrie(): void {
        this.root = new TrieNode();
        this.wordCount = 0;
    }
}

// DEMONSTRATION

const trie = new Trie();

console.log("==== TRIE ====");

// INSERT
console.log("\n--- INSERT ---");

trie.insert("car");
trie.insert("care");
trie.insert("cat");
trie.insert("dog");

trie.printWords();

console.log("Insert duplicate car:", trie.insert("car"));

// SEARCH
console.log("\n--- SEARCH ---");

console.log("Search car:", trie.search("car"));
console.log("Search care:", trie.search("care"));
console.log("Search ca:", trie.search("ca"));
console.log("Search cow:", trie.search("cow"));

// PREFIX CHECK
console.log("\n--- PREFIX CHECK ---");

console.log("Starts with ca:", trie.startsWith("ca"));
console.log("Starts with do:", trie.startsWith("do"));
console.log("Starts with z:", trie.startsWith("z"));

// REMOVE
console.log("\n--- REMOVE ---");

console.log("Remove car:", trie.remove("car"));

// care should still exist because it shares the "car" path.
console.log("Search car:", trie.search("car"));
console.log("Search care:", trie.search("care"));

trie.printWords();

console.log("Remove missing cow:", trie.remove("cow"));

// SIZE AND EMPTY CHECK
console.log("\n--- SIZE AND EMPTY CHECK ---");

console.log("Size:", trie.sizeOf());
console.log("Is empty:", trie.isEmpty());

// CLEAR
console.log("\n--- CLEAR ---");

trie.clearTrie();

trie.printWords();

console.log("Size after clearing:", trie.sizeOf());
console.log("Is empty:", trie.isEmpty());

// INSERT AFTER CLEAR
console.log("\n--- INSERT AFTER CLEAR ---");

trie.insert("hello");
trie.insert("help");

trie.printWords();