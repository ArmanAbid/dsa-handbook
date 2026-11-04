#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
using namespace std;

// DISCRETE TERNARY SEARCH
// Finds the index of the maximum element in a unimodal array.
// Returns -1 if the array is empty.

int ternarySearchMaximum(const vector<int>& values) {
    if (values.empty()) {
        return -1;
    }

    int left = 0;
    int right = static_cast<int>(values.size()) - 1;

    // Narrow the search interval.
    while (right - left > 2) {
        int third = (right - left) / 3;

        int middleOne = left + third;
        int middleTwo = right - third;

        if (values[middleOne] < values[middleTwo]) {
            // The maximum must be to the right.
            left = middleOne + 1;
        } else {
            // The maximum must be to the left.
            right = middleTwo - 1;
        }
    }

    // Check the remaining elements.
    int bestIndex = left;

    for (int i = left + 1; i <= right; i++) {
        if (values[i] > values[bestIndex]) {
            bestIndex = i;
        }
    }

    return bestIndex;
}

// CONTINUOUS TERNARY SEARCH
// Finds the approximate maximum position of a unimodal function.
// The function is evaluated 100 times.

double ternarySearchContinuousMaximum(
    double (*function)(double),
    double left,
    double right
) {
    if (left > right) {
        swap(left, right);
    }

    for (int iteration = 0; iteration < 100; iteration++) {
        double third = (right - left) / 3.0;

        double middleOne = left + third;
        double middleTwo = right - third;

        if (function(middleOne) < function(middleTwo)) {
            left = middleOne;
        } else {
            right = middleTwo;
        }
    }

    return left + (right - left) / 2.0;
}

// Example function:
// f(x) = -(x - 3)^2 + 10
// Maximum is at x = 3, with value 10.

double objectiveFunction(double x) {
    double difference = x - 3.0;

    return -(difference * difference) + 10.0;
}

// Helper function for discrete search tests.
void testDiscreteSearch(
    const vector<int>& values,
    int expectedIndex,
    const char* description
) {
    int result = ternarySearchMaximum(values);

    cout << description << ": " << result;

    if (result == expectedIndex) {
        cout << " [PASSED]";
    } else {
        cout << " [FAILED]";
    }

    cout << endl;
}

// Helper function for continuous search tests.
void testContinuousSearch(
    double left,
    double right,
    double expected,
    const char* description
) {
    double result = ternarySearchContinuousMaximum(
        objectiveFunction,
        left,
        right
    );

    cout << description << ": "
         << fixed << setprecision(8) << result;

    if (fabs(result - expected) < 0.0000001) {
        cout << " [PASSED]";
    } else {
        cout << " [FAILED]";
    }

    cout << endl;
}

// DEMONSTRATION

int main() {
    cout << "==== TERNARY SEARCH ====" << endl;

    // DISCRETE TERNARY SEARCH
    cout << "\n--- DISCRETE TERNARY SEARCH ---" << endl;

    vector<int> values;

    int input[] = {
        1, 3, 8, 12, 14, 11, 7, 4, 2
    };

    for (int i = 0; i < 9; i++) {
        values.push_back(input[i]);
    }

    cout << "Array: ";

    for (int i = 0; i < static_cast<int>(values.size()); i++) {
        cout << values[i] << " ";
    }

    cout << endl;

    int peakIndex = ternarySearchMaximum(values);

    cout << "Maximum index: " << peakIndex << endl;
    cout << "Maximum value: " << values[peakIndex] << endl;

    // DISCRETE EDGE CASES
    cout << "\n--- DISCRETE EDGE CASES ---" << endl;

    vector<int> emptyValues;

    testDiscreteSearch(
        emptyValues, -1, "Empty array"
    );

    vector<int> singleValue;
    singleValue.push_back(42);

    testDiscreteSearch(
        singleValue, 0, "Single element"
    );

    vector<int> increasing;

    increasing.push_back(1);
    increasing.push_back(2);
    increasing.push_back(3);
    increasing.push_back(4);
    increasing.push_back(5);

    testDiscreteSearch(
        increasing, 4, "Increasing array"
    );

    vector<int> decreasing;

    decreasing.push_back(5);
    decreasing.push_back(4);
    decreasing.push_back(3);
    decreasing.push_back(2);
    decreasing.push_back(1);

    testDiscreteSearch(
        decreasing, 0, "Decreasing array"
    );

    vector<int> plateau;

    plateau.push_back(1);
    plateau.push_back(3);
    plateau.push_back(5);
    plateau.push_back(5);
    plateau.push_back(5);
    plateau.push_back(4);
    plateau.push_back(2);

    testDiscreteSearch(
        plateau, 2, "Maximum plateau"
    );

    // CONTINUOUS TERNARY SEARCH
    cout << "\n--- CONTINUOUS TERNARY SEARCH ---" << endl;

    testContinuousSearch(
        -10.0, 10.0, 3.0, "Search in [-10, 10]"
    );

    testContinuousSearch(
        0.0, 10.0, 3.0, "Search in [0, 10]"
    );

    testContinuousSearch(
        4.0, 10.0, 4.0, "Maximum at left boundary"
    );

    testContinuousSearch(
        -10.0, 2.0, 2.0, "Maximum at right boundary"
    );

    return 0;
}