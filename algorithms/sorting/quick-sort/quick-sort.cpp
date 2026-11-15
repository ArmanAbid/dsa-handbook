#include <iostream>
#include <vector>
using namespace std;

// QUICK SORT RANGE
// Uses three-way partitioning:
//
// [left, less - 1]       Values smaller than pivot.
// [less, greater]        Values equal to pivot.
// [greater + 1, right]   Values greater than pivot.
//
// Recursively sorts the smaller partition and iteratively
// processes the larger partition to limit stack usage.

void quickSortRange(
    vector<int>& values,
    int left,
    int right
) {
    while (left < right) {
        // Choose the middle-position element as the pivot.
        int middle = left + (right - left) / 2;
        int pivot = values[middle];

        int less = left;
        int current = left;
        int greater = right;

        // THREE-WAY PARTITIONING
        while (current <= greater) {
            if (values[current] < pivot) {
                // Move smaller element into the left region.
                int temp = values[less];
                values[less] = values[current];
                values[current] = temp;

                less++;
                current++;

            } else if (values[current] > pivot) {
                // Move greater element into the right region.
                int temp = values[current];
                values[current] = values[greater];
                values[greater] = temp;

                greater--;

                // Do not increment current.
                // The incoming element still needs examination.

            } else {
                // Equal element belongs to the middle region.
                current++;
            }
        }

        // Calculate the sizes of the unsorted portions.
        int leftSize = less - left;
        int rightSize = right - greater;

        // Recursively sort the smaller portion.
        // Process the larger portion using the loop.
        if (leftSize < rightSize) {
            quickSortRange(
                values,
                left,
                less - 1
            );

            left = greater + 1;

        } else {
            quickSortRange(
                values,
                greater + 1,
                right
            );

            right = less - 1;
        }
    }
}


// QUICK SORT
// Sorts the original vector in ascending order.

void quickSort(vector<int>& values) {
    if (values.size() <= 1) {
        return;
    }

    quickSortRange(
        values,
        0,
        static_cast<int>(values.size()) - 1
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

    quickSort(values);

    bool passed = values == expected;

    cout << description << ": ";
    printArray(values);

    cout << (passed ? " [PASSED]" : " [FAILED]") << endl;
}


// DEMONSTRATION

int main() {
    cout << "==== QUICK SORT ====" << endl;

    // BASIC EXAMPLE
    cout << "\n--- BASIC SORTING ---" << endl;

    vector<int> values;

    int input[] = {
        8, 3, 5, 4, 7, 6, 1, 2
    };

    for (int i = 0; i < 8; i++) {
        values.push_back(input[i]);
    }

    cout << "Before sorting: ";
    printArray(values);
    cout << endl;

    quickSort(values);

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