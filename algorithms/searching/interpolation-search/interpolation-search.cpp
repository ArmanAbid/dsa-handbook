#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// INTERPOLATION SEARCH
// Requires ascending sorted input.
// Returns the first occurrence, or -1 if not found.

int interpolationSearch(
    const vector<int>& values,
    int target
) {
    if (values.empty()) {
        return -1;
    }

    vector<int>::size_type low = 0;
    vector<int>::size_type high = values.size() - 1;

    int answer = -1;

    while (
        low <= high &&
        target >= values[low] &&
        target <= values[high]
    ) {
        // Avoid division by zero.
        if (values[low] == values[high]) {
            if (values[low] == target) {
                answer = static_cast<int>(low);
            }

            break;
        }

        // Estimate the target's likely position.
        long double numerator =
            static_cast<long double>(target) - values[low];

        long double denominator =
            static_cast<long double>(values[high]) - values[low];

        long double fraction = numerator / denominator;

        vector<int>::size_type position =
            low + static_cast<vector<int>::size_type>(
                fraction * (high - low)
            );

        // Keep the estimated position within the search range.
        if (position < low) {
            position = low;
        }

        if (position > high) {
            position = high;
        }

        int currentValue = values[position];

        if (currentValue < target) {
            low = position + 1;
        } else {
            if (currentValue == target) {
                answer = static_cast<int>(position);
            }

            // Continue searching for an earlier occurrence.
            if (position == 0) {
                break;
            }

            high = position - 1;
        }
    }

    return answer;
}

// Helper function for demonstration.
void testSearch(
    const vector<int>& values,
    int target,
    int expected,
    const char* description
) {
    int result = interpolationSearch(values, target);

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
    cout << "==== INTERPOLATION SEARCH ====" << endl;

    // UNIFORMLY DISTRIBUTED VALUES
    cout << "\n--- UNIFORM DISTRIBUTION ---" << endl;

    vector<int> values;

    for (int i = 10; i <= 100; i += 10) {
        values.push_back(i);
    }

    cout << "Sorted array: ";

    for (vector<int>::size_type i = 0;
         i < values.size(); i++) {
        cout << values[i] << " ";
    }

    cout << endl;

    testSearch(values, 80, 7, "Search for 80");
    testSearch(values, 10, 0, "Search for 10");
    testSearch(values, 100, 9, "Search for 100");
    testSearch(values, 55, -1, "Search for 55");

    // EDGE CASES
    cout << "\n--- EDGE CASES ---" << endl;

    vector<int> emptyValues;

    testSearch(emptyValues, 10, -1, "Empty array");

    vector<int> singleValue;
    singleValue.push_back(42);

    testSearch(singleValue, 42, 0, "Single element found");
    testSearch(singleValue, 10, -1, "Single element not found");

    testSearch(values, 5, -1, "Target smaller than all elements");
    testSearch(values, 110, -1, "Target larger than all elements");

    // NEGATIVE VALUES
    cout << "\n--- NEGATIVE VALUES ---" << endl;

    vector<int> negativeValues;

    negativeValues.push_back(-50);
    negativeValues.push_back(-40);
    negativeValues.push_back(-30);
    negativeValues.push_back(-20);
    negativeValues.push_back(-10);
    negativeValues.push_back(0);

    testSearch(negativeValues, -30, 2, "Search for -30");

    // DUPLICATES
    cout << "\n--- DUPLICATES ---" << endl;

    vector<int> duplicateValues;

    duplicateValues.push_back(1);
    duplicateValues.push_back(2);
    duplicateValues.push_back(2);
    duplicateValues.push_back(2);
    duplicateValues.push_back(2);
    duplicateValues.push_back(3);

    testSearch(
        duplicateValues,
        2,
        1,
        "First occurrence of 2"
    );

    // ALL ELEMENTS EQUAL
    cout << "\n--- ALL ELEMENTS EQUAL ---" << endl;

    vector<int> equalValues;

    equalValues.push_back(5);
    equalValues.push_back(5);
    equalValues.push_back(5);
    equalValues.push_back(5);

    testSearch(equalValues, 5, 0, "Search for 5");
    testSearch(equalValues, 8, -1, "Search for 8");

    // NONUNIFORM DISTRIBUTION
    cout << "\n--- NONUNIFORM DISTRIBUTION ---" << endl;

    vector<int> nonuniformValues;

    nonuniformValues.push_back(1);
    nonuniformValues.push_back(2);
    nonuniformValues.push_back(3);
    nonuniformValues.push_back(4);
    nonuniformValues.push_back(1000);

    testSearch(
        nonuniformValues,
        1000,
        4,
        "Search in nonuniform data"
    );

    return 0;
}