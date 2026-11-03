#include <iostream>
#include <vector>
using namespace std;

// LINEAR SEARCH
// Returns the index of the first occurrence.
// Returns -1 if the target is not found.

int linearSearch(const vector<int>& values, int target) {
    for (vector<int>::size_type i = 0; i < values.size(); i++) {
        if (values[i] == target) {
            return static_cast<int>(i);
        }
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
    int result = linearSearch(values, target);

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
    cout << "==== LINEAR SEARCH ====" << endl;

    vector<int> values;

    values.push_back(8);
    values.push_back(3);
    values.push_back(6);
    values.push_back(3);
    values.push_back(9);

    // DISPLAY ARRAY
    cout << "\nArray: ";

    for (vector<int>::size_type i = 0; i < values.size(); i++) {
        cout << values[i] << " ";
    }

    cout << endl;

    // BASIC SEARCH
    cout << "\n--- BASIC SEARCH ---" << endl;

    testSearch(values, 3, 1, "Search for 3");
    testSearch(values, 6, 2, "Search for 6");
    testSearch(values, 9, 4, "Search for 9");
    testSearch(values, 5, -1, "Search for 5");

    // EDGE CASES
    cout << "\n--- EDGE CASES ---" << endl;

    vector<int> emptyValues;
    testSearch(emptyValues, 10, -1, "Empty array");

    vector<int> singleValue;
    singleValue.push_back(42);

    testSearch(singleValue, 42, 0, "Single element found");
    testSearch(singleValue, 10, -1, "Single element not found");

    vector<int> negativeValues;
    negativeValues.push_back(-5);
    negativeValues.push_back(-2);
    negativeValues.push_back(-8);

    testSearch(negativeValues, -2, 1, "Negative number");

    // DUPLICATE VALUES
    cout << "\n--- DUPLICATES ---" << endl;

    testSearch(values, 3, 1, "First occurrence of 3");

    return 0;
}