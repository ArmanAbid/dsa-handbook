#include <iostream>
#include <vector>
using namespace std;

// MERGE
// Combines two sorted portions:
// [left, middle) and [middle, right).

void merge(
    vector<int>& values,
    vector<int>& temp,
    vector<int>::size_type left,
    vector<int>::size_type middle,
    vector<int>::size_type right
) {
    vector<int>::size_type i = left;
    vector<int>::size_type j = middle;
    vector<int>::size_type k = left;

    // Compare elements from both halves.
    while (i < middle && j < right) {
        // Select the left element first when values are equal.
        // This preserves stability.
        if (values[i] <= values[j]) {
            temp[k] = values[i];
            i++;
        } else {
            temp[k] = values[j];
            j++;
        }

        k++;
    }

    // Copy remaining elements from the left half.
    while (i < middle) {
        temp[k] = values[i];

        i++;
        k++;
    }

    // Copy remaining elements from the right half.
    while (j < right) {
        temp[k] = values[j];

        j++;
        k++;
    }

    // Copy the merged portion back into the original array.
    for (vector<int>::size_type index = left;
         index < right; index++) {
        values[index] = temp[index];
    }
}


// MERGE SORT RECURSIVE HELPER
// Sorts the half-open range [left, right).

void mergeSortRange(
    vector<int>& values,
    vector<int>& temp,
    vector<int>::size_type left,
    vector<int>::size_type right
) {
    // A range containing zero or one element is already sorted.
    if (right - left <= 1) {
        return;
    }

    // Divide the range into two halves.
    vector<int>::size_type middle =
        left + (right - left) / 2;

    // Sort the left half.
    mergeSortRange(values, temp, left, middle);

    // Sort the right half.
    mergeSortRange(values, temp, middle, right);

    // Merge the two sorted halves.
    merge(values, temp, left, middle, right);
}


// MERGE SORT
// Sorts the original array in ascending order.

void mergeSort(vector<int>& values) {
    if (values.size() <= 1) {
        return;
    }

    // Allocate one temporary array and reuse it for all merges.
    vector<int> temp(values.size());

    mergeSortRange(
        values,
        temp,
        0,
        values.size()
    );
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

    mergeSort(values);

    bool passed = values == expected;

    cout << description << ": ";
    printArray(values);

    cout << (passed ? " [PASSED]" : " [FAILED]") << endl;
}


// DEMONSTRATION

int main() {
    cout << "==== MERGE SORT ====" << endl;

    // BASIC EXAMPLE
    cout << "\n--- BASIC SORTING ---" << endl;

    vector<int> values;

    values.push_back(8);
    values.push_back(3);
    values.push_back(5);
    values.push_back(4);
    values.push_back(7);
    values.push_back(6);
    values.push_back(1);
    values.push_back(2);

    cout << "Before sorting: ";
    printArray(values);
    cout << endl;

    mergeSort(values);

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

    vector<int> twoValues;
    twoValues.push_back(9);
    twoValues.push_back(3);

    vector<int> twoExpected;
    twoExpected.push_back(3);
    twoExpected.push_back(9);

    testSort(
        twoValues,
        twoExpected,
        "Two elements"
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

    vector<int> oddValues;

    oddValues.push_back(9);
    oddValues.push_back(1);
    oddValues.push_back(7);
    oddValues.push_back(3);
    oddValues.push_back(5);

    vector<int> oddExpected;

    oddExpected.push_back(1);
    oddExpected.push_back(3);
    oddExpected.push_back(5);
    oddExpected.push_back(7);
    oddExpected.push_back(9);

    testSort(
        oddValues,
        oddExpected,
        "Odd-sized array"
    );

    return 0;
}