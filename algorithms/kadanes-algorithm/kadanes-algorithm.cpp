#include <iostream>
#include <vector>
using namespace std;

struct MaxSubarrayResult {
    long long sum;
    size_t startIndex;
    size_t endIndex;
};

bool maxSubarraySum(
    const vector<int>& values,
    MaxSubarrayResult& result
) {
    if (values.empty()) {
        return false;
    }

    long long currentSum = values[0];
    long long bestSum = values[0];

    size_t currentStart = 0;
    size_t bestStart = 0;
    size_t bestEnd = 0;

    for (size_t i = 1; i < values.size(); i++) {
        long long extendedSum = currentSum + values[i];

        // Decide whether to extend or start a new subarray.
        if (values[i] > extendedSum) {
            currentSum = values[i];
            currentStart = i;
        } else {
            currentSum = extendedSum;
        }

        // Update the maximum subarray found so far.
        if (currentSum > bestSum) {
            bestSum = currentSum;
            bestStart = currentStart;
            bestEnd = i;
        }
    }

    result.sum = bestSum;
    result.startIndex = bestStart;
    result.endIndex = bestEnd;

    return true;
}

void printArray(const vector<int>& values) {
    cout << "[";

    for (size_t i = 0; i < values.size(); i++) {
        cout << values[i];

        if (i + 1 < values.size()) {
            cout << ", ";
        }
    }

    cout << "]";
}

void testResult(
    const vector<int>& values,
    long long expectedSum,
    size_t expectedStart,
    size_t expectedEnd,
    const string& label
) {
    MaxSubarrayResult result;

    bool found = maxSubarraySum(values, result);

    bool passed =
        found &&
        result.sum == expectedSum &&
        result.startIndex == expectedStart &&
        result.endIndex == expectedEnd;

    cout << label << ": ";

    if (found) {
        cout << "Sum = " << result.sum
             << ", Indices = ["
             << result.startIndex << ", "
             << result.endIndex << "]";
    } else {
        cout << "No result";
    }

    cout << (passed ? " [PASSED]" : " [FAILED]") << endl;
}

int main() {
    cout << "=== KADANE'S ALGORITHM ===" << endl;

    cout << "\n--- BASIC EXAMPLE ---" << endl;

    vector<int> values;
    values.push_back(-2);
    values.push_back(1);
    values.push_back(-3);
    values.push_back(4);
    values.push_back(-1);
    values.push_back(2);
    values.push_back(1);
    values.push_back(-5);
    values.push_back(4);

    cout << "Original array: ";
    printArray(values);
    cout << endl;

    MaxSubarrayResult result;

    if (maxSubarraySum(values, result)) {
        cout << "Maximum subarray sum: " << result.sum << endl;
        cout << "Start index: " << result.startIndex << endl;
        cout << "End index: " << result.endIndex << endl;

        cout << "Maximum subarray: ";

        vector<int> subarray;

        for (size_t i = result.startIndex; i <= result.endIndex; i++) {
            subarray.push_back(values[i]);
        }

        printArray(subarray);
        cout << endl;
    }

    cout << "\n--- TEST CASES ---" << endl;

    vector<int> allNegative;
    allNegative.push_back(-8);
    allNegative.push_back(-3);
    allNegative.push_back(-6);
    allNegative.push_back(-2);
    allNegative.push_back(-5);
    allNegative.push_back(-4);

    testResult(
        allNegative,
        -2,
        3,
        3,
        "All negative numbers"
    );

    vector<int> allPositive;
    allPositive.push_back(1);
    allPositive.push_back(2);
    allPositive.push_back(3);
    allPositive.push_back(4);

    testResult(
        allPositive,
        10,
        0,
        3,
        "All positive numbers"
    );

    vector<int> single;
    single.push_back(-7);

    testResult(
        single,
        -7,
        0,
        0,
        "Single element"
    );

    vector<int> mixed;
    mixed.push_back(5);
    mixed.push_back(-1);
    mixed.push_back(5);

    testResult(
        mixed,
        9,
        0,
        2,
        "Positive values with a negative value"
    );

    vector<int> tied;
    tied.push_back(1);
    tied.push_back(-1);
    tied.push_back(1);

    testResult(
        tied,
        1,
        0,
        0,
        "Multiple maximum subarrays"
    );

    cout << "\n--- EDGE CASES ---" << endl;

    vector<int> empty;

    bool emptyFound = maxSubarraySum(empty, result);

    cout << "Empty array: "
         << (!emptyFound ? "Rejected [PASSED]" : "Accepted [FAILED]")
         << endl;

    return 0;
}