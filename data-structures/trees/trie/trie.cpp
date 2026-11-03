#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

struct TrieNode {
    map<char, TrieNode*> children;
    bool isEndOfWord;

    TrieNode() {
        isEndOfWord = false;
    }
};

class Trie {
private:
    TrieNode* root;
    int wordCount;

    // SEARCH: Find the node corresponding to a complete prefix.
    TrieNode* findNode(const string& value) const {
        TrieNode* current = root;

        for (unsigned int i = 0; i < value.length(); i++) {
            char character = value[i];

            map<char, TrieNode*>::iterator it =
                current->children.find(character);

            if (it == current->children.end()) {
                return NULL;
            }

            current = it->second;
        }

        return current;
    }

    // REMOVE: Remove a word and prune unused nodes.
    // Returns true when the current node can also be deleted.
    bool removeNode(
        TrieNode* node,
        const string& word,
        unsigned int index,
        bool& removed
    ) {
        // Reached the end of the word.
        if (index == word.length()) {
            if (!node->isEndOfWord) {
                return false;
            }

            node->isEndOfWord = false;
            removed = true;

            return node->children.empty();
        }

        char character = word[index];

        map<char, TrieNode*>::iterator it =
            node->children.find(character);

        if (it == node->children.end()) {
            return false;
        }

        TrieNode* child = it->second;

        bool childCanBeDeleted = removeNode(
            child,
            word,
            index + 1,
            removed
        );

        if (childCanBeDeleted) {
            delete child;
            node->children.erase(it);
        }

        return !node->isEndOfWord && node->children.empty();
    }

    // Collect all complete words.
    void collectWords(
        TrieNode* node,
        string& currentWord,
        vector<string>& words
    ) const {
        if (node->isEndOfWord) {
            words.push_back(currentWord);
        }

        for (
            map<char, TrieNode*>::const_iterator it =
                node->children.begin();
            it != node->children.end();
            ++it
        ) {
            currentWord.push_back(it->first);

            collectWords(it->second, currentWord, words);

            currentWord.erase(currentWord.length() - 1);
        }
    }

    // Release all nodes recursively.
    void destroyTree(TrieNode* node) {
        if (node == NULL) {
            return;
        }

        for (
            map<char, TrieNode*>::iterator it =
                node->children.begin();
            it != node->children.end();
            ++it
        ) {
            destroyTree(it->second);
        }

        delete node;
    }

    // Prevent accidental shallow copying of owned pointers.
    Trie(const Trie&);
    Trie& operator=(const Trie&);

public:
    // CREATE: Initialize an empty Trie.
    Trie() {
        root = new TrieNode();
        wordCount = 0;
    }

    // INSERT: Add a word.
    bool insert(const string& word) {
        TrieNode* current = root;

        for (unsigned int i = 0; i < word.length(); i++) {
            char character = word[i];

            map<char, TrieNode*>::iterator it =
                current->children.find(character);

            if (it == current->children.end()) {
                TrieNode* newNode = new TrieNode();

                current->children[character] = newNode;
                current = newNode;
            } else {
                current = it->second;
            }
        }

        // Do not insert duplicate words.
        if (current->isEndOfWord) {
            return false;
        }

        current->isEndOfWord = true;
        wordCount++;

        return true;
    }

    // SEARCH: Check whether an exact word exists.
    bool search(const string& word) const {
        TrieNode* node = findNode(word);

        return node != NULL && node->isEndOfWord;
    }

    // STARTS WITH: Check whether a prefix exists.
    bool startsWith(const string& prefix) const {
        return findNode(prefix) != NULL;
    }

    // REMOVE: Delete a complete word.
    bool remove(const string& word) {
        bool removed = false;

        // The root itself is never deleted.
        removeNode(root, word, 0, removed);

        if (removed) {
            wordCount--;
        }

        return removed;
    }

    // SIZE: Get the number of stored words.
    int sizeOf() const {
        return wordCount;
    }

    // CHECK: Check whether the Trie is empty.
    bool isEmpty() const {
        return wordCount == 0;
    }

    // LIST WORDS: Get all complete words.
    vector<string> getWords() const {
        vector<string> words;
        string currentWord = "";

        collectWords(root, currentWord, words);

        return words;
    }

    // DISPLAY: Show all stored words.
    void printWords() const {
        vector<string> words = getWords();

        cout << "Words: ";

        if (words.empty()) {
            cout << "Empty";
        } else {
            cout << "{ ";

            for (unsigned int i = 0; i < words.size(); i++) {
                if (i > 0) {
                    cout << ", ";
                }

                if (words[i].empty()) {
                    cout << "\"\"";
                } else {
                    cout << words[i];
                }
            }

            cout << " }";
        }

        cout << endl;
    }

    // CLEAR: Remove all nodes and create a new root.
    void clearTrie() {
        destroyTree(root);

        root = new TrieNode();
        wordCount = 0;
    }

    // Destructor: Automatically free remaining nodes.
    ~Trie() {
        destroyTree(root);
    }
};

// DEMONSTRATION

int main() {
    Trie trie;

    cout << "==== TRIE ====" << endl;

    // INSERT
    cout << "\n--- INSERT ---" << endl;

    trie.insert("car");
    trie.insert("care");
    trie.insert("cat");
    trie.insert("dog");

    trie.printWords();

    cout << "Insert duplicate car: "
         << (trie.insert("car") ? "Inserted" : "Already exists")
         << endl;

    // SEARCH
    cout << "\n--- SEARCH ---" << endl;

    cout << "Search car: "
         << (trie.search("car") ? "Found" : "Not found") << endl;

    cout << "Search care: "
         << (trie.search("care") ? "Found" : "Not found") << endl;

    cout << "Search ca: "
         << (trie.search("ca") ? "Found" : "Not found") << endl;

    cout << "Search cow: "
         << (trie.search("cow") ? "Found" : "Not found") << endl;

    // PREFIX CHECK
    cout << "\n--- PREFIX CHECK ---" << endl;

    cout << "Starts with ca: "
         << (trie.startsWith("ca") ? "Yes" : "No") << endl;

    cout << "Starts with do: "
         << (trie.startsWith("do") ? "Yes" : "No") << endl;

    cout << "Starts with z: "
         << (trie.startsWith("z") ? "Yes" : "No") << endl;

    // REMOVE
    cout << "\n--- REMOVE ---" << endl;

    cout << "Remove car: "
         << (trie.remove("car") ? "Removed" : "Not found") << endl;

    // care should still exist because it shares the "car" path.
    cout << "Search car: "
         << (trie.search("car") ? "Found" : "Not found") << endl;

    cout << "Search care: "
         << (trie.search("care") ? "Found" : "Not found") << endl;

    trie.printWords();

    cout << "Remove missing cow: "
         << (trie.remove("cow") ? "Removed" : "Not found") << endl;

    // SIZE AND EMPTY CHECK
    cout << "\n--- SIZE AND EMPTY CHECK ---" << endl;

    cout << "Size: " << trie.sizeOf() << endl;
    cout << "Is empty: " << (trie.isEmpty() ? "Yes" : "No") << endl;

    // CLEAR
    cout << "\n--- CLEAR ---" << endl;

    trie.clearTrie();

    trie.printWords();

    cout << "Size after clearing: " << trie.sizeOf() << endl;
    cout << "Is empty: " << (trie.isEmpty() ? "Yes" : "No") << endl;

    // INSERT AFTER CLEAR
    cout << "\n--- INSERT AFTER CLEAR ---" << endl;

    trie.insert("hello");
    trie.insert("help");

    trie.printWords();

    return 0;
}