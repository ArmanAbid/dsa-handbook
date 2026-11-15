#include <iostream>
#include <vector>
using namespace std;

// TWO POINTERS: PAIR SUM
// Requires ascending sorted input.
// Returns true and stores the matching indices.
// Returns false when no matching pair exists.

bool findPairWithSum(
    const vector<int>& values,
    int target,
    vector<int>::size_type& firstIndex,
    vector<int>::size_type& secondIndex
) {
    if (values.size() < 2) {
        return false;
    }

    vector<int>::size_type left = 0;
    vector<int>::size_type right = values.size() - 1;

    while (left < right) {
        // Use long long to prevent int addition overflow.
        long long sum =
            static_cast<long long>(values[left]) +
            static_cast<long long>(values[right]);

        if (sum == target) {
            firstIndex = left;
            secondIndex = right;

            return true;
        }

        if (sum < target) {
            // Increase the sum by moving the left pointer.
            left++;
        } else {
            // Decrease the sum by moving the right pointer.
            right--;
        }
    }

    return false;
}


// Helper function for demonstration.
void testPair(
    const vector<int>& values,
    int target,
    bool expectedFound,
    int expectedLeft,
    int expectedRight,
    const char* description
) {
    vector<int>::size_type left = 0;
    vector<int>::size_type right = 0;

    bool found = findPairWithSum(
        values,
        target,
        left,
        right
    );

    bool passed = found == expectedFound;

    if (found && expectedFound) {
        passed =
            passed &&
            static_cast<int>(left) == expectedLeft &&
            static_cast<int>(right) == expectedRight;
    }

    cout << description << ": ";

    if (found) {
        cout << "(" << left << ", " << right << ")";
    } else {
        cout << "Not found";
    }

    cout << (passed ? " [PASSED]" : " [FAILED]") << endl;
}


// DEMONSTRATION

int main() {
    cout << "==== TWO POINTERS ====" << endl;

    // BASIC EXAMPLE
    cout << "\n--- BASIC PAIR SUM ---" << endl;

    vector<int> values;

    int input[] = {1, 2, 4, 6, 8, 9, 11};

    for (int i = 0; i < 7; i++) {
        values.push_back(input[i]);
    }

    cout << "Sorted array: ";

    for (vector<int>::size_type i = 0; i < values.size(); i++) {
        cout << values[i] << " ";
    }

    cout << endl;

    testPair(
        values, 10, true, 0, 5,
        "Find pair with sum 10"
    );

    testPair(
        values, 13, true, 1, 6,
        "Find pair with sum 13"
    );

    testPair(
        values, 21, false, -1, -1,
        "No pair with sum 21"
    );


    // EDGE CASES
    cout << "\n--- EDGE CASES ---" << endl;

    vector<int> emptyValues;

    testPair(
        emptyValues, 10, false, -1, -1,
        "Empty array"
    );

    vector<int> singleValue;
    singleValue.push_back(5);

    testPair(
        singleValue, 10, false, -1, -1,
        "Single element"
    );

    vector<int> twoValues;
    twoValues.push_back(3);
    twoValues.push_back(7);

    testPair(
        twoValues, 10, true, 0, 1,
        "Two elements"
    );

    testPair(
        twoValues, 8, false, -1, -1,
        "Two elements without a pair"
    );


    // DUPLICATES
    cout << "\n--- DUPLICATES ---" << endl;

    vector<int> duplicateValues;

    duplicateValues.push_back(1);
    duplicateValues.push_back(2);
    duplicateValues.push_back(2);
    duplicateValues.push_back(2);
    duplicateValues.push_back(4);

    testPair(
        duplicateValues, 4, true, 1, 3,
        "Duplicate values"
    );

    vector<int> equalValues;

    equalValues.push_back(5);
    equalValues.push_back(5);
    equalValues.push_back(5);

    testPair(
        equalValues, 10, true, 0, 2,
        "All elements equal"
    );


    // NEGATIVE VALUES
    cout << "\n--- NEGATIVE VALUES ---" << endl;

    vector<int> negativeValues;

    negativeValues.push_back(-8);
    negativeValues.push_back(-3);
    negativeValues.push_back(0);
    negativeValues.push_back(4);
    negativeValues.push_back(9);

    testPair(
        negativeValues, 1, true, 0, 4,
        "Negative and positive pair"
    );

    testPair(
        negativeValues, -11, true, 0, 1,
        "Negative pair"
    );

    testPair(
        negativeValues, 100, false, -1, -1,
        "Target too large"
    );

    return 0;
}