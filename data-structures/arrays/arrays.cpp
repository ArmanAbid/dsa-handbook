#include <iostream>
#include <vector>
#include <cstddef>
using namespace std;

// TRADITIONAL FIXED-SIZE ARRAYS

// READ

template <size_t N>
bool getAt(
    const int (&arr)[N],
    int size,
    int index,
    int& value
) {
    if (size < 0 || size > static_cast<int>(N) ||
        index < 0 || index >= size) {
        return false;
    }

    value = arr[index];
    return true;
}

template <size_t N>
bool getFirst(
    const int (&arr)[N],
    int size,
    int& value
) {
    if (size <= 0 || size > static_cast<int>(N)) {
        return false;
    }

    value = arr[0];
    return true;
}

template <size_t N>
bool getLast(
    const int (&arr)[N],
    int size,
    int& value
) {
    if (size <= 0 || size > static_cast<int>(N)) {
        return false;
    }

    value = arr[size - 1];
    return true;
}

template <size_t N>
void printArray(const int (&arr)[N], int size) {
    if (size < 0 || size > static_cast<int>(N)) {
        cout << "Invalid size\n";
        return;
    }

    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }

    cout << '\n';
}


// UPDATE

template <size_t N>
bool setAt(
    int (&arr)[N],
    int size,
    int index,
    int value
) {
    if (size < 0 || size > static_cast<int>(N) ||
        index < 0 || index >= size) {
        return false;
    }

    arr[index] = value;
    return true;
}


// INSERT

// Insert an element at the end.
template <size_t N>
bool append(
    int (&arr)[N],
    int& size,
    int value
) {
    if (size < 0 || size >= static_cast<int>(N)) {
        return false;
    }

    arr[size] = value;
    size++;

    return true;
}


// Insert an element at the beginning.
template <size_t N>
bool prepend(
    int (&arr)[N],
    int& size,
    int value
) {
    if (size < 0 || size >= static_cast<int>(N)) {
        return false;
    }

    for (int i = size; i > 0; i--) {
        arr[i] = arr[i - 1];
    }

    arr[0] = value;
    size++;

    return true;
}


// Insert at a specific index.
// index == size means insertion at the end.
template <size_t N>
bool insertAt(
    int (&arr)[N],
    int& size,
    int index,
    int value
) {
    if (size < 0 || size >= static_cast<int>(N) ||
        index < 0 || index > size) {
        return false;
    }

    for (int i = size; i > index; i--) {
        arr[i] = arr[i - 1];
    }

    arr[index] = value;
    size++;

    return true;
}


// DELETE

// Remove an element at a specific index.
template <size_t N>
bool removeAt(
    int (&arr)[N],
    int& size,
    int index,
    int& removedValue
) {
    if (size < 0 || size > static_cast<int>(N) ||
        index < 0 || index >= size) {
        return false;
    }

    removedValue = arr[index];

    for (int i = index; i < size - 1; i++) {
        arr[i] = arr[i + 1];
    }

    size--;

    return true;
}


// Remove the first element.
template <size_t N>
bool popFront(
    int (&arr)[N],
    int& size,
    int& removedValue
) {
    return removeAt(arr, size, 0, removedValue);
}


// Remove the last element.
template <size_t N>
bool popBack(
    int (&arr)[N],
    int& size,
    int& removedValue
) {
    if (size <= 0 || size > static_cast<int>(N)) {
        return false;
    }

    removedValue = arr[size - 1];
    size--;

    return true;
}


// Remove all active elements.
template <size_t N>
void clearArray(
    int (&arr)[N],
    int& size
) {
    size = 0;
}


// SIZE AND CAPACITY

int sizeOf(int size) {
    return size;
}

bool isEmpty(int size) {
    return size == 0;
}

template <size_t N>
int capacityOf(const int (&arr)[N]) {
    return static_cast<int>(sizeof(arr) / sizeof(arr[0]));
}



// DYNAMIC ARRAYS USING STD::VECTOR

void demonstrateVector() {

    cout << "\n==== DYNAMIC ARRAY: VECTOR ====\n";

    // Create a dynamic array using std::vector.
    vector<int> arr;

    // INSERT

    // Append elements.
    arr.push_back(10);
    arr.push_back(20);
    arr.push_back(30);

    cout << "After appending: ";

    for (size_t i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }

    cout << '\n';

    // Insert at the beginning.
    arr.insert(arr.begin(), 5);

    // Insert at a specific index.
    arr.insert(arr.begin() + 2, 15);

    cout << "After inserting: ";

    for (size_t i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }

    cout << '\n';


    // READ

    cout << "Element at index 2: " << arr[2] << '\n';
    cout << "First element: " << arr.front() << '\n';
    cout << "Last element: " << arr.back() << '\n';


    // UPDATE

    arr[2] = 25;

    cout << "After updating: ";

    for (size_t i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }

    cout << '\n';


    // DELETE

    // Remove at a specific index.
    arr.erase(arr.begin() + 1);

    // Remove the first element.
    arr.erase(arr.begin());

    // Remove the last element.
    arr.pop_back();

    cout << "After deleting: ";

    for (size_t i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }

    cout << '\n';


    // SIZE AND CAPACITY

    cout << "Size: " << arr.size() << '\n';
    cout << "Capacity: " << arr.capacity() << '\n';
    cout << "Empty: " << (arr.empty() ? "true" : "false") << '\n';


    // Resize changes the number of elements.
    arr.resize(5, 0);

    cout << "After resizing: ";

    for (size_t i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }

    cout << '\n';


    // Reserve changes capacity without changing size.
    arr.reserve(10);

    cout << "Capacity after reserve: " << arr.capacity() << '\n';


    // Clear removes all elements.
    arr.clear();

    cout << "Size after clearing: " << arr.size() << '\n';
    cout << "Empty after clearing: "
         << (arr.empty() ? "true" : "false") << '\n';
}



// MAIN


int main() {

    cout << "==== FIXED-SIZE ARRAY ====\n";

    // Traditional C++ array.
    //
    // Physical capacity = 10
    // Current logical size = 5
    //
    // We use extra capacity so that insertion
    // operations can be demonstrated.

    int arr[10] = {10, 20, 30, 40, 50};
    int size = 5;

    cout << "Initial array: ";
    printArray(arr, size);


    // READ

    int value = 0;

    if (getAt(arr, size, 2, value)) {
        cout << "Element at index 2: " << value << '\n';
    }

    if (getFirst(arr, size, value)) {
        cout << "First element: " << value << '\n';
    }

    if (getLast(arr, size, value)) {
        cout << "Last element: " << value << '\n';
    }


    // UPDATE

    setAt(arr, size, 2, 35);


    // INSERT

    insertAt(arr, size, 2, 25);

    append(arr, size, 60);

    prepend(arr, size, 5);

    cout << "After updates and insertions: ";
    printArray(arr, size);


    // DELETE

    int removedValue = 0;

    if (removeAt(arr, size, 1, removedValue)) {
        cout << "Removed at index 1: " << removedValue << '\n';
    }

    if (popFront(arr, size, removedValue)) {
        cout << "Removed first element: " << removedValue << '\n';
    }

    if (popBack(arr, size, removedValue)) {
        cout << "Removed last element: " << removedValue << '\n';
    }

    cout << "Current array: ";
    printArray(arr, size);


    // SIZE AND CAPACITY

    cout << "Size: " << sizeOf(size) << '\n';
    cout << "Capacity: " << capacityOf(arr) << '\n';

    cout << "Empty: "
         << (isEmpty(size) ? "true" : "false") << '\n';


    // CLEAR

    clearArray(arr, size);

    cout << "Size after clearing: " << sizeOf(size) << '\n';

    cout << "Empty after clearing: "
         << (isEmpty(size) ? "true" : "false") << '\n';


    // DYNAMIC ARRAY DEMONSTRATION

    demonstrateVector();

    return 0;
}
