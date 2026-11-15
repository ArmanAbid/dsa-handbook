#include <iostream>
#include <vector>
using namespace std;

// INSERTION SORT
// Sorts the array in ascending order.
// Builds a sorted portion by inserting each new element
// into its correct position.

void insertionSort(vector<int>& values) {
    vector<int>::size_type n = values.size();

    for (vector<int>::size_type i = 1; i < n; i++) {
        // Store the current element.
        int key = values[i];

        // Start comparing with the element immediately to the left.
        vector<int>::size_type j = i;

        // Shift elements greater than key one position to the right.
        while (j > 0 && values[j - 1] > key) {
            values[j] = values[j - 1];
            j--;
        }

        // Insert key into its correct position.
        values[j] = key;
    }
}

// Print an array.
void printArray(const vector<int>& values) {
    cout << "[";

    for (vector<int>::size_type i = 0; i < values.size(); i++) {
        cout << values[i];

        if (i + 1 < values.size()) {
            cout << ", ";
        }
    }

    cout << "]";
}

// Test a sorting case.
void testSort(
    const vector<int>& input,
    const vector<int>& expected,
    const char* description
) {
    vector<int> values = input;

    insertionSort(values);

    bool passed = values == expected;

    cout << description << ": ";
    printArray(values);

    cout << (passed ? " [PASSED]" : " [FAILED]") << endl;
}

// DEMONSTRATION

int main() {
    cout << "==== INSERTION SORT ====" << endl;

    // BASIC EXAMPLE
    cout << "\n--- BASIC SORTING ---" << endl;

    vector<int> values;

    values.push_back(5);
    values.push_back(3);
    values.push_back(8);
    values.push_back(4);
    values.push_back(2);

    cout << "Before sorting: ";
    printArray(values);
    cout << endl;

    insertionSort(values);

    cout << "After sorting:  ";
    printArray(values);
    cout << endl;

    // EDGE CASES
    cout << "\n--- EDGE CASES ---" << endl;

    vector<int> emptyValues;
    vector<int> emptyExpected;

    testSort(
        emptyValues,
        emptyExpected,
        "Empty array"
    );

    vector<int> singleValue;
    singleValue.push_back(42);

    testSort(
        singleValue,
        singleValue,
        "Single element"
    );

    vector<int> sortedValues;

    sortedValues.push_back(1);
    sortedValues.push_back(2);
    sortedValues.push_back(3);
    sortedValues.push_back(4);
    sortedValues.push_back(5);

    testSort(
        sortedValues,
        sortedValues,
        "Already sorted"
    );

    vector<int> reversedValues;

    reversedValues.push_back(5);
    reversedValues.push_back(4);
    reversedValues.push_back(3);
    reversedValues.push_back(2);
    reversedValues.push_back(1);

    testSort(
        reversedValues,
        sortedValues,
        "Reverse sorted"
    );

    vector<int> duplicateValues;

    duplicateValues.push_back(4);
    duplicateValues.push_back(2);
    duplicateValues.push_back(4);
    duplicateValues.push_back(1);
    duplicateValues.push_back(2);

    vector<int> duplicateExpected;

    duplicateExpected.push_back(1);
    duplicateExpected.push_back(2);
    duplicateExpected.push_back(2);
    duplicateExpected.push_back(4);
    duplicateExpected.push_back(4);

    testSort(
        duplicateValues,
        duplicateExpected,
        "Duplicate values"
    );

    vector<int> equalValues;

    equalValues.push_back(7);
    equalValues.push_back(7);
    equalValues.push_back(7);
    equalValues.push_back(7);

    testSort(
        equalValues,
        equalValues,
        "All elements equal"
    );

    vector<int> negativeValues;

    negativeValues.push_back(-5);
    negativeValues.push_back(3);
    negativeValues.push_back(-10);
    negativeValues.push_back(0);
    negativeValues.push_back(8);

    vector<int> negativeExpected;

    negativeExpected.push_back(-10);
    negativeExpected.push_back(-5);
    negativeExpected.push_back(0);
    negativeExpected.push_back(3);
    negativeExpected.push_back(8);

    testSort(
        negativeValues,
        negativeExpected,
        "Negative and positive values"
    );

    vector<int> nearlySortedValues;

    nearlySortedValues.push_back(1);
    nearlySortedValues.push_back(2);
    nearlySortedValues.push_back(4);
    nearlySortedValues.push_back(3);
    nearlySortedValues.push_back(5);

    vector<int> nearlySortedExpected;

    nearlySortedExpected.push_back(1);
    nearlySortedExpected.push_back(2);
    nearlySortedExpected.push_back(3);
    nearlySortedExpected.push_back(4);
    nearlySortedExpected.push_back(5);

    testSort(
        nearlySortedValues,
        nearlySortedExpected,
        "Nearly sorted"
    );

    return 0;
}