#include <iostream>
#include <vector>
#include <climits>
#include <cstddef>
using namespace std;

// STABLE COUNTING SORT BY DIGIT
// Sorts values according to one decimal digit.
// The original values and their transformed keys move together.

void countingSortByDigit(
    vector<int>& values,
    vector<long long>& keys,
    vector<int>& output,
    vector<long long>& outputKeys,
    long long exponent
) {
    size_t counts[10] = {0};

    size_t n = values.size();

    // STEP 1: Count occurrences of each digit.
    for (size_t i = 0; i < n; i++) {
        int digit = static_cast<int>((keys[i] / exponent) % 10);
        counts[digit]++;
    }

    // STEP 2: Calculate cumulative counts.
    for (int i = 1; i < 10; i++) {
        counts[i] += counts[i - 1];
    }

    // STEP 3: Construct output backwards to preserve stability.
    for (size_t i = n; i > 0; i--) {
        size_t currentIndex = i - 1;

        int digit = static_cast<int>(
            (keys[currentIndex] / exponent) % 10
        );

        counts[digit]--;

        size_t position = counts[digit];

        output[position] = values[currentIndex];
        outputKeys[position] = keys[currentIndex];
    }

    // Copy the sorted result back.
    for (size_t i = 0; i < n; i++) {
        values[i] = output[i];
        keys[i] = outputKeys[i];
    }
}


// RADIX SORT
// Supports negative and positive integers.
// Sorts the original vector in ascending order.

void radixSort(vector<int>& values) {
    size_t n = values.size();

    if (n <= 1) {
        return;
    }

    // STEP 1: Find minimum and maximum values.
    int minimum = values[0];
    int maximum = values[0];

    for (size_t i = 1; i < n; i++) {
        if (values[i] < minimum) {
            minimum = values[i];
        }

        if (values[i] > maximum) {
            maximum = values[i];
        }
    }

    // STEP 2: Transform values into non-negative keys.
    // Use long long to safely handle INT_MIN and INT_MAX.
    vector<long long> keys(n);

    long long maxKey =
        static_cast<long long>(maximum) -
        static_cast<long long>(minimum);

    for (size_t i = 0; i < n; i++) {
        keys[i] =
            static_cast<long long>(values[i]) -
            static_cast<long long>(minimum);
    }

    vector<int> output(n);
    vector<long long> outputKeys(n);

    // STEP 3: Process decimal digits from right to left.
    long long exponent = 1;

    while (maxKey / exponent > 0) {
        countingSortByDigit(
            values,
            keys,
            output,
            outputKeys,
            exponent
        );

        // Avoid overflowing when moving to the next digit.
        if (exponent > maxKey / 10) {
            break;
        }

        exponent *= 10;
    }
}


// Print an array.
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


// Test a sorting case.
void testSort(
    const vector<int>& input,
    const vector<int>& expected,
    const char* description
) {
    vector<int> values = input;

    radixSort(values);

    bool passed = values == expected;

    cout << description << ": ";
    printArray(values);

    cout << (passed ? " [PASSED]" : " [FAILED]") << endl;
}


// DEMONSTRATION

int main() {
    cout << "==== RADIX SORT ====" << endl;

    // BASIC EXAMPLE
    cout << "\n--- BASIC SORTING ---" << endl;

    vector<int> values;

    int input[] = {
        170, 45, 75, 90, 802, 24, 2, 66
    };

    for (int i = 0; i < 8; i++) {
        values.push_back(input[i]);
    }

    cout << "Before sorting: ";
    printArray(values);
    cout << endl;

    radixSort(values);

    cout << "After sorting:  ";
    printArray(values);
    cout << endl;


    // EDGE CASES
    cout << "\n--- EDGE CASES ---" << endl;

    vector<int> emptyValues;
    vector<int> emptyExpected;

    testSort(
        emptyValues,
        emptyExpected,
        "Empty array"
    );

    vector<int> singleValue;
    singleValue.push_back(42);

    testSort(
        singleValue,
        singleValue,
        "Single element"
    );

    vector<int> sortedValues;

    sortedValues.push_back(1);
    sortedValues.push_back(2);
    sortedValues.push_back(3);
    sortedValues.push_back(4);
    sortedValues.push_back(5);

    testSort(
        sortedValues,
        sortedValues,
        "Already sorted"
    );

    vector<int> reversedValues;

    reversedValues.push_back(5);
    reversedValues.push_back(4);
    reversedValues.push_back(3);
    reversedValues.push_back(2);
    reversedValues.push_back(1);

    testSort(
        reversedValues,
        sortedValues,
        "Reverse sorted"
    );

    vector<int> duplicateValues;

    duplicateValues.push_back(4);
    duplicateValues.push_back(2);
    duplicateValues.push_back(4);
    duplicateValues.push_back(1);
    duplicateValues.push_back(2);

    vector<int> duplicateExpected;

    duplicateExpected.push_back(1);
    duplicateExpected.push_back(2);
    duplicateExpected.push_back(2);
    duplicateExpected.push_back(4);
    duplicateExpected.push_back(4);

    testSort(
        duplicateValues,
        duplicateExpected,
        "Duplicate values"
    );

    vector<int> equalValues;

    equalValues.push_back(7);
    equalValues.push_back(7);
    equalValues.push_back(7);
    equalValues.push_back(7);

    testSort(
        equalValues,
        equalValues,
        "All elements equal"
    );

    vector<int> negativeValues;

    negativeValues.push_back(-5);
    negativeValues.push_back(-2);
    negativeValues.push_back(-5);
    negativeValues.push_back(0);
    negativeValues.push_back(3);
    negativeValues.push_back(-2);

    vector<int> negativeExpected;

    negativeExpected.push_back(-5);
    negativeExpected.push_back(-5);
    negativeExpected.push_back(-2);
    negativeExpected.push_back(-2);
    negativeExpected.push_back(0);
    negativeExpected.push_back(3);

    testSort(
        negativeValues,
        negativeExpected,
        "Negative and positive values"
    );

    vector<int> mixedValues;

    mixedValues.push_back(0);
    mixedValues.push_back(-3);
    mixedValues.push_back(2);
    mixedValues.push_back(-1);
    mixedValues.push_back(3);
    mixedValues.push_back(-2);

    vector<int> mixedExpected;

    mixedExpected.push_back(-3);
    mixedExpected.push_back(-2);
    mixedExpected.push_back(-1);
    mixedExpected.push_back(0);
    mixedExpected.push_back(2);
    mixedExpected.push_back(3);

    testSort(
        mixedValues,
        mixedExpected,
        "Mixed negative and positive values"
    );

    // DIFFERENT NUMBER OF DIGITS
    cout << "\n--- DIFFERENT DIGIT LENGTHS ---" << endl;

    vector<int> differentDigits;

    differentDigits.push_back(1000);
    differentDigits.push_back(5);
    differentDigits.push_back(50);
    differentDigits.push_back(500);
    differentDigits.push_back(1);

    vector<int> differentDigitsExpected;

    differentDigitsExpected.push_back(1);
    differentDigitsExpected.push_back(5);
    differentDigitsExpected.push_back(50);
    differentDigitsExpected.push_back(500);
    differentDigitsExpected.push_back(1000);

    testSort(
        differentDigits,
        differentDigitsExpected,
        "Different digit lengths"
    );

    // SIGNED INTEGER LIMITS
    cout << "\n--- INTEGER LIMITS ---" << endl;

    vector<int> extremeValues;

    extremeValues.push_back(INT_MAX);
    extremeValues.push_back(0);
    extremeValues.push_back(INT_MIN);
    extremeValues.push_back(-1);
    extremeValues.push_back(1);

    vector<int> extremeExpected;

    extremeExpected.push_back(INT_MIN);
    extremeExpected.push_back(-1);
    extremeExpected.push_back(0);
    extremeExpected.push_back(1);
    extremeExpected.push_back(INT_MAX);

    testSort(
        extremeValues,
        extremeExpected,
        "INT_MIN and INT_MAX"
    );

    return 0;
}