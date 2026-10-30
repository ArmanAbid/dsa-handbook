#include <iostream>
#include <string>
#include <cstring>

using namespace std;

// C++ STRINGS USING STD::STRING

// READ

bool getAt(const string& text, int index, char& value) {
    if (index < 0 || static_cast<size_t>(index) >= text.size()) {
        return false;
    }

    value = text[index];
    return true;
}

bool getFirst(const string& text, char& value) {
    if (text.empty()) {
        return false;
    }

    value = text.front();
    return true;
}

bool getLast(const string& text, char& value) {
    if (text.empty()) {
        return false;
    }

    value = text.back();
    return true;
}

void printString(const string& text) {
    cout << text << '\n';
}

// UPDATE

bool setAt(string& text, int index, char value) {
    if (index < 0 || static_cast<size_t>(index) >= text.size()) {
        return false;
    }

    text[index] = value;
    return true;
}

// INSERT

void appendText(string& text, const string& value) {
    text += value;
}

void prependText(string& text, const string& value) {
    text.insert(0, value);
}

// index == text.size() inserts at the end.
bool insertAt(string& text, int index, const string& value) {
    if (index < 0 || static_cast<size_t>(index) > text.size()) {
        return false;
    }

    text.insert(static_cast<size_t>(index), value);
    return true;
}

// DELETE

// Remove one character at the specified index.
bool removeAt(string& text, int index, char& removedValue) {
    if (index < 0 || static_cast<size_t>(index) >= text.size()) {
        return false;
    }

    removedValue = text[index];
    text.erase(static_cast<size_t>(index), 1);

    return true;
}

bool removeFirst(string& text, char& removedValue) {
    return removeAt(text, 0, removedValue);
}

bool removeLast(string& text, char& removedValue) {
    if (text.empty()) {
        return false;
    }

    removedValue = text.back();
    text.erase(text.size() - 1, 1);

    return true;
}

void clearString(string& text) {
    text.clear();
}

// SIZE AND BASIC PROPERTIES

size_t sizeOf(const string& text) {
    return text.size();
}

bool isEmpty(const string& text) {
    return text.empty();
}

// OTHER BASIC STRING OPERATIONS

// Extract the range [start, end).
// Start is included; end is excluded.
bool substringRange(
    const string& text,
    int start,
    int end,
    string& result
) {
    if (start < 0 ||
        end < start ||
        static_cast<size_t>(end) > text.size()) {
        return false;
    }

    result = text.substr(
        static_cast<size_t>(start),
        static_cast<size_t>(end - start)
    );

    return true;
}

string concatenate(const string& first, const string& second) {
    return first + second;
}

bool stringsEqual(const string& first, const string& second) {
    return first == second;
}

// C-STYLE STRINGS

void demonstrateCString() {
    cout << "\n==== C-STYLE STRING ====\n";

    // A character array with a fixed capacity of 20.
    char text[20] = "Hello";

    cout << "Original: " << text << '\n';

    // Read a character.
    cout << "First character: " << text[0] << '\n';

    // Update a character.
    text[0] = 'Y';

    cout << "After updating: " << text << '\n';

    // strlen counts characters before the null terminator.
    cout << "Length: " << strlen(text) << '\n';

    cout << "Buffer capacity: " << sizeof(text) << '\n';
}

// DEMONSTRATION

int main() {

    // Initialize a string using native C++ syntax.
    string text = "Hello";

    cout << "==== STD::STRING ====\n";

    cout << "Original: ";
    printString(text);

    // READ
    char value = '\0';

    if (getAt(text, 1, value)) {
        cout << "Character at index 1: " << value << '\n';
    }

    if (getFirst(text, value)) {
        cout << "First character: " << value << '\n';
    }

    if (getLast(text, value)) {
        cout << "Last character: " << value << '\n';
    }

    // UPDATE
    setAt(text, 0, 'Y');

    cout << "After updating: ";
    printString(text);

    // INSERT
    insertAt(text, 5, "!");
    appendText(text, " World");
    prependText(text, "Hi, ");

    cout << "After inserting: ";
    printString(text);

    // DELETE
    char removedValue = '\0';

    if (removeAt(text, 2, removedValue)) {
        cout << "Removed character: " << removedValue << '\n';
    }

    if (removeFirst(text, removedValue)) {
        cout << "Removed first character: " << removedValue << '\n';
    }

    if (removeLast(text, removedValue)) {
        cout << "Removed last character: " << removedValue << '\n';
    }

    cout << "After deleting: ";
    printString(text);

    // SIZE AND PROPERTIES
    cout << "Length: " << sizeOf(text) << '\n';
    cout << "Empty: " << (isEmpty(text) ? "true" : "false") << '\n';

    // SUBSTRING
    string part;

    if (substringRange(text, 0, 2, part)) {
        cout << "Substring [0, 2): " << part << '\n';
    }

    // CONCATENATION
    string combined = concatenate(text, "!!!");

    cout << "Concatenated: ";
    printString(combined);

    // COMPARISON
    cout << "Strings equal: "
         << (stringsEqual(text, combined) ? "true" : "false")
         << '\n';

    // CLEAR
    clearString(text);

    cout << "After clearing: \"" << text << "\"\n";
    cout << "Empty after clearing: "
         << (isEmpty(text) ? "true" : "false") << '\n';

    // C-STYLE STRING DEMONSTRATION
    demonstrateCString();

    return 0;
}
