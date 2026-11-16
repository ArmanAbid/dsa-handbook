#include <iostream>
#include <vector>
using namespace std;

class DifferenceArray {
private:
    vector<long long> diff;

public:
    // CREATE: Build a difference array from the original array.
    DifferenceArray(const vector<long long>& values) {
        diff.resize(values.size(), 0);

        if (values.empty()) {
            return;
        }

        diff[0] = values[0];

        for (vector<long long>::size_type i = 1;
             i < values.size(); i++) {

            diff[i] = values[i] - values[i - 1];
        }
    }

    // RANGE UPDATE:
    // Add value to every element in the inclusive range [left, right].
    // Returns false if the range is invalid.
    bool rangeAdd(int left, int right, long long value) {
        if (
            left < 0 ||
            right < left ||
            static_cast<vector<long long>::size_type>(right) >= diff.size()
        ) {
            return false;
        }

        vector<long long>::size_type start =
            static_cast<vector<long long>::size_type>(left);

        vector<long long>::size_type end =
            static_cast<vector<long long>::size_type>(right);

        diff[start] += value;

        // Cancel the update immediately after the requested range.
        if (end + 1 < diff.size()) {
            diff[end + 1] -= value;
        }

        return true;
    }

    // RECONSTRUCT: Build the final array using Prefix Sum.
    vector<long long> buildArray() const {
        vector<long long> result(diff.size(), 0);

        long long current = 0;

        for (vector<long long>::size_type i = 0;
             i < diff.size(); i++) {

            current += diff[i];
            result[i] = current;
        }

        return result;
    }

    // SIZE: Get the number of elements.
    vector<long long>::size_type size() const {
        return diff.size();
    }

    // CHECK: Is the structure empty?
    bool isEmpty() const {
        return diff.empty();
    }
};


// Print an array.
void printArray(const vector<long long>& values) {
    cout << "[";

    for (vector<long long>::size_type i = 0;
         i < values.size(); i++) {

        cout << values[i];

        if (i + 1 < values.size()) {
            cout << ", ";
        }
    }

    cout << "]";
}


// Test a range update.
void testUpdate(
    DifferenceArray& values,
    int left,
    int right,
    long long delta,
    bool expected,
    const char* description
) {
    bool result = values.rangeAdd(left, right, delta);

    bool passed = result == expected;

    cout << description << ": "
         << (result ? "Updated" : "Rejected")
         << (passed ? " [PASSED]" : " [FAILED]")
         << endl;
}


// Test reconstructed output.
void testArray(
    DifferenceArray& values,
    const vector<long long>& expected,
    const char* description
) {
    vector<long long> result = values.buildArray();

    bool passed = result == expected;

    cout << description << ": ";
    printArray(result);

    cout << (passed ? " [PASSED]" : " [FAILED]") << endl;
}


// DEMONSTRATION

int main() {
    cout << "==== DIFFERENCE ARRAY ====" << endl;

    // BASIC EXAMPLE
    cout << "\n--- BUILD DIFFERENCE ARRAY ---" << endl;

    vector<long long> initial;

    initial.push_back(10);
    initial.push_back(20);
    initial.push_back(30);
    initial.push_back(40);
    initial.push_back(50);

    DifferenceArray values(initial);

    cout << "Original array: ";
    printArray(initial);
    cout << endl;

    cout << "Size: " << values.size() << endl;
    cout << "Is empty: " << (values.isEmpty() ? "Yes" : "No") << endl;


    // RANGE UPDATES
    cout << "\n--- RANGE UPDATES ---" << endl;

    testUpdate(
        values, 1, 3, 5, true,
        "Add 5 to range [1, 3]"
    );

    vector<long long> intermediateExpected;
    intermediateExpected.push_back(10);
    intermediateExpected.push_back(25);
    intermediateExpected.push_back(35);
    intermediateExpected.push_back(45);
    intermediateExpected.push_back(50);

testArray(values, intermediateExpected, "Intermediate result after first update");

    testUpdate(
        values, 0, 2, -3, true,
        "Add -3 to range [0, 2]"
    );

    testUpdate(
        values, 2, 4, 10, true,
        "Add 10 to range [2, 4]"
    );

    vector<long long> expected;

    expected.push_back(7);
    expected.push_back(22);
    expected.push_back(42);
    expected.push_back(55);
    expected.push_back(60);

    testArray(
        values,
        expected,
        "Final array after three updates"
    );


    // EDGE CASES
    cout << "\n--- EDGE CASES ---" << endl;

    vector<long long> emptyValues;

    DifferenceArray emptyArray(emptyValues);

    cout << "Empty array size: " << emptyArray.size() << endl;
    cout << "Empty check: "
         << (emptyArray.isEmpty() ? "Yes" : "No") << endl;

    testUpdate(
        emptyArray, 0, 0, 5, false,
        "Update empty array"
    );

    vector<long long> single;

    single.push_back(10);

    DifferenceArray singleArray(single);

    testUpdate(
        singleArray, 0, 0, 5, true,
        "Single-element update"
    );

    vector<long long> singleExpected;
    singleExpected.push_back(15);

    testArray(
        singleArray,
        singleExpected,
        "Single-element result"
    );


    // FULL ARRAY UPDATE
    cout << "\n--- FULL ARRAY UPDATE ---" << endl;

    vector<long long> fullInput;

    fullInput.push_back(1);
    fullInput.push_back(2);
    fullInput.push_back(3);

    DifferenceArray fullArray(fullInput);

    testUpdate(
        fullArray, 0, 2, 10, true,
        "Add 10 to entire array"
    );

    vector<long long> fullExpected;

    fullExpected.push_back(11);
    fullExpected.push_back(12);
    fullExpected.push_back(13);

    testArray(
        fullArray,
        fullExpected,
        "Full array result"
    );


    // OVERLAPPING UPDATES
    cout << "\n--- OVERLAPPING UPDATES ---" << endl;

    vector<long long> overlappingInput;

    overlappingInput.push_back(0);
    overlappingInput.push_back(0);
    overlappingInput.push_back(0);
    overlappingInput.push_back(0);
    overlappingInput.push_back(0);

    DifferenceArray overlapping(overlappingInput);

    overlapping.rangeAdd(0, 2, 5);
    overlapping.rangeAdd(1, 4, 3);

    vector<long long> overlappingExpected;

    overlappingExpected.push_back(5);
    overlappingExpected.push_back(8);
    overlappingExpected.push_back(8);
    overlappingExpected.push_back(3);
    overlappingExpected.push_back(3);

    testArray(
        overlapping,
        overlappingExpected,
        "Overlapping range updates"
    );


    // INVALID RANGES
    cout << "\n--- INVALID RANGES ---" << endl;

    testUpdate(
        overlapping, -1, 2, 5, false,
        "Negative left index"
    );

    testUpdate(
        overlapping, 0, 5, 5, false,
        "Right index out of bounds"
    );

    testUpdate(
        overlapping, 3, 1, 5, false,
        "Left greater than right"
    );

    return 0;
}