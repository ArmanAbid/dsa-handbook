#include <iostream>
#include <vector>
#include <cstddef>
using namespace std;

// COUNTING SORT
// Supports negative and positive integers.
// Sorts the original array in ascending order.
// Uses cumulative counts to preserve stability.

void countingSort(vector<int>& values) {
    if (values.size() <= 1) {
        return;
    }

    // STEP 1: Find minimum and maximum values.
    int minimum = values[0];
    int maximum = values[0];

    for (vector<int>::size_type i = 1;
         i < values.size(); i++) {

        if (values[i] < minimum) {
            minimum = values[i];
        }

        if (values[i] > maximum) {
            maximum = values[i];
        }
    }

    // Calculate the range using long long to avoid int overflow.
    long long range =
        static_cast<long long>(maximum) -
        static_cast<long long>(minimum) + 1;

    // STEP 2: Create the counting array.
    vector<size_t> counts(
        static_cast<size_t>(range),
        0
    );

    // Count the occurrences of each value.
    for (vector<int>::size_type i = 0;
         i < values.size(); i++) {

        size_t index = static_cast<size_t>(
            static_cast<long long>(values[i]) - minimum
        );

        counts[index]++;
    }

    // STEP 3: Calculate cumulative counts.
    for (size_t i = 1; i < counts.size(); i++) {
        counts[i] += counts[i - 1];
    }

    // STEP 4: Construct the output array.
    vector<int> output(values.size());

    // Traverse backwards to preserve stability.
    for (vector<int>::size_type i = values.size(); i > 0; i--) {
        int value = values[i - 1];

        size_t index = static_cast<size_t>(
            static_cast<long long>(value) - minimum
        );

        counts[index]--;

        output[counts[index]] = value;
    }

    // Copy the sorted output back into the original array.
    for (vector<int>::size_type i = 0; i < values.size(); i++) {
        values[i] = output[i];
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

    countingSort(values);

    bool passed = values == expected;

    cout << description << ": ";
    printArray(values);

    cout << (passed ? " [PASSED]" : " [FAILED]") << endl;
}


// DEMONSTRATION

int main() {
    cout << "==== COUNTING SORT ====" << endl;

    // BASIC EXAMPLE
    cout << "\n--- BASIC SORTING ---" << endl;

    vector<int> values;

    values.push_back(4);
    values.push_back(2);
    values.push_back(2);
    values.push_back(8);
    values.push_back(3);
    values.push_back(3);
    values.push_back(1);

    cout << "Before sorting: ";
    printArray(values);
    cout << endl;

    countingSort(values);

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
    negativeValues.push_back(-2);
    negativeValues.push_back(-5);
    negativeValues.push_back(0);
    negativeValues.push_back(3);
    negativeValues.push_back(-2);

    vector<int> negativeExpected;

    negativeExpected.push_back(-5);
    negativeExpected.push_back(-5);
    negativeExpected.push_back(-2);
    negativeExpected.push_back(-2);
    negativeExpected.push_back(0);
    negativeExpected.push_back(3);

    testSort(
        negativeValues,
        negativeExpected,
        "Negative and positive values"
    );

    vector<int> mixedValues;

    mixedValues.push_back(0);
    mixedValues.push_back(-3);
    mixedValues.push_back(2);
    mixedValues.push_back(-1);
    mixedValues.push_back(3);
    mixedValues.push_back(-2);

    vector<int> mixedExpected;

    mixedExpected.push_back(-3);
    mixedExpected.push_back(-2);
    mixedExpected.push_back(-1);
    mixedExpected.push_back(0);
    mixedExpected.push_back(2);
    mixedExpected.push_back(3);

    testSort(
        mixedValues,
        mixedExpected,
        "Mixed negative and positive values"
    );

    return 0;
}