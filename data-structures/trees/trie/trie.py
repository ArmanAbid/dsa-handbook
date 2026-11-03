from typing import Dict, List, Tuple

class _TrieNode:
    def __init__(self):
        self.children: Dict[str, "_TrieNode"] = {}
        self.is_end_of_word = False


class Trie:
    def __init__(self):
        self._root = _TrieNode()
        self._size = 0

    # INSERT: Add a word character by character.
    def insert(self, word: str) -> bool:
        current = self._root

        for character in word:
            if character not in current.children:
                current.children[character] = _TrieNode()

            current = current.children[character]

        # Do not insert duplicate words.
        if current.is_end_of_word:
            return False

        current.is_end_of_word = True
        self._size += 1

        return True

    # Find the node corresponding to a complete prefix.
    def _find_node(self, value: str) -> _TrieNode | None:
        current = self._root

        for character in value:
            if character not in current.children:
                return None

            current = current.children[character]

        return current

    # SEARCH: Check whether an exact word exists.
    def search(self, word: str) -> bool:
        node = self._find_node(word)

        return node is not None and node.is_end_of_word

    # STARTS WITH: Check whether a prefix exists.
    def starts_with(self, prefix: str) -> bool:
        return self._find_node(prefix) is not None

    # REMOVE: Remove a word and prune unused nodes.
    # Returns whether the current node can also be deleted.
    def _remove_node(
        self,
        node: _TrieNode,
        word: str,
        index: int
    ) -> Tuple[bool, bool]:

        # Reached the end of the word.
        if index == len(word):
            if not node.is_end_of_word:
                return False, False

            node.is_end_of_word = False

            return len(node.children) == 0, True

        character = word[index]
        child = node.children.get(character)

        if child is None:
            return False, False

        child_can_be_deleted, removed = self._remove_node(
            child,
            word,
            index + 1
        )

        if child_can_be_deleted:
            del node.children[character]

        can_be_deleted = (
            not node.is_end_of_word and len(node.children) == 0
        )

        return can_be_deleted, removed

    # REMOVE: Delete a complete word.
    def remove(self, word: str) -> bool:
        # The root itself is never deleted.
        _, removed = self._remove_node(
            self._root,
            word,
            0
        )

        if removed:
            self._size -= 1

        return removed

    # LIST WORDS: Collect all complete words.
    def get_words(self) -> List[str]:
        words = []

        def collect(
            node: _TrieNode,
            current_word: str
        ) -> None:
            if node.is_end_of_word:
                words.append(current_word)

            for character, child in node.children.items():
                collect(child, current_word + character)

        collect(self._root, "")

        return words

    # SIZE: Get the number of stored words.
    def size(self) -> int:
        return self._size

    # CHECK: Check whether the Trie is empty.
    def is_empty(self) -> bool:
        return self._size == 0

    # DISPLAY: Show all stored words.
    def print_words(self) -> None:
        words = self.get_words()

        if not words:
            print("Words: Empty")
        else:
            print("Words:", words)

    # CLEAR: Remove all nodes.
    def clear(self) -> None:
        self._root = _TrieNode()
        self._size = 0


# DEMONSTRATION

trie = Trie()

print("==== TRIE ====")

# INSERT
print("\n--- INSERT ---")

trie.insert("car")
trie.insert("care")
trie.insert("cat")
trie.insert("dog")

trie.print_words()

print("Insert duplicate car:", trie.insert("car"))

# SEARCH
print("\n--- SEARCH ---")

print("Search car:", trie.search("car"))
print("Search care:", trie.search("care"))
print("Search ca:", trie.search("ca"))
print("Search cow:", trie.search("cow"))

# PREFIX CHECK
print("\n--- PREFIX CHECK ---")

print("Starts with ca:", trie.starts_with("ca"))
print("Starts with do:", trie.starts_with("do"))
print("Starts with z:", trie.starts_with("z"))

# REMOVE
print("\n--- REMOVE ---")

print("Remove car:", trie.remove("car"))

# care should still exist because it shares the "car" path.
print("Search car:", trie.search("car"))
print("Search care:", trie.search("care"))

trie.print_words()

print("Remove missing cow:", trie.remove("cow"))

# SIZE AND EMPTY CHECK
print("\n--- SIZE AND EMPTY CHECK ---")

print("Size:", trie.size())
print("Is empty:", trie.is_empty())

# CLEAR
print("\n--- CLEAR ---")

trie.clear()

trie.print_words()

print("Size after clearing:", trie.size())
print("Is empty:", trie.is_empty())

# INSERT AFTER CLEAR
print("\n--- INSERT AFTER CLEAR ---")

trie.insert("hello")
trie.insert("help")

trie.print_words()