#include <iostream>
#include <vector>
using namespace std;

// BUILD PREFIX SUM
// prefix[i] represents the sum of the first i elements.
// Therefore, prefix[0] is always zero.

vector<long long> buildPrefixSum(const vector<int>& values) {
    vector<long long> prefix(values.size() + 1, 0);

    for (vector<int>::size_type i = 0; i < values.size(); i++) {
        prefix[i + 1] = prefix[i] + values[i];
    }

    return prefix;
}


// RANGE SUM QUERY
// Returns the sum of the inclusive range [left, right].
// Returns false for an invalid range.

bool rangeSum(
    const vector<long long>& prefix,
    int left,
    int right,
    long long& result
) {
    // A valid prefix array contains at least the initial zero.
    if (prefix.empty()) {
        return false;
    }

    if (left < 0 || right < left) {
        return false;
    }

    vector<long long>::size_type n = prefix.size() - 1;

    if (static_cast<vector<long long>::size_type>(right) >= n) {
        return false;
    }

    result = prefix[right + 1] - prefix[left];

    return true;
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


// Print a prefix array.
void printPrefix(const vector<long long>& prefix) {
    cout << "[";

    for (vector<long long>::size_type i = 0; i < prefix.size(); i++) {
        cout << prefix[i];

        if (i + 1 < prefix.size()) {
            cout << ", ";
        }
    }

    cout << "]";
}


// Test a range sum query.
void testRangeSum(
    const vector<long long>& prefix,
    int left,
    int right,
    bool expectedFound,
    long long expectedSum,
    const char* description
) {
    long long result = 0;

    bool found = rangeSum(prefix, left, right, result);

    bool passed = found == expectedFound;

    if (found && expectedFound) {
        passed = passed && result == expectedSum;
    }

    cout << description << ": ";

    if (found) {
        cout << result;
    } else {
        cout << "Invalid range";
    }

    cout << (passed ? " [PASSED]" : " [FAILED]") << endl;
}


// DEMONSTRATION

int main() {
    cout << "==== PREFIX SUM ====" << endl;

    // BASIC EXAMPLE
    cout << "\n--- BUILD PREFIX SUM ---" << endl;

    vector<int> values;

    int input[] = {2, 4, 1, 7, 3, 6};

    for (int i = 0; i < 6; i++) {
        values.push_back(input[i]);
    }

    vector<long long> prefix = buildPrefixSum(values);

    cout << "Original array: ";
    printArray(values);
    cout << endl;

    cout << "Prefix array:   ";
    printPrefix(prefix);
    cout << endl;


    // RANGE SUM QUERIES
    cout << "\n--- RANGE SUM QUERIES ---" << endl;

    testRangeSum(prefix, 1, 4, true, 15, "Sum from index 1 to 4");
    testRangeSum(prefix, 0, 2, true, 7, "Sum from index 0 to 2");
    testRangeSum(prefix, 2, 5, true, 17, "Sum from index 2 to 5");
    testRangeSum(prefix, 0, 5, true, 23, "Sum of entire array");
    testRangeSum(prefix, 3, 3, true, 7, "Single element range");


    // EDGE CASES
    cout << "\n--- EDGE CASES ---" << endl;

    vector<int> emptyValues;

    vector<long long> emptyPrefix =
        buildPrefixSum(emptyValues);

    testRangeSum(
        emptyPrefix, 0, 0, false, 0,
        "Empty array"
    );

    vector<int> singleValue;
    singleValue.push_back(42);

    vector<long long> singlePrefix =
        buildPrefixSum(singleValue);

    testRangeSum(
        singlePrefix, 0, 0, true, 42,
        "Single element"
    );

    testRangeSum(
        prefix, -1, 2, false, 0,
        "Negative left index"
    );

    testRangeSum(
        prefix, 0, 6, false, 0,
        "Right index out of bounds"
    );

    testRangeSum(
        prefix, 4, 2, false, 0,
        "Left greater than right"
    );


    // NEGATIVE VALUES
    cout << "\n--- NEGATIVE VALUES ---" << endl;

    vector<int> negativeValues;

    int negativeInput[] = {-5, -2, -8, -1, -3};

    for (int i = 0; i < 5; i++) {
        negativeValues.push_back(negativeInput[i]);
    }

    vector<long long> negativePrefix =
        buildPrefixSum(negativeValues);

    cout << "Prefix array: ";
    printPrefix(negativePrefix);
    cout << endl;

    testRangeSum(
        negativePrefix, 1, 3, true, -11,
        "Sum of negative range"
    );


    // ZERO VALUES
    cout << "\n--- ZERO VALUES ---" << endl;

    vector<int> zeroValues;

    zeroValues.push_back(0);
    zeroValues.push_back(0);
    zeroValues.push_back(0);

    vector<long long> zeroPrefix =
        buildPrefixSum(zeroValues);

    testRangeSum(
        zeroPrefix, 0, 2, true, 0,
        "All zero values"
    );


    // LARGE SUM
    cout << "\n--- LARGE SUM ---" << endl;

    vector<int> largeValues;

    largeValues.push_back(2000000000);
    largeValues.push_back(2000000000);
    largeValues.push_back(2000000000);

    vector<long long> largePrefix =
        buildPrefixSum(largeValues);

    testRangeSum(
        largePrefix, 0, 2, true, 6000000000LL,
        "Sum exceeding 32-bit integer range"
    );

    return 0;
}