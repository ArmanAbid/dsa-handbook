#include <iostream>
#include <vector>
#include <string>
using namespace std;

bool dutchNationalFlag(vector<int>& values) {
    // Validate the entire array before modifying it.
    for (size_t i = 0; i < values.size(); i++) {
        if (values[i] != 0 &&
            values[i] != 1 &&
            values[i] != 2) {
            return false;
        }
    }

    size_t low = 0;
    size_t mid = 0;
    size_t high = values.size();

    while (mid < high) {
        if (values[mid] == 0) {
            // Move zero to the beginning.
            int temp = values[low];
            values[low] = values[mid];
            values[mid] = temp;

            low++;
            mid++;
        }
        else if (values[mid] == 1) {
            // One is already in the correct partition.
            mid++;
        }
        else {
            // Move two to the end.
            high--;

            int temp = values[mid];
            values[mid] = values[high];
            values[high] = temp;

            // Do not increment mid.
            // The swapped value is still unprocessed.
        }
    }

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

void testSort(
    vector<int> values,
    const vector<int>& expected,
    const string& label
) {
    bool valid = dutchNationalFlag(values);
    bool passed = valid && values == expected;

    cout << label << ": ";
    printArray(values);

    cout << (passed ? " [PASSED]" : " [FAILED]") << endl;
}

int main() {
    cout << "==== DUTCH NATIONAL FLAG ====" << endl;

    cout << "\n--- BASIC EXAMPLE ---" << endl;

    vector<int> values;
    values.push_back(2);
    values.push_back(0);
    values.push_back(2);
    values.push_back(1);
    values.push_back(1);
    values.push_back(0);

    cout << "Original array: ";
    printArray(values);
    cout << endl;

    bool valid = dutchNationalFlag(values);

    cout << "Sorted array: ";
    printArray(values);
    cout << (valid ? " [PASSED]" : " [FAILED]") << endl;

    cout << "\n--- TEST CASES ---" << endl;

    vector<int> mixed;
    mixed.push_back(2);
    mixed.push_back(0);
    mixed.push_back(1);
    mixed.push_back(2);
    mixed.push_back(1);
    mixed.push_back(0);

    vector<int> mixedExpected;
    mixedExpected.push_back(0);
    mixedExpected.push_back(0);
    mixedExpected.push_back(1);
    mixedExpected.push_back(1);
    mixedExpected.push_back(2);
    mixedExpected.push_back(2);

    testSort(mixed, mixedExpected, "Mixed values");

    vector<int> sorted;
    sorted.push_back(0);
    sorted.push_back(1);
    sorted.push_back(2);

    testSort(sorted, sorted, "Already sorted");

    vector<int> reverse;
    reverse.push_back(2);
    reverse.push_back(1);
    reverse.push_back(0);

    testSort(reverse, sorted, "Reverse order");

    vector<int> zeros;
    zeros.push_back(0);
    zeros.push_back(0);
    zeros.push_back(0);

    testSort(zeros, zeros, "All zeros");

    vector<int> ones;
    ones.push_back(1);
    ones.push_back(1);
    ones.push_back(1);

    testSort(ones, ones, "All ones");

    vector<int> twos;
    twos.push_back(2);
    twos.push_back(2);
    twos.push_back(2);

    testSort(twos, twos, "All twos");

    vector<int> duplicates;
    duplicates.push_back(2);
    duplicates.push_back(2);
    duplicates.push_back(1);
    duplicates.push_back(0);
    duplicates.push_back(1);
    duplicates.push_back(0);

    vector<int> duplicatesExpected;
    duplicatesExpected.push_back(0);
    duplicatesExpected.push_back(0);
    duplicatesExpected.push_back(1);
    duplicatesExpected.push_back(1);
    duplicatesExpected.push_back(2);
    duplicatesExpected.push_back(2);

    testSort(
        duplicates,
        duplicatesExpected,
        "Repeated values"
    );

    vector<int> single;
    single.push_back(2);

    testSort(single, single, "Single element");

    vector<int> empty;
    testSort(empty, empty, "Empty array");

    cout << "\n--- INVALID INPUT ---" << endl;

    vector<int> invalid;
    invalid.push_back(2);
    invalid.push_back(0);
    invalid.push_back(3);
    invalid.push_back(1);

    vector<int> original = invalid;

    bool accepted = dutchNationalFlag(invalid);
    bool unchanged = invalid == original;

    cout << "Invalid value: "
         << (!accepted ? "Rejected" : "Accepted")
         << (unchanged ? " and unchanged" : " but modified")
         << ((!accepted && unchanged) ? " [PASSED]" : " [FAILED]")
         << endl;

    return 0;
}