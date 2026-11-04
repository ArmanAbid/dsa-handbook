#include <iostream>
#include <vector>
using namespace std;

// BINARY SEARCH WITHIN A KNOWN RANGE.
// Returns the first occurrence of the target.
int binarySearchFirstOccurrence(
    const vector<int>& values,
    int target,
    vector<int>::size_type left,
    vector<int>::size_type right
) {
    int answer = -1;

    while (left <= right) {
        vector<int>::size_type middle =
            left + (right - left) / 2;

        if (values[middle] >= target) {
            if (values[middle] == target) {
                answer = static_cast<int>(middle);
            }

            // Continue looking for an earlier occurrence.
            if (middle == 0) {
                break;
            }

            right = middle - 1;
        } else {
            left = middle + 1;
        }
    }

    return answer;
}

// EXPONENTIAL SEARCH
// Requires ascending sorted input.
// Returns the first occurrence, or -1 if not found.
int exponentialSearch(
    const vector<int>& values,
    int target
) {
    vector<int>::size_type n = values.size();

    if (n == 0) {
        return -1;
    }

    if (values[0] == target) {
        return 0;
    }

    if (values[0] > target) {
        return -1;
    }

    vector<int>::size_type low = 0;
    vector<int>::size_type high = 1;

    // Find a range that can contain the target.
    while (high < n && values[high] < target) {
        low = high;

        // Prevent index overflow when doubling.
        if (high > n / 2) {
            high = n;
            break;
        }

        high *= 2;
    }

    // The previous boundary is known to be smaller
    // than the target, so search starts after it.
    vector<int>::size_type left = low + 1;

    vector<int>::size_type right =
        high < n ? high : n - 1;

    return binarySearchFirstOccurrence(
        values,
        target,
        left,
        right
    );
}

// Helper function for demonstration.
void testSearch(
    const vector<int>& values,
    int target,
    int expected,
    const char* description
) {
    int result = exponentialSearch(values, target);

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
    cout << "==== EXPONENTIAL SEARCH ====" << endl;

    vector<int> values;

    int input[] = {
        2, 4, 6, 8, 10, 12, 14, 16,
        18, 20, 22, 24, 26, 28, 30
    };

    for (int i = 0; i < 15; i++) {
        values.push_back(input[i]);
    }

    // DISPLAY ARRAY
    cout << "\nSorted array: ";

    for (vector<int>::size_type i = 0;
         i < values.size(); i++) {
        cout << values[i] << " ";
    }

    cout << endl;

    // BASIC SEARCH
    cout << "\n--- BASIC SEARCH ---" << endl;

    testSearch(values, 22, 10, "Search for 22");
    testSearch(values, 2, 0, "Search for 2");
    testSearch(values, 4, 1, "Search for 4");
    testSearch(values, 30, 14, "Search for 30");
    testSearch(values, 17, -1, "Search for 17");

    // EDGE CASES
    cout << "\n--- EDGE CASES ---" << endl;

    vector<int> emptyValues;

    testSearch(emptyValues, 10, -1, "Empty array");

    vector<int> singleValue;
    singleValue.push_back(42);

    testSearch(singleValue, 42, 0, "Single element found");
    testSearch(singleValue, 10, -1, "Single element not found");

    testSearch(values, 1, -1, "Target smaller than all elements");
    testSearch(values, 50, -1, "Target larger than all elements");

    // NEGATIVE VALUES
    cout << "\n--- NEGATIVE VALUES ---" << endl;

    vector<int> negativeValues;

    negativeValues.push_back(-20);
    negativeValues.push_back(-10);
    negativeValues.push_back(-5);
    negativeValues.push_back(0);
    negativeValues.push_back(5);

    testSearch(negativeValues, -10, 1, "Search for -10");

    // DUPLICATES
    cout << "\n--- DUPLICATES ---" << endl;

    vector<int> duplicateValues;

    duplicateValues.push_back(2);
    duplicateValues.push_back(4);
    duplicateValues.push_back(4);
    duplicateValues.push_back(4);
    duplicateValues.push_back(6);
    duplicateValues.push_back(8);

    testSearch(
        duplicateValues,
        4,
        1,
        "First occurrence of 4"
    );

    return 0;
}