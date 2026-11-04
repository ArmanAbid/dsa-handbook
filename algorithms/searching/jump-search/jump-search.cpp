#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// JUMP SEARCH
// Requires an array sorted in ascending order.
// Returns the first occurrence of the target.
// Returns -1 if the target is not found.

int jumpSearch(const vector<int>& values, int target) {
    vector<int>::size_type n = values.size();

    if (n == 0) {
        return -1;
    }

    // Calculate the optimal block size: floor(sqrt(n)).
    vector<int>::size_type blockSize =
        static_cast<vector<int>::size_type>(
            sqrt(static_cast<double>(n))
        );

    if (blockSize == 0) {
        blockSize = 1;
    }

    vector<int>::size_type start = 0;
    vector<int>::size_type end = blockSize;

    if (end > n) {
        end = n;
    }

    // STAGE 1: Find the candidate block.
    while (values[end - 1] < target) {
        start = end;

        if (start >= n) {
            return -1;
        }

        // Extend the block without exceeding the array size.
        if (blockSize >= n - end) {
            end = n;
        } else {
            end += blockSize;
        }
    }

    // STAGE 2: Linear Search inside the candidate block.
    for (vector<int>::size_type i = start; i < end; i++) {
        if (values[i] == target) {
            return static_cast<int>(i);
        }

        // The array is sorted, so no later value can match.
        if (values[i] > target) {
            return -1;
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
    int result = jumpSearch(values, target);

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
    cout << "==== JUMP SEARCH ====" << endl;

    vector<int> values;

    int input[] = {
        1, 3, 5, 7, 9, 11, 13, 15,
        17, 19, 21, 23, 25, 27, 29
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

    testSearch(values, 19, 9, "Search for 19");
    testSearch(values, 1, 0, "Search for 1");
    testSearch(values, 15, 7, "Search for 15");
    testSearch(values, 29, 14, "Search for 29");
    testSearch(values, 20, -1, "Search for 20");

    // EDGE CASES
    cout << "\n--- EDGE CASES ---" << endl;

    vector<int> emptyValues;

    testSearch(emptyValues, 10, -1, "Empty array");

    vector<int> singleValue;
    singleValue.push_back(42);

    testSearch(singleValue, 42, 0, "Single element found");
    testSearch(singleValue, 10, -1, "Single element not found");

    testSearch(values, 0, -1, "Target smaller than all elements");
    testSearch(values, 40, -1, "Target larger than all elements");

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

    vector<int> equalValues;

    equalValues.push_back(5);
    equalValues.push_back(5);
    equalValues.push_back(5);
    equalValues.push_back(5);

    testSearch(
        equalValues,
        5,
        0,
        "All elements equal"
    );

    return 0;
}