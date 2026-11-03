#include <iostream>
#include <vector>
using namespace std;

// BINARY SEARCH
// Requires an array sorted in ascending order.
// Returns the first occurrence of the target.
// Returns -1 if the target is not found.

int binarySearch(const vector<int>& values, int target) {
    vector<int>::size_type left = 0;
    vector<int>::size_type right = values.size();

    // Search using a half-open interval [left, right).
    while (left < right) {
        vector<int>::size_type middle =
            left + (right - left) / 2;

        if (values[middle] < target) {
            // Target can only be in the right half.
            left = middle + 1;
        } else {
            // Keep the middle in the search range.
            // This allows us to find the first occurrence.
            right = middle;
        }
    }

    // Check whether the target exists at the final position.
    if (left < values.size() && values[left] == target) {
        return static_cast<int>(left);
    }

    return -1;
}

// Helper function for demonstration.
void testSearch(
    const vector<int>& values,
    int target,
    int expected,
    const char* description
) {
    int result = binarySearch(values, target);

    cout << description << ": " << result;

    if (result == expected) {
        cout << " [PASSED]";
    } else {
        cout << " [FAILED]";
    }

    cout << endl;
}

// DEMONSTRATION

int main() {
    cout << "==== BINARY SEARCH ====" << endl;

    vector<int> values;

    values.push_back(2);
    values.push_back(4);
    values.push_back(4);
    values.push_back(4);
    values.push_back(7);
    values.push_back(9);
    values.push_back(12);
    values.push_back(15);

    // DISPLAY ARRAY
    cout << "\nSorted array: ";

    for (vector<int>::size_type i = 0; i < values.size(); i++) {
        cout << values[i] << " ";
    }

    cout << endl;

    // BASIC SEARCH
    cout << "\n--- BASIC SEARCH ---" << endl;

    testSearch(values, 4, 1, "Search for 4");
    testSearch(values, 7, 4, "Search for 7");
    testSearch(values, 15, 7, "Search for 15");
    testSearch(values, 2, 0, "Search for 2");
    testSearch(values, 10, -1, "Search for 10");

    // EDGE CASES
    cout << "\n--- EDGE CASES ---" << endl;

    vector<int> emptyValues;

    testSearch(emptyValues, 10, -1, "Empty array");

    vector<int> singleValue;
    singleValue.push_back(42);

    testSearch(singleValue, 42, 0, "Single element found");
    testSearch(singleValue, 10, -1, "Single element not found");

    testSearch(values, 1, -1, "Target smaller than all elements");
    testSearch(values, 20, -1, "Target larger than all elements");

    vector<int> negativeValues;

    negativeValues.push_back(-10);
    negativeValues.push_back(-5);
    negativeValues.push_back(-2);
    negativeValues.push_back(0);
    negativeValues.push_back(5);

    testSearch(negativeValues, -5, 1, "Negative number");

    // DUPLICATE VALUES
    cout << "\n--- DUPLICATES ---" << endl;

    testSearch(values, 4, 1, "First occurrence of 4");

    vector<int> equalValues;

    equalValues.push_back(5);
    equalValues.push_back(5);
    equalValues.push_back(5);
    equalValues.push_back(5);

    testSearch(equalValues, 5, 0, "All elements equal");

    return 0;
}