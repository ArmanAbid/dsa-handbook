#include <iostream>
#include <vector>
#include <limits>
using namespace std;

// FEASIBILITY CHECK
// Can all packages be shipped within the allowed days
// using the given capacity?

bool canShipWithinDays(
    const vector<long long>& weights,
    long long days,
    long long capacity
) {
    long long usedDays = 1;
    long long currentLoad = 0;

    for (vector<long long>::size_type i = 0;
         i < weights.size(); i++) {

        long long weight = weights[i];

        if (currentLoad + weight > capacity) {
            // Start a new day.
            usedDays++;
            currentLoad = weight;

        } else {
            currentLoad += weight;
        }

        // No need to continue if the limit is exceeded.
        if (usedDays > days) {
            return false;
        }
    }

    return true;
}

// BINARY SEARCH ON ANSWER
// Returns the minimum capacity required.
// Returns -1 for invalid input.

long long minimumShipCapacity(
    const vector<long long>& weights,
    long long days
) {
    if (days <= 0) {
        return -1;
    }

    if (weights.empty()) {
        return 0;
    }

    long long low = 0;
    long long high = 0;

    // Find the minimum and maximum possible capacities.
    for (vector<long long>::size_type i = 0;
         i < weights.size(); i++) {

        long long weight = weights[i];

        // Package weights must be positive.
        if (weight <= 0) {
            return -1;
        }

        if (weight > low) {
            low = weight;
        }

        // Prevent signed integer overflow.
        if (weight > numeric_limits<long long>::max() - high) {
            return -1;
        }

        high += weight;
    }

    // Search for the first feasible capacity.
    while (low < high) {
        long long middle = low + (high - low) / 2;

        if (canShipWithinDays(weights, days, middle)) {
            // This capacity works.
            // Try to find a smaller one.
            high = middle;
        } else {
            // This capacity is insufficient.
            low = middle + 1;
        }
    }

    return low;
}

// Helper function for demonstration.
void testMinimumCapacity(
    const vector<long long>& weights,
    long long days,
    long long expected,
    const char* description
) {
    long long result = minimumShipCapacity(weights, days);

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
    cout << "==== BINARY SEARCH ON ANSWER ====" << endl;

    vector<long long> weights;

    long long input[] = {
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10
    };

    for (int i = 0; i < 10; i++) {
        weights.push_back(input[i]);
    }

    // DISPLAY INPUT
    cout << "\nWeights: ";

    for (vector<long long>::size_type i = 0;
         i < weights.size(); i++) {
        cout << weights[i] << " ";
    }

    cout << endl;

    // BASIC TESTS
    cout << "\n--- BASIC TESTS ---" << endl;

    testMinimumCapacity(weights, 5, 15, "Ship within 5 days");
    testMinimumCapacity(weights, 3, 21, "Ship within 3 days");
    testMinimumCapacity(weights, 10, 10, "Ship within 10 days");
    testMinimumCapacity(weights, 1, 55, "Ship within 1 day");

    // EDGE CASES
    cout << "\n--- EDGE CASES ---" << endl;

    vector<long long> emptyWeights;

    testMinimumCapacity(
        emptyWeights, 5, 0, "Empty package array"
    );

    vector<long long> singlePackage;
    singlePackage.push_back(7);

    testMinimumCapacity(
        singlePackage, 2, 7, "Single package"
    );

    testMinimumCapacity(
        singlePackage, 1, 7, "Single package, one day"
    );

    vector<long long> equalWeights;

    equalWeights.push_back(5);
    equalWeights.push_back(5);
    equalWeights.push_back(5);
    equalWeights.push_back(5);

    testMinimumCapacity(
        equalWeights, 2, 10, "Equal package weights"
    );

    vector<long long> anotherExample;

    anotherExample.push_back(3);
    anotherExample.push_back(2);
    anotherExample.push_back(2);
    anotherExample.push_back(4);
    anotherExample.push_back(1);
    anotherExample.push_back(4);

    testMinimumCapacity(
        anotherExample, 3, 6, "Another shipping example"
    );

    // INVALID INPUT
    cout << "\n--- INVALID INPUT ---" << endl;

    testMinimumCapacity(
        weights, 0, -1, "Zero allowed days"
    );

    testMinimumCapacity(
        weights, -2, -1, "Negative allowed days"
    );

    vector<long long> invalidWeights;

    invalidWeights.push_back(3);
    invalidWeights.push_back(0);
    invalidWeights.push_back(5);

    testMinimumCapacity(
        invalidWeights, 2, -1, "Zero package weight"
    );

    return 0;
}