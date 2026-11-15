#include <iostream>
#include <vector>
using namespace std;

struct WindowResult {
    long long sum;
    vector<int>::size_type startIndex;
    vector<int>::size_type endIndex;
};

// FIXED-SIZE SLIDING WINDOW
// Finds the maximum sum of a contiguous subarray
// containing exactly k elements.
//
// Returns false for an invalid window size.

bool maximumSumSubarray(
    const vector<int>& values,
    int k,
    WindowResult& result
) {
    if (k <= 0 || static_cast<vector<int>::size_type>(k) > values.size()) {
        return false;
    }

    vector<int>::size_type windowSize =
        static_cast<vector<int>::size_type>(k);

    // STEP 1: Calculate the first window sum.
    long long currentSum = 0;

    for (vector<int>::size_type i = 0; i < windowSize; i++) {
        currentSum += static_cast<long long>(values[i]);
    }

    // Initialize the best result using the first actual window.
    result.sum = currentSum;
    result.startIndex = 0;
    result.endIndex = windowSize - 1;

    // STEP 2: Slide the window.
    for (vector<int>::size_type i = windowSize;
         i < values.size(); i++) {

        // Remove the element leaving the window.
        currentSum -= static_cast<long long>(values[i - windowSize]);

        // Add the element entering the window.
        currentSum += static_cast<long long>(values[i]);

        // Update only when a strictly better sum is found.
        // This preserves the first window when sums are equal.
        if (currentSum > result.sum) {
            result.sum = currentSum;
            result.startIndex = i - windowSize + 1;
            result.endIndex = i;
        }
    }

    return true;
}


// Helper function for testing.
void testMaximumSum(
    const vector<int>& values,
    int k,
    bool expectedFound,
    long long expectedSum,
    int expectedStart,
    int expectedEnd,
    const char* description
) {
    WindowResult result;

    bool found = maximumSumSubarray(values, k, result);

    bool passed = found == expectedFound;

    if (found && expectedFound) {
        passed =
            passed &&
            result.sum == expectedSum &&
            static_cast<int>(result.startIndex) == expectedStart &&
            static_cast<int>(result.endIndex) == expectedEnd;
    }

    cout << description << ": ";

    if (found) {
        cout << "Sum = " << result.sum
             << ", Indices = ("
             << result.startIndex << ", "
             << result.endIndex << ")";
    } else {
        cout << "No valid window";
    }

    cout << (passed ? " [PASSED]" : " [FAILED]") << endl;
}


// DEMONSTRATION

int main() {
    cout << "==== SLIDING WINDOW ====" << endl;

    // BASIC EXAMPLE
    cout << "\n--- MAXIMUM SUM SUBARRAY ---" << endl;

    vector<int> values;

    int input[] = {2, 1, 5, 1, 3, 2};

    for (int i = 0; i < 6; i++) {
        values.push_back(input[i]);
    }

    cout << "Array: ";

    for (vector<int>::size_type i = 0; i < values.size(); i++) {
        cout << values[i] << " ";
    }

    cout << endl;
    cout << "Window size: 3" << endl;

    testMaximumSum(
        values, 3, true, 9, 2, 4,
        "Maximum sum"
    );


    // EDGE CASES
    cout << "\n--- EDGE CASES ---" << endl;

    vector<int> emptyValues;

    testMaximumSum(
        emptyValues, 2, false, 0, 0, 0,
        "Empty array"
    );

    vector<int> singleValue;
    singleValue.push_back(7);

    testMaximumSum(
        singleValue, 1, true, 7, 0, 0,
        "Single element"
    );

    testMaximumSum(
        singleValue, 2, false, 0, 0, 0,
        "Window larger than array"
    );

    testMaximumSum(
        values, 0, false, 0, 0, 0,
        "Zero window size"
    );

    testMaximumSum(
        values, -2, false, 0, 0, 0,
        "Negative window size"
    );

    testMaximumSum(
        values, 6, true, 14, 0, 5,
        "Window equals array size"
    );


    // NEGATIVE VALUES
    cout << "\n--- NEGATIVE VALUES ---" << endl;

    vector<int> negativeValues;

    int negativeInput[] = {-5, -2, -8, -1, -3};

    for (int i = 0; i < 5; i++) {
        negativeValues.push_back(negativeInput[i]);
    }

    testMaximumSum(
        negativeValues, 2, true, -4, 3, 4,
        "All negative values"
    );


    // DUPLICATE MAXIMUM WINDOWS
    cout << "\n--- EQUAL MAXIMUM WINDOWS ---" << endl;

    vector<int> equalValues;

    int equalInput[] = {4, 4, 4, 4};

    for (int i = 0; i < 4; i++) {
        equalValues.push_back(equalInput[i]);
    }

    testMaximumSum(
        equalValues, 2, true, 8, 0, 1,
        "First window among equal maximum sums"
    );


    // MAXIMUM AT DIFFERENT POSITIONS
    cout << "\n--- MAXIMUM WINDOW POSITIONS ---" << endl;

    vector<int> firstMaximum;

    int firstInput[] = {10, 2, 3, 1};

    for (int i = 0; i < 4; i++) {
        firstMaximum.push_back(firstInput[i]);
    }

    testMaximumSum(
        firstMaximum, 2, true, 12, 0, 1,
        "Maximum at first window"
    );

    vector<int> lastMaximum;

    int lastInput[] = {1, 2, 3, 10};

    for (int i = 0; i < 4; i++) {
        lastMaximum.push_back(lastInput[i]);
    }

    testMaximumSum(
        lastMaximum, 2, true, 13, 2, 3,
        "Maximum at last window"
    );

    return 0;
}