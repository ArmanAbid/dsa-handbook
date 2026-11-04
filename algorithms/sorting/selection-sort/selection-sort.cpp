#include <iostream>
#include <vector>
using namespace std;

// SELECTION SORT
// Sorts the array in ascending order.
// Finds the minimum element in the unsorted portion
// and places it at the beginning of that portion.

void selectionSort(vector<int>& values) {
    vector<int>::size_type n = values.size();

    for (vector<int>::size_type i = 0; i + 1 < n; i++) {
        // Assume the current position contains the minimum.
        vector<int>::size_type minIndex = i;

        // Find the actual minimum in the remaining portion.
        for (vector<int>::size_type j = i + 1; j < n; j++) {
            if (values[j] < values[minIndex]) {
                minIndex = j;
            }
        }

        // Swap only when the minimum is not already in place.
        if (minIndex != i) {
            int temp = values[i];
            values[i] = values[minIndex];
            values[minIndex] = temp;
        }
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

    selectionSort(values);

    bool passed = values == expected;

    cout << description << ": ";
    printArray(values);

    cout << (passed ? " [PASSED]" : " [FAILED]") << endl;
}

// DEMONSTRATION

int main() {
    cout << "==== SELECTION SORT ====" << endl;

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

    selectionSort(values);

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

    return 0;
}